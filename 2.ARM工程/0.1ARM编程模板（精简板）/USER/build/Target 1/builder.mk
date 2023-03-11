EIDE_UNIFY_BUILDER := 1
CFLAGS := -c --apcs=interwork --cpu Cortex-M3 --c99 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -I.\..\HARDWARE\LED -I.\..\HARDWARE\BEEP -I.\..\HARDWARE\KEY -I.\.eide\deps -DSTM32F10X_HD
CXXFLAGS := -c --cpp --apcs=interwork --cpu Cortex-M3 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -I.\..\HARDWARE\LED -I.\..\HARDWARE\BEEP -I.\..\HARDWARE\KEY -I.\.eide\deps -DSTM32F10X_HD
ASMFLAGS := --apcs=interwork --cpu Cortex-M3 --pd "__MICROLIB SETA 1" -g -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -I.\..\HARDWARE\LED -I.\..\HARDWARE\BEEP -I.\..\HARDWARE\KEY -I.\.eide\deps
LDFLAGS := --cpu Cortex-M3 --library_type=microlib --scatter "c:/Users/梁芝瑞/Desktop/天堂制造/咸鱼先生的图书馆/【正点原子】STM32F103最小系统板资料/4，程序源码/1，标准例程-寄存器版本/实验3 串口实验/USER/build/Target 1/USER.sct" --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --list ".\build\Target 1\USER.map"
LDLIBS := 
