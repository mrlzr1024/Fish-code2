EIDE_UNIFY_BUILDER := 1
CFLAGS := -c --apcs=interwork --cpu Cortex-M4.fp --li --c99 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\CORE -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -Ie:\咸鱼先生的单片机开发文件\2.ARM工程\其他\F4LED\USER\. -I.\..\FWLIB\inc -I.\.eide\deps -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER
CXXFLAGS := -c --cpp --apcs=interwork --cpu Cortex-M4.fp --li -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\..\CORE -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -Ie:\咸鱼先生的单片机开发文件\2.ARM工程\其他\F4LED\USER\. -I.\..\FWLIB\inc -I.\.eide\deps -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER
ASMFLAGS := --apcs=interwork --cpu Cortex-M4.fp --li --pd "__MICROLIB SETA 1" -g -I.\..\CORE -I.\..\SYSTEM\delay -I.\..\SYSTEM\sys -I.\..\SYSTEM\usart -Ie:\咸鱼先生的单片机开发文件\2.ARM工程\其他\F4LED\USER\. -I.\..\FWLIB\inc -I.\.eide\deps
LDFLAGS := --cpu Cortex-M4.fp --library_type=microlib --scatter "e:/咸鱼先生的单片机开发文件/2.ARM工程/其他/F4LED/USER/build/Template/USER.sct" --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --list .\build\Template\USER.map
LDLIBS := 
