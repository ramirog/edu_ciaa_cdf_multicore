
PROJECT_NAME ?= adc_pool

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
CORES = M4

# FILES
M4_SRC       =   sysinit.c adc.c cr_startup_lpc43xx.c crp.c helper.c
M4_SRC       +=  sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c dac_18xx_43xx.c adc_18xx_43xx.c gpio_18xx_43xx.c
M4_SRC_DIRS = $(DVR_SRC_DIR)$(DS) $(PROJECT_PATH)$(DS)src$(DS)m4
M4_INC_DIRS = $(PROJECT_PATH)$(DS)inc$(DS)m4
