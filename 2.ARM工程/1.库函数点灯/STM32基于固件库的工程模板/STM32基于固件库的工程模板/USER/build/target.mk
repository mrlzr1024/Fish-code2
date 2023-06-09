###########################################################################
#  !!! This file is Auto-Generated By Embedded IDE, Don't modify it !!!
###########################################################################

# eide version
EIDE_VER = 2

# current target
CUR_TARGET := Template

# current compiler
COMPILER_TYPE := AC5

# include folders
INCLUDE_FOLDERS += ../CORE
INCLUDE_FOLDERS += .
INCLUDE_FOLDERS += ../HALLIB/inc
INCLUDE_FOLDERS += ../SYSTEM/sys
INCLUDE_FOLDERS += ../SYSTEM/delay
INCLUDE_FOLDERS += ../SYSTEM/usart
INCLUDE_FOLDERS += ../HAREWEAR/LED
INCLUDE_FOLDERS += .eide/deps

# library search folders

# c source files
C_SOURCES += ../CORE/core_cm3.c
C_SOURCES += ../HALLIB/src/misc.c
C_SOURCES += ../HALLIB/src/stm32f10x_adc.c
C_SOURCES += ../HALLIB/src/stm32f10x_bkp.c
C_SOURCES += ../HALLIB/src/stm32f10x_can.c
C_SOURCES += ../HALLIB/src/stm32f10x_cec.c
C_SOURCES += ../HALLIB/src/stm32f10x_crc.c
C_SOURCES += ../HALLIB/src/stm32f10x_dac.c
C_SOURCES += ../HALLIB/src/stm32f10x_dbgmcu.c
C_SOURCES += ../HALLIB/src/stm32f10x_dma.c
C_SOURCES += ../HALLIB/src/stm32f10x_exti.c
C_SOURCES += ../HALLIB/src/stm32f10x_flash.c
C_SOURCES += ../HALLIB/src/stm32f10x_fsmc.c
C_SOURCES += ../HALLIB/src/stm32f10x_gpio.c
C_SOURCES += ../HALLIB/src/stm32f10x_i2c.c
C_SOURCES += ../HALLIB/src/stm32f10x_iwdg.c
C_SOURCES += ../HALLIB/src/stm32f10x_pwr.c
C_SOURCES += ../HALLIB/src/stm32f10x_rcc.c
C_SOURCES += ../HALLIB/src/stm32f10x_rtc.c
C_SOURCES += ../HALLIB/src/stm32f10x_sdio.c
C_SOURCES += ../HALLIB/src/stm32f10x_spi.c
C_SOURCES += ../HALLIB/src/stm32f10x_tim.c
C_SOURCES += ../HALLIB/src/stm32f10x_usart.c
C_SOURCES += ../HALLIB/src/stm32f10x_wwdg.c
C_SOURCES += ../HAREWEAR/LED/LED.c
C_SOURCES += ../SYSTEM/delay/delay.c
C_SOURCES += ../SYSTEM/sys/sys.c
C_SOURCES += ../SYSTEM/usart/usart.c
C_SOURCES += main.c
C_SOURCES += stm32f10x_it.c
C_SOURCES += system_stm32f10x.c

# cpp source files

# asm source files
ASM_SOURCES += ../CORE/startup_stm32f10x_hd.s

# object files

# macro defines
DEFINES += STM32F10X_MD
DEFINES += USE_STDPERIPH_DRIVER