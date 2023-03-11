CFLAGS := -std=c11 -c -xc -mthumb -mfloat-abi=soft -mcpu=cortex-m4 -Og -Wall -g -ffunction-sections -fdata-sections -I./.eide/deps -I./Core/Src -I./Core/Inc -I./Drivers -I./Drivers/STM32F4xx_HAL_Driver/Src -I./Drivers/STM32F4xx_HAL_Driver/Inc -I./Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I./Drivers/CMSIS/Include -I./Drivers/CMSIS/Device/ST/STM32F4xx/Include -DSTM32F401xE
CXXFLAGS := -std=c++11 -c -xc++ -mthumb -mfloat-abi=soft -mcpu=cortex-m4 -Og -Wall -g -ffunction-sections -fdata-sections -I./.eide/deps -I./Core/Src -I./Core/Inc -I./Drivers -I./Drivers/STM32F4xx_HAL_Driver/Src -I./Drivers/STM32F4xx_HAL_Driver/Inc -I./Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I./Drivers/CMSIS/Include -I./Drivers/CMSIS/Device/ST/STM32F4xx/Include -DSTM32F401xE
ASMFLAGS := -c -x assembler-with-cpp -mthumb -mfloat-abi=soft -mcpu=cortex-m4 -g -I./.eide/deps -I./Core/Src -I./Core/Inc -I./Drivers -I./Drivers/STM32F4xx_HAL_Driver/Src -I./Drivers/STM32F4xx_HAL_Driver/Inc -I./Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I./Drivers/CMSIS/Include -I./Drivers/CMSIS/Device/ST/STM32F4xx/Include
LDFLAGS := -mthumb -mfloat-abi=soft -mcpu=cortex-m4 -T "e:/咸鱼先生的单片机开发文件/2.ARM工程/F401-2.SPI/SPI/STM32F401CDUx_FLASH.ld" --specs=nosys.specs --specs=nano.specs -Wl,--gc-sections -Wl,--print-memory-usage -Wl,-Map=./build/Debug/SPI.map
LDLIBS := -lm
