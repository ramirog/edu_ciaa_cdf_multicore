
# COMPILER
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
GDB = arm-none-eabi-gdb
NM = arm-none-eabi-nm
AS = arm-none-eabi-as

# M4 FLAGS
M4_CFLAGS += -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -DCORE_M4

M4_LFLAGS += -T $(CONFIG_DIR)$(DS)lpc4337$(DS)ld$(DS)ciaa_lpc4337_m4.ld
M4_LFLAGS += -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp

M4_AFLAGS += -ggdb3 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb

# M0 FLAGS
M0_CFLAGS += -mcpu=cortex-m0 -DCORE_M0 -DLPC43XX_CORE_M0APP

M0_LFLAGS += -T $(CONFIG_DIR)$(DS)lpc4337$(DS)ld$(DS)ciaa_lpc4337_m0.ld
M0_LFLAGS += -mcpu=cortex-m0

M0_AFLAGS += -ggdb3 -mcpu=cortex-m0 -mthumb


# OPEN OCD
OPENOCD_CFG  ?= $(CONFIG_DIR)$(DS)lpc4337$(DS)openocd$(DS)ciaa-nxp_b.cfg
TARGET_DOWNLOAD_FLASH_BASE_ADDR_M4 ?= 0x1A000000
TARGET_DOWNLOAD_FLASH_BASE_ADDR_M0 ?= 0x1B000000

# DEFAULT DRIVER
DRIVER_NAME ?= lpc43xx
