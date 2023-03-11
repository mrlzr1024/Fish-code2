/*
	ԭ������������:							MjGame 		https://space.bilibili.com/38673747
	ͬGifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	��������ע��ɾ�������Ż��� ��������:	һֻ����Ե	https://space.bilibili.com/237304109
	����֮ǰ��ԭ�����汾����һͬ�ṩ,���������ַ��ȡ���������Ϣ,������������ԭ��ͬ��,��лԭ��
	
	ͼ�ο�ԭ��:��ʵ���Ƕ�һ��������в���,����������֮��,ֱ�ӽ�����
	����ˢ�µ���Ļ��
	��˴�c�ļ���������oled�ײ� ���ڵ�Ƭ����oled��ֱ����Ψһͨ��
	
	��ֲ��ͼ�ο���Ҫ�ı���������
	SPI_Configuration()	����ͨ������
	WriteCmd()			д����
	WriteDat()			д����
	OledTimeMsFunc()	oled_config�еĺ��� Ϊϵͳ�ṩʱ��
	�����̽�ΪSPIͨ�ŷ�ʽ ��Ҫ��������ͨ�ŷ�ʽ�ĺõײ�����3��������ž���
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
			command[1]=(fontaddr&0xff0000)>>16;   //��ַ�ĸ�8λ,��24λ
			command[2]=(fontaddr&0xff00)>>8;       //��ַ����8λ,��24λ
			command[3]=(fontaddr&0xff);            //��ַ�ĵ�8λ,��24λ
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 32, 0xffff);
			ZK_CS_Set();
		break;
		case 2:
			fontaddr=(first-0xa1)*94;
			fontaddr+=(second-0xa1);
			fontaddr=fontaddr*32;		
			command[1]=(fontaddr&0xff0000)>>16;   //��ַ�ĸ�8λ,��24λ
			command[2]=(fontaddr&0xff00)>>8;       //��ַ����8λ,��24λ
			command[3]=(fontaddr&0xff);            //��ַ�ĵ�8λ,��24λ
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 32, 0xffff);
			ZK_CS_Set();
		break;
		case 3:
			fontaddr=(first-0x20);
			fontaddr=(unsigned long)(fontaddr*16);
			fontaddr=(unsigned long)(fontaddr+0x3cf80);;			
			command[1]=(fontaddr&0xff0000)>>16;   //��ַ�ĸ�8λ,��24λ
			command[2]=(fontaddr&0xff00)>>8;       //��ַ����8λ,��24λ
			command[3]=(fontaddr&0xff);            //��ַ�ĵ�8λ,��24λ
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 16, 0xffff);
			ZK_CS_Set();
		break;
		case 4:
			fontaddr=(first-0x20);
			fontaddr=(unsigned long)(fontaddr*8);
			fontaddr=(unsigned long)(fontaddr+0x3bfc0);
			command[1]=(fontaddr&0xff0000)>>16;   //��ַ�ĸ�8λ,��24λ
			command[2]=(fontaddr&0xff00)>>8;       //��ַ����8λ,��24λ
			command[3]=(fontaddr&0xff);            //��ַ�ĵ�8λ,��24λ
			ZK_CS_Clr();
			HAL_SPI_Transmit(&ZK_SPI, command, 4, 0xffff);			
			HAL_SPI_Receive(&ZK_SPI, pbuff, 8, 0xffff);
			ZK_CS_Set();
	}
}

void OLED_WR_Byte(u8 dat,u8 cmd)
{	
			  
	if(cmd) OLED_DC_Set();//д����
		else	OLED_DC_Clr();
	OLED_CS_Clr();		  
	HAL_SPI_Transmit(&OLED_SPI, &dat, 1, 0x100);		 
	OLED_CS_Set();		    	  
} 

void OLED_WR_Plenty_Dat(u8 *dat,u16 lenth)
{	
			  
	OLED_DC_Set();//д����

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


void OLED_CLS(void)//���� ȫ������0x00
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
	OLED_WR_Byte(0X8D,OLED_CMD);  //���õ�ɱ�
	OLED_WR_Byte(0X14,OLED_CMD);  //������ɱ�
	OLED_WR_Byte(0XAF,OLED_CMD);  //OLED����
}

void OLED_OFF(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //���õ�ɱ�
	OLED_WR_Byte(0X10,OLED_CMD);  //�رյ�ɱ�
	OLED_WR_Byte(0XAE,OLED_CMD);  //OLED����
}



