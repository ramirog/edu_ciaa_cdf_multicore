

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
WORKING_DIR := .
OUT_DIR  = $(WORKING_DIR)$(DS)out
BIN_DIR  = $(OUT_DIR)$(DS)bin

ROOT_DIR := .
CONFIG_DIR = $(ROOT_DIR)$(DS)config
DRIVERS_DIR = $(ROOT_DIR)$(DS)externals$(DS)drivers


###############################################################################
# OPEN OCD

# The file type to be flashed, must be specified explicitly. ex.: bin
TARGET_DOWNLOAD_EXTENSION = bin
OPENOCD_BIN 		   = openocd
OPENOCD_FLAGS 		   = -f $(OPENOCD_CFG)


###############################################################################
# INCLUDE PROJECT MAKEFILE
-include $(PROJECT_PATH)$(DS)mak$(DS)Makefile

###############################################################################
# INCLUDE PROCESSOR MAKEFILE
-include $(CONFIG_DIR)$(DS)$(PROCESSOR_NAME)$(DS)mak$(DS)Makefile

###############################################################################
# INCLUDE DRIVER MAKEFILE
-include $(DRIVERS_DIR)$(DS)$(DRIVER_NAME)$(DS)mak$(DS)Makefile


###############################################################################
# INITIALIZE FLAGS
CFLAGS ?= -Wall -ggdb3
COMMON_CFLAGS += -DCPUTYPE=$(CPUTYPE) -DCPU=$(CPU) -DBOARD=$(BOARD)
COMMON_CFLAGS += -c -mthumb -DNO_BOARD_LIB $(CFLAGS)

COMMON_LFLAGS += -nostdlib -fno-builtin -mthumb $(LFLAGS)

COMMON_AFLAGS = $(AFLAGS)


###############################################################################
# INCLUDE COMMON MODULES
LIBS := ''
include $(foreach coremodule, $(COMMON_MODS),$(coremodule)$(DS)mak$(DS)Makefile)
COMMON_LIBS := $(LIBS)

###############################################################################
# CORE TEMPLATE
# PARAMETRO <COREID>
# VARIABLES TO DEFINE IN THE PROJECT's Makefile
#  1. <CORE_ID>_SRC: Project sources exclusive to the core. Absolute or relative to '<CORE_ID>_SRC_DIRS'
#  1. <CORE_ID>_CFLAGS: CFLAGS exclusive to the core
#  1. <CORE_ID>_AFLAGS: AFLAGS exclusive to the core
#  1. <CORE_ID>_LFLAGS: LFLAGS exclusive to the core
#  1. <CORE_ID>_SRC_DIRS: Directory list with core sources
#  1. <CORE_ID>_INC_DIRS: Directory list with core includes
#  1. <CORE_ID>_MODS: Modules exclusive to the core
define CORE_TEMPLATE

# '----------------------- $(1) --------------------------'

ARCH := $$($(1)_ARCH)

# LOAD VARIABLES FROM LIBRARIES 
LIBS := ''
include $$(foreach coremodule, $$($(1)_MODS),$$(coremodule)$(DS)mak$(DS)Makefile)
$(1)_LIBS := $$(COMMON_LIBS) $$(LIBS)
$(1)_INC_DIRS += $$(foreach lib, $$($(1)_LIBS),$$($$(lib)_INC_PATH))
$(1)_SRC += $$(foreach lib, $$($(1)_LIBS),$$($$(lib)_SRC_FILES))

# SET CORE FLAGS
$(1)_ALL_AFLAGS := $$(COMMON_AFLAGS) $$($(1)_AFLAGS)
$(1)_ALL_CFLAGS := $$(COMMON_CFLAGS)
$(1)_ALL_CFLAGS += $$(foreach inc, $$($(1)_INC_DIRS), -I$$(inc))
$(1)_ALL_CFLAGS += -DARCH=$$($(1)_ARCH) $$($(1)_CFLAGS)
$(1)_ALL_LFLAGS := $$(COMMON_LFLAGS) -Wl,-Map="$$@.map",-gc-sections $$($(1)_LFLAGS)

# SET CORE OBJECT FILES
$(1)_OBJ_DIR := $(OUT_DIR)$(DS)obj$(DS)$(1)
$(1)_OBJECTS := $$(foreach file, $$($(1)_SRC), $$($(1)_OBJ_DIR)$(DS)$$(patsubst %.c,%.o,$$(patsubst %.s,%.o,$$(file))))

# SET TARGET
$(1)_TARGET_NAME := $(BIN_DIR)$(DS)$(PROJECT_NAME)_$(CORE_ID)

# SET RULES
$(1)_defs:
	@echo 'Configuring vpath for $(1)'
	$$(foreach pattern, %.c %.s %.h, $$(eval vpath $$(pattern)))
	$$(eval vpath %.c $$($(1)_SRC_DIRS))
	$$(eval vpath %.s $$($(1)_SRC_DIRS))

$$($(1)_OBJ_DIR)$(DS)%.o: %.c
	@echo ''
	@echo 'Core $(1). Compiling 'c' file: $$<.'
	@mkdir -p $$(@D)
	$(CC) -o $$@ $$< $$($(1)_ALL_CFLAGS)

$$($(1)_OBJ_DIR)$(DS)%.o: %.s
	@echo ''
	@echo Compiling 'asm' file: $<
	@mkdir -p $$(@D)
	$(AS) -o $$@ $$< $$($(1)_ALL_AFLAGS)

$$($(1)_TARGET_NAME): $(1)_defs $$($(1)_OBJECTS)
	@echo ''
	@echo '=== LINK $(1) CORE ==='
	@mkdir -p $$(@D)
	$(LD)  -o $$@.xsf $$($(1)_OBJECTS) $$($(1)_ALL_LFLAGS)
	arm-none-eabi-objcopy -v -O binary $$@.xsf $$@.bin
	@echo '-------------------'
	@echo ''

download$(1):
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

#$(foreach CORE_ID,$(CORES),$(info $(call CORE_TEMPLATE,$(CORE_ID))))
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


