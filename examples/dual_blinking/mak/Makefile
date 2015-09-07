
PROJECT_NAME ?= dual_blinking

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
PROJECT_DEPS  = baremetal.h start_m0_core.h
DEPS 	  += $(patsubst %,$(PROJECT_INC_DIR)/%,$(PROJECT_DEPS))

PROJECT_M4_FILES  = sysinit.c multicore_m4.c cr_startup_lpc43xx.c crp.c start_m0_core.c
M4_SRC       = $(foreach file,$(PROJECT_M4_FILES), $(PROJECT_PATH)$(DS)src$(DS)m4$(DS)$(file))

PROJECT_M4_DRIVER_FILES  =  sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c
M4_SRC       += $(foreach file,$(PROJECT_M4_DRIVER_FILES), $(DVR_SRC_DIR)$(DS)$(file))

PROJECT_M0_FILES  = multicore_m0.c crp.c cr_startup_lpc43xx-m0app.c
M0_SRC       = $(foreach file,$(PROJECT_M0_FILES), $(PROJECT_PATH)$(DS)src$(DS)m0$(DS)$(file))

PROCESSOR_NAME ?= lpc4337
DRIVER_NAME ?= lpc43xx

