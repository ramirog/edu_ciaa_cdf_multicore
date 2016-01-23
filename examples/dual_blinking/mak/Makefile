
PROJECT_NAME ?= dual_blinking

# DEFAULT COMPILATION CONFIG
PROCESSOR_NAME ?= lpc4337
CPUTYPE        ?= lpc43xx
CPU            ?= lpc4337
COMPILER       ?= gcc
BOARD          ?= edu_ciaa_nxp
M0_ARCH        ?= cortexM0
M4_ARCH        ?= cortexM4
DRIVER_NAME ?= lpc43xx

# CORE LIST
CORES = M0 M4

# FILES
M4_INC 		= baremetal.h start_m0_core.h
M4_SRC      = sysinit.c multicore_m4.c cr_startup_lpc43xx.c crp.c start_m0_core.c
M4_SRC      += sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c
M4_SRC_DIRS = $(DVR_SRC_DIR)$(DS) $(PROJECT_PATH)$(DS)src$(DS)m4
M4_INC_DIRS = $(PROJECT_PATH)$(DS)inc 

M0_SRC       = multicore_m0.c crp.c cr_startup_lpc43xx-m0app.c
M0_SRC_DIRS = $(DVR_SRC_DIR)$(DS) $(PROJECT_PATH)$(DS)src$(DS)m0
M0_INC_DIRS = $(PROJECT_PATH)$(DS)inc 
