
/*--------------------------------------------------------------*/
//写入一个字节(数据或指令)
//wbyte:	待写入的数据
//dat_cmd:	1-数据, 0-指令
void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd)
{
	unsigned char i;
	
	LCD_CS = 0;			//使能
	LCD_DC = dat_cmd;	//1-数据	//0-指令

	for(i = 8; i; i--)	//8位数据, 先高后低
	{
		if(wbyte & 0x80) {LCD_DIN = 1;}
		else			 {LCD_DIN = 0;}
		
		LCD_CLK = 0;
		wbyte <<= 1;	//移位(延时)
		LCD_CLK = 1;	//上升沿写入
	}
	
	LCD_CS = 1;			//禁止
}


/*--------------------------------------------------------------*/
//写入n个字节(数据)(ROM)
//*wbyte:	待写入的数据指针
//num:		待写入的数据个数
/*void LCD_write_nbyte(unsigned char code *wbyte, unsigned char num)
{
	unsigned char i, j;
	unsigned char temp;

	LCD_CS = 0;			//使能
	LCD_DC = 1;			//数据

	for(j = 0; j < num; j++)//num个数据
	{
		temp = wbyte[j];
		for(i = 8; i; i--)	//8位数据, 先高后低
		{
			if(temp & 0x80) {LCD_DIN = 1;}
			else			{LCD_DIN = 0;}
		
			LCD_CLK = 0;
			temp <<= 1;		//移位(延时)
			LCD_CLK = 1;	//上升沿写入
		}	
	}
	
	LCD_CS = 1;			//禁止
}


/*--------------------------------------------------------------*/
//显示清屏(清DDRAM)
void LCD_clr_scr(void)
{
	unsigned int i;
	
	LCD_write_cmd(X_Col_Addr);
	LCD_write_cmd(Y_Page_Addr);
	
	for(i = 504; i; i--) LCD_write_dat(0x00);
}


/*--------------------------------------------------------------*/
//显示清行
//num:	0 - 5
void LCD_clr_row(unsigned char num)
{
	unsigned char i;
	
	LCD_pos_byte(0, num);
	for(i = 84; i; i--) LCD_write_dat(0x00);
}


/*--------------------------------------------------------------*/
//液晶字节定位(1*1)
//液晶规划:
//x: 0 - 83
//y: 0 - 5
void LCD_pos_byte(unsigned char x, unsigned char y)
{
	x |= X_Col_Addr;  
	y |= Y_Page_Addr; 
	LCD_write_cmd(x);	//列地址
	LCD_write_cmd(y);	//页地址
}


/*--------------------------------------------------------------*/
//液晶字符输出(8*16字体)
//x: 0 - 9
//y: 0 - 2
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat)
{
	unsigned char i, j;

	c_dat -= 32;
	x <<= 3;		//8
	y <<= 1;		//16
	for(j = 0; j < 2; j++)
	{
		LCD_pos_byte(x, (y + j));
		for(i = 0; i < 8; i++) 
		LCD_write_dat(Font_code[c_dat][8 * j + i]);		
	}
}


/*--------------------------------------------------------------*/
//液晶字符串输出(8*16字体)
//x: 0 - 9
//y: 0 - 2
void LCD_prints(unsigned char x, unsigned char y, unsigned char code *s_dat)
{
	while(*s_dat && x < 10) 
	{LCD_printc(x++, y, *s_dat); s_dat++;}
}


/*--------------------------------------------------------------*/
//复位LCD5510
/*void LCD_reset_5510(void)
{
	LCD_clr_scr();				//清全屏
	
	LCD_write_cmd(0x25);		//省电模式, 水平寻址, 扩展指令
	LCD_write_cmd(0x04);		//VLCD温度系数0
	LCD_write_cmd(0x10);		//设置偏置系统(BSx)
	LCD_write_cmd(0xc0);		//设置电压VLCD = 3.06 + 0.06*Vop;
	
	LCD_write_cmd(0x24);		//省电模式, 水平寻址, 常规指令
	LCD_write_cmd(0x08);		//显示空白
	LCD_write_cmd(Y_Page_Addr);	//起始页地址0
	LCD_write_cmd(X_Col_Addr);	//起始列地址0
}


/*--------------------------------------------------------------*/
//初始化LCD5510
void LCD5510_Init(void)
{
	LCD_reset_hard;				//硬件复位
//	LCD_reset_soft;				//软件复位

	LCD_write_cmd(0x21);		//工作模式, 水平寻址, 扩展指令
	LCD_write_cmd(0x06);		//VLCD温度系数2
	LCD_write_cmd(0x13);		//设置偏置系统(BSx) 1:48
	LCD_write_cmd(0xc8);		//设置电压VLCD = 3.06 + 0.06*Vop, 对比度调整

	LCD_write_cmd(0x20);		//工作模式, 水平寻址, 常规指令
	LCD_write_cmd(0x0c);		//普通模式
	LCD_write_cmd(Y_Page_Addr);	//起始页地址0
	LCD_write_cmd(X_Col_Addr);	//起始列地址0
	LCD_clr_scr();				//清全屏
}

/*--------------------------------------------------------------*/
	




 
