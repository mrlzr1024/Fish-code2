CFLAGS := PRINT(".\build\Target 1\${c}.lst") OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:/keil5B/C51/INC/Atmel;D:\keil5B\C51\INC) DEFINE(__UVISION_VERSION='526')
CXXFLAGS := PRINT(".\build\Target 1\${cpp}.lst") OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:/keil5B/C51/INC/Atmel;D:\keil5B\C51\INC) DEFINE(__UVISION_VERSION='526')
ASMFLAGS := PRINT(.\build\Target 1\${asm}.lst) SET(SMALL) INCDIR(D:/keil5B/C51/INC/Atmel;D:\keil5B\C51\INC)
LDFLAGS :=  PRINT(".\build\Target 1\工程文件Project.map") REMOVEUNUSED
LDLIBS := 
