#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif
#define MIN(a,b)		((a < b) ? (a):(b))
#define MAX(a,b)		((a > b) ? (a):(b))
#define ABS(x)			((x) ? (x):(-x))
typedef unsigned char	uint8;			/* 定义可移植的无符号8位整数关键字*/
typedef signed   char	int8;			/* 定义可移植的有符号8位整数关键字*/
typedef unsigned int	uint16;			/* 定义可移植的无符号16位整数关键字*/
typedef signed   int	int16;			/* 定义可移植的有符号16位整数关键字*/
typedef unsigned long	uint32;			/* 定义可移植的无符号32位整数关键字*/
typedef signed   long	int32;			/* 定义可移植的有符号32位整数关键字*/