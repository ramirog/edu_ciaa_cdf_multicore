

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
PROJECT_PATH ?= .$(DS)examples$(DS)com_queue


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
# INCLUDE DRIVERS MAKEFILE
-include $(DRIVERS_DIR)$(DS)$(DRIVER_NAME)$(DS)mak$(DS)Makefile


###############################################################################
# INITIALIZE FLAGS
CFLAGS += -DCPUTYPE=$(CPUTYPE) -DCPU=$(CPU) -DBOARD=$(BOARD)
CFLAGS += -I $(PROJECT_INC_DIR)
CFLAGS += -c -Wall -ggdb3 -mthumb -DNO_BOARD_LIB

LFLAGS += -nostdlib -fno-builtin -mthumb


###############################################################################
# INCLUDE COMMON MODULES
LIBS := ''
include $(foreach coremodule, $(COMMON_MODS),$(coremodule)$(DS)mak$(DS)Makefile)
COMMON_LIBS := $(LIBS)

###############################################################################
# CORE TEMPLATE
# PARAMETRO <COREID>
# VARIABLES A DEFINIR
#  1. <CORE_ID>_SRC: sources del proyecto que van al core
#  1. <CORE_ID>_CFLAGS: CFLAGS especificos para el core
#  1. <CORE_ID>_LFLAGS: LFLAGS especificos para el core

define CORE_TEMPLATE

# '----------------------- $(1) --------------------------'

LIBS := ''
ARCH := $$($(1)_ARCH)
include $$(foreach coremodule, $$($(1)_MODS),$$(coremodule)$(DS)mak$(DS)Makefile)
$(1)_LIBS := $$(LIBS)

# SET INCLUDES
$(1)_INC_PATHS += $$(foreach lib, $$($(1)_LIBS),$$($$(lib)_INC_PATH))
$(1)_INC_PATHS += $$(foreach lib, $$(COMMON_LIBS),$$($$(lib)_INC_PATH))
$(1)_CFLAGS += $$(foreach inc, $$($(1)_INC_PATHS), -I$$(inc))
$(1)_CFLAGS += -DARCH=$$($(1)_ARCH)

# SET OBJECT FILES
$(1)_SRC += $$(foreach lib, $$($(1)_LIBS),$$($$(lib)_SRC_FILES))
$(1)_SRC += $$(foreach lib, $$(COMMON_LIBS),$$($$(lib)_SRC_FILES))
$(1)_OBJ_DIR := $(OUT_DIR)$(DS)obj$(DS)$(1)
$(1)_OBJECTS := $$(foreach file, $$($(1)_SRC), $$($(1)_OBJ_DIR)$(DS)$$(patsubst .$(DS)%.c,%.o,$$(patsubst .$(DS)%.s,%.o,$$(file))))


$(1)_TARGET_NAME := $(BIN_DIR)$(DS)$(PROJECT_NAME)_$(CORE_ID)

# SET RULES
$(1)_defs:
	@echo 'Setting ARCH to $$($(1)_ARCH)'
	$$(eval ARCH := $$($(1)_ARCH))

$$($(1)_OBJ_DIR)$(DS)%.o: %.c
	@echo ''
	@echo 'Core $(1). Compiling 'c' file: $$<.'
	@mkdir -p $$(@D)
	$(CC) -o $$@ $$< $$(CFLAGS) $$($(1)_CFLAGS)

$$($(1)_OBJ_DIR)$(DS)%.o : %.s
	@echo ''
	@echo Compiling 'asm' file: $<
	@mkdir -p $$(@D)
	$(AS) -o $$@ $$< $$(AFLAGS) $$($(1)_AFLAGS)

$$($(1)_TARGET_NAME): $(1)_defs $$($(1)_OBJECTS)
	@echo '=== LINK $(1) CORE ==='
	$(LD)  -o $$@.xsf $$($(1)_OBJECTS) $$(LFLAGS) $$($(1)_LFLAGS) -Wl,-Map="$$@.map",-gc-sections
	arm-none-eabi-objcopy -v -O binary $$@.xsf $$@.bin
	@echo '-------------------'

download$(1):
	@echo  '=== DOWNLOAD $(1) CORE ==='
	$(OPENOCD_BIN) $(OPENOCD_FLAGS) -c "init" -c "halt 0" -c "flash write_image erase unlock $$($(1)_TARGET_NAME).$(TARGET_DOWNLOAD_EXTENSION) $$(TARGET_DOWNLOAD_FLASH_BASE_ADDR_$(1)) $(TARGET_DOWNLOAD_EXTENSION)" -c "shutdown"

# UPDATE COLLECTION VARIABLES
TARGETS += $$($(1)_TARGET_NAME)
DOWNLOAD_RULES += download$(1)
OBJECT_DIRS += $$($(1)_OBJ_DIR)

endef

###############################################################################
# TARGETS

.PHONY: all
all: main_target

$(foreach CORE_ID,$(CORES),$(eval $(call CORE_TEMPLATE,$(CORE_ID))))

main_target: $(TARGETS)
	@echo TARGETS: $(TARGETS)


###############################################################################
# DOWNLOAD

download: $(DOWNLOAD_RULES)
	$(OPENOCD_BIN) $(OPENOCD_FLAGS) -c "init" -c "reset run" -c "shutdown"


###############################################################################
# CLEAN

.PHONY: clean
clean:
	$(foreach obj_dir, $(OBJECT_DIRS), find $(obj_dir) -name "*.o" -type f -delete $(endl))


