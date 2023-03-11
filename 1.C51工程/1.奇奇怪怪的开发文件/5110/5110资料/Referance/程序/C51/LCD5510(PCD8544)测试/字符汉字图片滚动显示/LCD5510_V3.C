
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
//液晶字符输出(6*8字体)
//x: 0 - 13
//y: 0 - 5
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat)
{
	unsigned char i;

	c_dat -= 32;		//查表
	x *= 6;				//宽6

	LCD_pos_byte(x, y);	//坐标
	for(i = 0; i < 6; i++) LCD_write_dat(Font_code[c_dat][i]);	
}


/*--------------------------------------------------------------*/
//液晶字符串输出(6*8字体)
//x: 0 - 13
//y: 0 - 5
void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat)
{
	while(*s_dat && x < 14) {LCD_printc(x++, y, *s_dat); s_dat++;}
}


/*--------------------------------------------------------------*/
//液晶字符串输出,自动换行(6*8字体)
//x: 0 - 13
//y: 0 - 5
void LCD_printsl(unsigned char x, unsigned char y, unsigned char *s_dat)
{
	while(*s_dat) 
	{
		LCD_printc(x++, y, *s_dat); 
		s_dat++;
		if(x == 14) {x = 0; y++;}
		if(y == 6)  {y = 0;}
	}
}


/*--------------------------------------------------------------*/
//液晶汉字输出(16*16字体)
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//x: 0 - 4
//y: 0 - 2
void LCD_printch(unsigned char x, unsigned char y, unsigned char code *h_dat)
{
	unsigned char i, j;

	x <<= 4; 	//字宽16
	y <<= 1;	//字高16
	for(j = 0; j < 2; j++)
	{
		LCD_pos_byte(x, (y + j));	//坐标
		for(i = 0; i < 16; i++) LCD_write_dat(h_dat[16 * j + i]);		
	}
}


/*--------------------------------------------------------------*/
//液晶汉字输出(16*16字体)
//查表显示输出
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//x: 0 - 4
//y: 0 - 2
void LCD_showch(unsigned char x, unsigned char y, unsigned char code *dat)
{
	unsigned char i;
	
	for(i = 0; i < GB_16_num; i++)
	{
		if((GB_16[i].Index[0] == dat[0]) && (GB_16[i].Index[1] == dat[1])) break;
	}
	LCD_printch(x, y, GB_16[i].Msk);
}


/*--------------------------------------------------------------*/
//液晶汉字词组输出(16*16字体)
//查表显示输出
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//x: 0 - 4
//y: 0 - 2
//一行最多5个
void LCD_showsh(unsigned char x, unsigned char y, unsigned char code *dat)
{
	while(*dat) {LCD_showch(x++, y, dat); dat += 2;}	//一个汉字GB码由2个字节组成
}


/*--------------------------------------------------------------*/
//显示84X48图片
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
void LCD_picture(unsigned char code *img_dat)
{
	unsigned int i;

	for(i = 0; i < 504; i++) LCD_write_dat(img_dat[i]);
}


/*--------------------------------------------------------------*/
//定位显示指定大小图片
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//pag:	0 - 5			页坐标
//col:  0 - 83			列坐标
//x:	0 - (83-col)	图片宽
//y:	0 - (47-pag*8)	图片高
void LCD_pos_picture(unsigned char col, unsigned char pag, unsigned char x, unsigned char y, unsigned char code *img_dat)
{
	unsigned char i, j;

	y = (y + 4) >> 3;			//四舍五入
	for(j = 0; j < y; j++)
	{	
		for(i = 0; i < x; i++) 
		{
			LCD_pos_byte(col + i, pag + j);		//坐标
			LCD_write_dat(img_dat[j * x + i]);	//数据
		}
	}
}


/*--------------------------------------------------------------*/
//滚动显示图片
//取码规则:	低位在前, 逐列式扫描, 阴码(1-亮, 0-灭)
//pag:	0 - 5			页坐标
//col:  0 - 83			列坐标
//y:	0 - (47-pag*8)	图片高
void LCD_roll_picture(unsigned char col, unsigned char pag, unsigned char y, unsigned char code *img_dat)
{
	unsigned char i, j;

	y = (y + 4) >> 3;			//四舍五入
	y -= pag;					//算出一列多少字节
	for(i = 0; i < (84 - col); i++)	//多少行数据
	{	
		for(j = 0; j < y; j++)		//每一列数据
		{
			LCD_pos_byte(col + i, pag + j);		//坐标
			LCD_write_dat(img_dat[i * y + j]);	//数据
		}
	}
}


/*--------------------------------------------------------------*/ 
//定位输出数字
//x: 0 - 13
//y: 0 - 5
//num: 0 - 65535	要显示的数字
//num_bit: 0 - 5	数字的位数
void LCD_printn(unsigned char x, unsigned char y, unsigned int num, unsigned char num_bit)
{
	signed   char i;
	unsigned char ii;
	unsigned char dat[6];
	
	for(i = 0; i < 6; i++) dat[i] = 0; 	//初始化数据
	i = 0;
	while(num / 10)						//拆位
	{
		dat[i] = num % 10;				//最低位
		num /= 10; i++;		
	}
	dat[i] = num;						//最高位
	ii = i;								//保存dat的位数
	for(; i >= 0; i--)	dat[i] += 48;	//转化成ASCII
	for(i = 0; i < num_bit; i++)
	LCD_printc(x + i, y, ' ');			//清显示区域
	for(i = ii; i >= 0; i--)
	LCD_printc(x++, y, dat[i]);			//输出数值
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
	




 
