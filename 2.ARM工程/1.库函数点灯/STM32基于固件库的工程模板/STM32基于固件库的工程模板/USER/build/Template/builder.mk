EIDE_UNIFY_BUILDER := 1
CFLAGS := -c --apcs=interwork --cpu Cortex-M3 --c99 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\CORE -I.\. -I.\..\HALLIB\inc -I.\..\SYSTEM\sys -I.\..\SYSTEM\delay -I.\..\SYSTEM\usart -I.\..\HAREWEAR\LED -I.\.eide\deps -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CXXFLAGS := -c --cpp --apcs=interwork --cpu Cortex-M3 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\CORE -I.\. -I.\..\HALLIB\inc -I.\..\SYSTEM\sys -I.\..\SYSTEM\delay -I.\..\SYSTEM\usart -I.\..\HAREWEAR\LED -I.\.eide\deps -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
ASMFLAGS := --apcs=interwork --cpu Cortex-M3 --pd "__MICROLIB SETA 1" -g -I.\..\CORE -I.\. -I.\..\HALLIB\inc -I.\..\SYSTEM\sys -I.\..\SYSTEM\delay -I.\..\SYSTEM\usart -I.\..\HAREWEAR\LED -I.\.eide\deps
LDFLAGS := --cpu Cortex-M3 --library_type=microlib --scatter "e:/咸鱼先生的单片机开发文件/2.ARM工程/1.库函数点灯/STM32基于固件库的工程模板/STM32基于固件库的工程模板/USER/build/Template/USER.sct" --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --list .\build\Template\USER.map
LDLIBS := 
