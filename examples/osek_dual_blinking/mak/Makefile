
PROJECT_NAME = dual_blinking

PROCESSOR_NAME ?= lpc4337
CPUTYPE        ?= lpc43xx
CPU            ?= lpc4337
COMPILER       ?= gcc
BOARD          ?= edu_ciaa_nxp
M0_ARCH           ?= cortexM0
M4_ARCH           ?= cortexM4

CORES = M0 M4

# DEPENDENCIES
PROJECT_INC_DIR   += $(PROJECT_PATH)$(DS)inc 
PROJECT_DEPS      = baremetal.h
DEPS 			  += $(patsubst %,$(PROJECT_INC_DIR)/%,$(PROJECT_DEPS))


# CONFIGURE COMMON MODULES
COMMON_MODS = modules$(DS)base modules$(DS)drivers modules$(DS)posix modules$(DS)ciaak modules$(DS)libs

# Configure M4 sources
PROJECT_M4_FILES     = blinking.c crp.c start_m0_core.c cr_startup_lpc43xx.c
M4_SRC       = $(foreach file,$(PROJECT_M4_FILES), $(PROJECT_PATH)$(DS)src$(DS)m4$(DS)$(file))
M4_SRC       += $(wildcard $(DVR_SRC_DIR)$(DS)*.c)	

M4_MODS = modules$(DS)rtos

# Configure M0 sources

PROJECT_M0_FILES     = blinking.c crp.c cr_startup_lpc43xx-m0app.c
M0_SRC       = $(foreach file,$(PROJECT_M0_FILES), $(PROJECT_PATH)$(DS)src$(DS)m0$(DS)$(file))
M0_SRC       += $(wildcard $(DVR_SRC_DIR)$(DS)*.c)	

M0_MODS = modules$(DS)rtos



