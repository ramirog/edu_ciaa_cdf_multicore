

###############################################################################
# VARIABLES

DS = /

# Libraries group linker parameters
START_GROUP       = -Xlinker --start-group
END_GROUP         = -Xlinker --end-group

define endl


endef

###############################################################################
# INCLUDE CONFIG MAKEFILE

-include Makefile.mine
PROJECT_PATH ?= .$(DS)examples$(DS)dual_blinking


###############################################################################
# PATHS

# DIRS
ROOT_DIR := .
OUT_DIR  = $(ROOT_DIR)$(DS)out
BIN_DIR  = $(OUT_DIR)$(DS)bin

CONFIG_DIR = $(ROOT_DIR)$(DS)config
DRIVERS_DIR = $(ROOT_DIR)$(DS)externals$(DS)drivers


###############################################################################
# OPEN OCD

# The file type to be flashed, must be specified explicitly. ex.: bin
TARGET_DOWNLOAD_EXTENSION = bin
OPENOCD_BIN 		   = openocd
OPENOCD_FLAGS 		   = -f $(OPENOCD_CFG)


###############################################################################
# INCLUDE PROYECT MAKEFILE
-include $(PROJECT_PATH)$(DS)mak$(DS)Makefile


###############################################################################
# INCLUDE PROCESSOR MAKEFILE
-include $(CONFIG_DIR)$(DS)$(PROCESSOR_NAME)$(DS)mak$(DS)Makefile


###############################################################################
# INCLUDE DRIVER MAKEFILE
-include $(DRIVERS_DIR)$(DS)$(DRIVER_NAME)$(DS)mak$(DS)Makefile


###############################################################################
# INITIALIZE FLAGS

CFLAGS += -I $(PROJECT_INC_DIR)
CFLAGS += -c -Wall -ggdb3 -mthumb -DNO_BOARD_LIB

LFLAGS += -nostdlib -fno-builtin -mthumb

DEPS = $(patsubst %,$(PROJECT_INC_DIR)/%,$(PROJECT_DEPS))


###############################################################################
# CORE TEMPLATE
# PARAMETRO <COREID>
# VARIABLES A DEFINIR
#  1. PROJECT_<COREID>_SRC: sources del proyecto que van al core
#  1. <COREID>_CFLAGS: CFLAGS especificos para el core
#  1. <COREID>_LFLAGS: LFLAGS especificos para el core

define CORE_TEMPLATE

$(1)_OBJ_DIR := $(OUT_DIR)$(DS)obj$(DS)$(1)

$$($(1)_OBJ_DIR)$(DS)%.o: $$(PROJECT_$(1)_SRC_DIR)$(DS)%.c
	@echo ' '
	@echo $$^
	@echo 'Core $(1). Compiling 'c' file: $$<.'
	$(CC) -c -o $$($(1)_OBJ_DIR)$(DS)$$(notdir $$@) $$< $(CFLAGS) $$($(1)_CFLAGS)

$$($(1)_OBJ_DIR)$(DS)%.o: $(DVR_SRC_DIR)$(DS)%.c
	@echo ' '
	@echo 'Core $(1). Compiling 'c' file: $$<.'
	$(CC) -c -o $$($(1)_OBJ_DIR)$(DS)$$(notdir $$@) $$< $(CFLAGS) $$($(1)_CFLAGS)

$(1)_OBJECTS := $(foreach file, $(PROJECT_$(1)_SRC), $$($(1)_OBJ_DIR)$(DS)$(notdir $(patsubst %.c, %.o, $(file))))

$(1)_TARGET_NAME = $(BIN_DIR)$(DS)$(PROJECT_NAME)_$(1)
$(1)_LFLAGS += -Wl,-Map="$$($(1)_TARGET_NAME).map",-gc-sections

$$($(1)_TARGET_NAME): $$($(1)_OBJECTS)
	@echo ' ' 
	@echo $$^
	@echo '=== LINK $(1) CORE ==='
	$(LD)  -o $$@.xsf $$($(1)_OBJECTS) $(LFLAGS) $$($(1)_LFLAGS) 
	arm-none-eabi-objcopy -v -O binary $$@.xsf $$@.bin
	@echo '-------------------'

TARGET_CORES += $$($(1)_TARGET_NAME)

download$(1):
	$(OPENOCD_BIN) $(OPENOCD_FLAGS) -c "init" -c "halt 0" -c "flash write_image erase unlock $$($(1)_TARGET_NAME).$(TARGET_DOWNLOAD_EXTENSION) $$(TARGET_DOWNLOAD_FLASH_BASE_ADDR_$(1)) $(TARGET_DOWNLOAD_EXTENSION)" -c "shutdown"

DOWNLOAD_CORES += download$(1)

CORE_OBJECT_DIRS += $$($(1)_OBJ_DIR)

endef

###############################################################################
# TARGETS

.PHONY: all
all: out_dirs $(PROJECT_NAME)

.PHONY: out_dirs
out_dirs:
	$(foreach core,$(CORES), mkdir -p $(OUT_DIR)$(DS)obj$(DS)$(core) $(endl))

$(foreach i,$(CORES),$(eval $(call CORE_TEMPLATE,$(i))))

$(PROJECT_NAME): $(TARGET_CORES)


###############################################################################
# DOWNLOAD

download: $(DOWNLOAD_CORES)
	$(OPENOCD_BIN) $(OPENOCD_FLAGS) -c "init" -c "reset run" -c "shutdown"


###############################################################################
# CLEAN

.PHONY: clean
clean:
	$(foreach obj_dir, $(CORE_OBJECT_DIRS), rm -f $(obj_dir)$(DS)*.o $(endl))


