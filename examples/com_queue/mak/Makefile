
PROJECT_NAME ?= ipc_queue

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
PROJECT_DEPS  = shmem.h start_m0_core.h queue32.h core_api.h
DEPS 	  += $(patsubst %,$(PROJECT_INC_DIR)/%,$(PROJECT_DEPS))

PROJECT_COMMON_FILES  = crp.c core_api.c queue32.c
COMMON_SRC       = $(foreach file,$(PROJECT_COMMON_FILES), $(PROJECT_PATH)$(DS)src$(DS)common$(DS)$(file))

PROJECT_M4_FILES  = sysinit.c multicore_m4.c cr_startup_lpc43xx.c start_m0_core.c shmem_cfg.c
M4_SRC       = $(foreach file,$(PROJECT_M4_FILES), $(PROJECT_PATH)$(DS)src$(DS)m4$(DS)$(file))
M4_CFLAGS += -DCURRENT_CORE_NUMBER=0

PROJECT_M4_DRIVER_FILES  =  sysinit_18xx_43xx.c fpu_init.c clock_18xx_43xx.c chip_18xx_43xx.c
M4_SRC       += $(foreach file,$(PROJECT_M4_DRIVER_FILES), $(DVR_SRC_DIR)$(DS)$(file))
M4_SRC       += $(COMMON_SRC)

PROJECT_M0_FILES  = multicore_m0.c cr_startup_lpc43xx-m0app.c
M0_SRC       = $(foreach file,$(PROJECT_M0_FILES), $(PROJECT_PATH)$(DS)src$(DS)m0$(DS)$(file))
M0_SRC       += $(COMMON_SRC)
M0_CFLAGS += -DCURRENT_CORE_NUMBER=1

PROCESSOR_NAME ?= lpc4337
DRIVER_NAME ?= lpc43xx