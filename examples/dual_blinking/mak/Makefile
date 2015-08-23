
PROJECT_NAME ?= dual_blinking

CORES = M0 M4

PROJECT_INC_DIR   += $(PROJECT_PATH)$(DS)inc
PROJECT_DEPS      = baremetal.h

PROJECT_M4_SRC_DIR   += $(PROJECT_PATH)$(DS)src$(DS)m4
PROJECT_M4_SRC       =   sysinit.c multicore_m4.c cr_startup_lpc43xx.c crp.c start_m0_core.c
PROJECT_M4_SRC       +=  sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c

PROJECT_M0_SRC_DIR   += $(PROJECT_PATH)$(DS)src$(DS)m0
PROJECT_M0_SRC       = multicore_m0.c crp.c cr_startup_lpc43xx-m0app.c

PROCESSOR_NAME ?= lpc4337
DRIVER_NAME ?= lpc43xx

