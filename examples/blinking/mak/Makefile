
PROJECT_NAME ?= blinking

CORES = M4

PROJECT_INC_DIR   += $(PROJECT_PATH)$(DS)inc
PROJECT_DEPS      = baremetal.h

PROJECT_M4_SRC_DIR   += $(PROJECT_PATH)$(DS)src$(DS)m4
PROJECT_M4_SRC       =   sysinit.c multicore_m4.c cr_startup_lpc43xx.c crp.c
PROJECT_M4_SRC       +=  sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c

PROCESSOR_NAME ?= lpc4337
DRIVER_NAME ?= lpc43xx
