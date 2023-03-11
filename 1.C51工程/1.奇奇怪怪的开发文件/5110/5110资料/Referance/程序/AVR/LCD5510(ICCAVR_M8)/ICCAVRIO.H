/*--------------------------------------------------------------*/
// ICC-AVR application builder : 2009-7-22 20:46:10
// Target : M8
// Crystal: 1.000Mhz
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
//防止重复定义
#ifndef __ICCAVRIO_H__
#define	__ICCAVRIO_H__


/*--------------------------------------------------------------*/
//定义新的数据类型，方便进行IO端口操作。
//定义一个8字节的位域 bit0~7是每个位域名称, 1代表一位, bit_field就是整个位域的名称
typedef struct
 {
    unsigned bit0: 1 ;
    unsigned bit1: 1 ;
    unsigned bit2: 1 ;
    unsigned bit3: 1 ;
    unsigned bit4: 1 ;
    unsigned bit5: 1 ;
    unsigned bit6: 1 ;
    unsigned bit7: 1 ;
}bit_field;
#define GET_BIT(adr)   (*(( volatile bit_field * )(&adr)))


/*--------------------------------------------------------------*/
//设置是否自动初始化IO方向寄存器
//自动初始化IO方向寄存器无需在初始化程序中用PORTA=0X..;形式来初始化io控制寄存器，
//同时也不争的证明了avr单片机的端口输入/出切换功能
#define AUTOINIT	1		
//					0	//手动配置IO方向寄存器
//					1	//自动配置IO方向寄存器					


/*--------------------------------------------------------------*/
//输出端口设置
#if	(AUTOINIT == 1)		//自动初始化IO方向寄存器
	#define PORT(m, n)	GET_BIT(DDR##m).bit##n = 1;\
						GET_BIT(PORT##m).bit##n
	#define PPORT(m, n)	DDR##m |= n; PORT##m

#else					//需手动配置IO方向寄存器
	#define PORT(m, n)	GET_BIT(PORT##m).bit##n
#endif
//手动
#define	P_OUT(m, n)		GET_BIT(PORT##m).bit##n


/*--------------------------------------------------------------*/
//输入端口设置(检测输入端口)
#if (AUTOINIT == 1)		//自动初始化IO方向寄存器
	#define PIN(m, n)	(!(GET_BIT(DDR##m).bit##n = 0) &&\
						 (GET_BIT(PORT##m).bit##n = 1) &&\
						 GET_BIT(PIN##m).bit##n)
	#define PPIN(m, n)  (DDR##m &= ~n, PORT##m = n, PIN##m & n)

#else					//需手动配置IO方向寄存器
	#define PIN(m, n)	GET_BIT(PIN##m).bit##n
#endif 
//手动
#define	P_IN(m, n)		GET_BIT(PIN##m).bit##n


/*-------------------------------------------------------------*/
//端口输入输出方向设置
//方便直观操作 自由设定单个io口的方向
#define DRA(n)			GET_BIT(DDRA).bit##n 
#define DRB(n)			GET_BIT(DDRB).bit##n
#define DRC(n)			GET_BIT(DDRC).bit##n
#define DRD(n)			GET_BIT(DDRD).bit##n
#define DDR(m, n)		GET_BIT(DDR##m).bit##n


/*--------------------------------------------------------------*/
#endif



/*-------------------------------------------------------------*/
/*
//在我们实际项目中，需要用到按键输入，继电器，SPI器件输出，
//两者分别为输入，和输出之用，这时候可以方面的在各自c文件对应的.h文件中写下如下语句：
#define KEY1	PIN(C, 3)		//定义三个按键，使能上拉
#define KEY2	PIN(C, 4)
#define KEY3	PIN(C, 5)

#define SCLK_SPI	PORT(B, 5)	//定义spi口的两个控制引脚
#define CS_SPI		PORT(C, 0)


//多位定义（数据总线端口）
#define KEY_IN	PPIN(D, 0x0f)	//按键手动输入	低四位设置为输入，其他位方向不变
#define	LED_OUT	PPORT(C, 0x0f)	//LED显示输出	低四位设置为输出，其他位方向不变
定义后直接赋值：
LED_OUT = ~KEY_IN;	//高电平点亮LED, 按键低电平有效

#define LCD_DATA_IN		PPIN(D, 0xff)	//LCD数据总线设置为输入
#define LCD_DATA_OUT	PPORT(D, 0xff)	//LCD数据总线设置为输出
定义后直接赋值：
TEMP = LCD_DATA_IN;		//读入数据
LCD_DATA_OUT = TEMP;	//输出数据


//上述PIN PORT 自动化定义的方法中，有些不足，
//如：在DS18B20这样的应用中，需要切换引脚的输入输出，就必须为18B20的引脚安排两套定义，
//类似于：	
		#define DS18B20_IN   PIN(A, 1)
		#define DS18B20_OUT  PORT(A, 1)

//此外：PORT和PIN的自动化定义中，含有DDR的操作，
//凡是用到PIN和PORT定义过的端口的地方都需要重复DDR操作，带来冗余代码。
//呵呵，虽然代码有点繁琐，但却很方便的，便于程序的移植。
//希望朋友们能够用得上！
/*-------------------------------------------------------------*/