/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	图形库原理:其实就是对一个数组进行操作,数组操作完成之后,直接将整个
	数组刷新到屏幕上
	因此此c文件用于配置oled底层 用于单片机与oled的直接且唯一通信
	
	移植此图形库主要改变以下内容
	SPI_Configuration()	配置通信引脚
	WriteCmd()			写命令
	WriteDat()			写数据
	OledTimeMsFunc()	oled_config中的函数 为系统提供时基
	此例程仅为SPI通信方式 需要更改其他通信方式改好底层上面3个函数大概就行
*/

#include "oled_driver.h"
#include "string.h"


extern SPI_HandleTypeDef hspi2;
#define OLED_SPI hspi2
#define ZK_SPI hspi2

unsigned char OLED_Get_Type(u8 first, u8 second)
{
	unsigned char type = 0;
	if((first>=0xb0)&&(first<=0xf7)&&(second>=0xa1))				type = 1;
		else if((first>=0xa1)&&(first<=0xa3)&&(second>=0xa1))	type = 2;
			else if((first>=0x20)&&(first<=0x7e))								type = 3;
	return type;
}

void OLED_Get_front(u8 first, u8 second, u8 *pbuff, u8 type)
{
	u32 fontaddr=0;
	u8 command[4] = {0x03, 0, 0, 0};
	switch(type)
	{
		case 1:
			fontaddr=(first-0xb0)*94;
			fontaddr+=(second-0xa1)+846;
			fontaddr=fontaddr*32;			
			command[1]=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			command[2]=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			command[3]=(fontaddr&0xff);            //地址的低8位,共24位
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 32, 0xffff);
			ZK_CS_Set();
		break;
		case 2:
			fontaddr=(first-0xa1)*94;
			fontaddr+=(second-0xa1);
			fontaddr=fontaddr*32;		
			command[1]=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			command[2]=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			command[3]=(fontaddr&0xff);            //地址的低8位,共24位
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 32, 0xffff);
			ZK_CS_Set();
		break;
		case 3:
			fontaddr=(first-0x20);
			fontaddr=(unsigned long)(fontaddr*16);
			fontaddr=(unsigned long)(fontaddr+0x3cf80);;			
			command[1]=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			command[2]=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			command[3]=(fontaddr&0xff);            //地址的低8位,共24位
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 16, 0xffff);
			ZK_CS_Set();
		break;
		case 4:
			fontaddr=(first-0x20);
			fontaddr=(unsigned long)(fontaddr*8);
			fontaddr=(unsigned long)(fontaddr+0x3bfc0);
			command[1]=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			command[2]=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			command[3]=(fontaddr&0xff);            //地址的低8位,共24位
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 8, 0xffff);
			ZK_CS_Set();
	}
}

void OLED_WR_Byte(u8 dat,u8 cmd)
{	
			  
	if(cmd) OLED_DC_Set();//写命令
		else	OLED_DC_Clr();
	OLED_CS_Clr();		  
	HAL_SPI_Transmit(&OLED_SPI, &dat, 1, 0x100);		 
	OLED_CS_Set();		    	  
} 

void OLED_WR_Plenty_Dat(u8 *dat,u16 lenth)
{	
			  
	OLED_DC_Set();//写命令

	OLED_CS_Clr();		  
	HAL_SPI_Transmit(&OLED_SPI, dat, lenth, 0x100);		 
	OLED_CS_Set();		    	  
} 


void OLED_FILL(unsigned char BMP[])
{
	u8 i;
	unsigned char *p;
	p=BMP;

	for(i=0;i<8;i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD);		//page0-page1
		OLED_WR_Byte(0x00,	OLED_CMD);			//low column start address
		OLED_WR_Byte(0x10,	OLED_CMD);	
		OLED_WR_Plenty_Dat(p + i * 128,128);
	}
}


void OLED_Init(void)
{
//	OLED_RES_Clr();
//	HAL_Delay(200);
//	OLED_RES_Set();
	
	HAL_Delay(200);
	
  OLED_WR_Byte(0xAE,OLED_CMD); /*display off*/ 
  OLED_WR_Byte(0x00,OLED_CMD); /*set lower column address*/ 
  OLED_WR_Byte(0x10,OLED_CMD); /*set higher column address*/
	OLED_WR_Byte(0xB0,OLED_CMD); /*set page address*/ 
	OLED_WR_Byte(0x40,OLED_CMD); /*set display start lines*/ 
	OLED_WR_Byte(0x81,OLED_CMD); /*contract control*/ 
	OLED_WR_Byte(0x88,OLED_CMD); /*4d*/ 
	OLED_WR_Byte(0x82,OLED_CMD); /* iref resistor set and adjust ISEG*/ 
	OLED_WR_Byte(0x00,OLED_CMD); 
	OLED_WR_Byte(0xA1,OLED_CMD); /*set segment remap 0xA0*/ 
	OLED_WR_Byte(0xA2,OLED_CMD); /*set seg pads hardware configuration*/ 
	OLED_WR_Byte(0xA4,OLED_CMD); /*Disable Entire Display On (0xA4/0xA5)*/ 
	OLED_WR_Byte(0xA6,OLED_CMD); /*normal / reverse*/ 
	OLED_WR_Byte(0xA8,OLED_CMD); /*multiplex ratio*/ 
	OLED_WR_Byte(0x3F,OLED_CMD); /*duty = 1/64*/ 
	OLED_WR_Byte(0xC8,OLED_CMD); /*Com scan direction 0XC0*/ 
	OLED_WR_Byte(0xD3,OLED_CMD); /*set display offset*/ 
	OLED_WR_Byte(0x00,OLED_CMD); /* */ 
	OLED_WR_Byte(0xD5,OLED_CMD); /*set osc division*/ 
	OLED_WR_Byte(0xa0,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); /*set pre-charge period*/ 
	OLED_WR_Byte(0x22,OLED_CMD); 
	OLED_WR_Byte(0xdb,OLED_CMD); /*set vcomh*/ 
	OLED_WR_Byte(0x40,OLED_CMD); 
	OLED_WR_Byte(0x31,OLED_CMD); /* Set pump 7.4v */ 
	OLED_WR_Byte(0xad,OLED_CMD); /*set charge pump enable*/ 
	OLED_WR_Byte(0x8b,OLED_CMD); /*Set DC-DC enable (0x8a=disable; 0x8b=enable) */ 
	OLED_CLS();
	OLED_WR_Byte(0xAF,OLED_CMD);
}


void OLED_CLS(void)//清屏 全部发送0x00
{
	unsigned char m,n[128] = {0};
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,OLED_CMD);		//page0-page1
		OLED_WR_Byte(0x00,	OLED_CMD);			//low  column start address
		OLED_WR_Byte(0x10,	OLED_CMD);			//high column start address
		OLED_WR_Plenty_Dat(n, 128);
	}
}

void OLED_ON(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置电荷泵
	OLED_WR_Byte(0X14,OLED_CMD);  //开启电荷泵
	OLED_WR_Byte(0XAF,OLED_CMD);  //OLED唤醒
}

void OLED_OFF(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置电荷泵
	OLED_WR_Byte(0X10,OLED_CMD);  //关闭电荷泵
	OLED_WR_Byte(0XAE,OLED_CMD);  //OLED休眠
}



