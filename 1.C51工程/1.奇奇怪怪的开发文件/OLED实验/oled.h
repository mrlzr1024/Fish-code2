/**********************************************************************************
 * ������:    SSD1306��������	
 * ����:      DaveoCKII			
 * ����:      2020.3.12			
 * �汾:      STC12C5A60S2 		
 **********************************************************************************/

#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <STC12C5A60S3.H>
//------------------------------------�����б�------------------------------------//
sbit SCL = P3^4;	// ʱ����
sbit SDA = P3^3;	// ������
//------------------------------------�����б�------------------------------------//
void OLED_Init(void);						// OLED ��ʼ��
void OLED_Clear(void);						// OLED ����
void OLED_WriteCmd(unsigned char cmd);		// OLED ����д����
void OLED_WriteDat(unsigned char dat);		// OLED ����д����
void OLED_WriteC(unsigned char cmd);		// OLED ����д����	�ڽ�βҪ����IIC_STOP();
void OLED_WriteD(unsigned char dat);		// OLED ����д����	�ڽ�βҪ����IIC_STOP();
void OLED_Frame(unsigned char P[8][128]);	// OLED һ֡ͼ��д��
//------------------------------------�ڲ�����------------------------------------//
static void IIC_START(void);				// IIC_��ʼ�ź�	(�ؿ�ʼ�ź��ô����)
static void IIC_STOP(void); 				// IIC_�����ź�
static unsigned char IIC_WaitACK(void);		// IIC_�ȴ�Ӧ��		����ֵ: 0:NACK 1:ACK 
static void IIC_Write(unsigned char dat);	// IIC_д���ݺ���	����:Ҫд�������
static unsigned char IIC_Read(void);		// IIC_�����ݺ���	����ֵ:����������
static void delay1us(void);					// ��ʱ1us    
//------------------------------------��������------------------------------------//

void OLED_WriteD(unsigned char dat)
{
	IIC_START();		// ͨ�ſ�ʼ
	IIC_Write(0X78);	// д�ӻ���ַ'0111 100' ��д����'0'
	IIC_WaitACK();
	IIC_Write(0X40);	// д���� Co='0' C/D='100 0000'
	IIC_WaitACK();
	IIC_Write(dat);		// д������
	IIC_WaitACK();
}

void OLED_WriteC(unsigned char cmd)
{
	IIC_START();		// ͨ�ſ�ʼ
	IIC_Write(0X78);	// д�ӻ���ַ'0111 100' ��д����'0'
	IIC_WaitACK();
	IIC_Write(0X00);	// д���� Co='0' C/D='000 0000'
	IIC_WaitACK();
	IIC_Write(cmd);		// д������
	IIC_WaitACK();
}

void OLED_WriteDat(unsigned char dat)
{
	OLED_WriteD(dat);
	IIC_STOP();			// ͨ�Ž���
}

void OLED_WriteCmd(unsigned char cmd)
{
	OLED_WriteC(cmd);
	IIC_STOP();			// ͨ�Ž���
}

void OLED_Init(void)
{	
	OLED_WriteC(0XAE);		// ��OLED��ʾ
	// ��������
	OLED_WriteC(0XA4);		// ���GDDRAM����	
	OLED_WriteC(0XA6);		// ������ʾ(1��0��)	
	OLED_WriteC(0X81);		// ���öԱȶ�		
	OLED_WriteC(0X7F);		// ��127���Աȶ�	
	// COM��SEG�������
	OLED_WriteC(0XD3);		// ���ô�ֱ��ʾƫ��(����)
	OLED_WriteC(0X00);		// ƫ��0��					
	OLED_WriteC(0X40);		// ����GDDRAM��ʼ�� 0		
	OLED_WriteC(0XA8);		// ����MUX�� (��ʾ����)		
	OLED_WriteC(0X3F);		//  MUX=63	 (��ʾ63��)			
	OLED_WriteC(0XA1);		// ���ҷ��ù�(����ӳ��)		
	OLED_WriteC(0XC8);		// ���·��ù�(����ӳ��)		
	OLED_WriteC(0XDA);		// ����COM��������		
	OLED_WriteC(0X02);		// ����COM����,�������ҷ���
	// ʱ������
	OLED_WriteC(0XD5);		// ����DCLK��Ƶ��OSCƵ��
	OLED_WriteC(0X80);		// �޷�Ƶ,��8��OSCƵ��	
	// ��OLED
	OLED_WriteC(0X8D);		// ���õ�ɱ�
	OLED_WriteC(0X14);		// ���õ�ɱ�
	OLED_WriteC(0XAF);		// ��OLED��ʾ
	
	IIC_STOP();
}

void OLED_Clear(void)
{
	unsigned char i,j;
	
	OLED_WriteC(0X00);		// ˮƽѰַģʽ 
	OLED_WriteC(0X21);		// ��������ʼ�ͽ�����ַ
	OLED_WriteC(0X00);		// ����ʼ��ַ 0
	OLED_WriteC(0X7F);		// ����ֹ��ַ 127
	OLED_WriteC(0X22);		// ����ҳ��ʼ�ͽ�����ַ
	OLED_WriteC(0X00);		// ҳ��ʼ��ַ 0
	OLED_WriteC(0X07);		// ҳ��ֹ��ַ 7
	
	for(i=0; i<8; i++)		// д��һ֡'0'
		for(j=0; j<128; j++)
			OLED_WriteD(0X00);
	
	IIC_STOP();
}

void OLED_Frame(unsigned char P[8][128])
{
	unsigned char i,j;
	
	OLED_WriteC(0X20);	// ����GDDRAMģʽ
	OLED_WriteC(0X00);	// ˮƽѰַģʽ 
	OLED_WriteC(0X21);	// ��������ʼ�ͽ�����ַ
	OLED_WriteC(0X00);	// ����ʼ��ַ 0
	OLED_WriteC(0X7F);	// ����ֹ��ַ 127
	OLED_WriteC(0X22);	// ����ҳ��ʼ�ͽ�����ַ
	OLED_WriteC(0X00);	// ҳ��ʼ��ַ 0
	OLED_WriteC(0X07);	// ҳ��ֹ��ַ 7
	
	for(i=0; i<8; i++)		// д��һ֡����
		for(j=0; j<128; j++)
			OLED_WriteDat(P[i][j]);
	
	IIC_STOP();
}

//----------------------------------�ڲ���������-----------------------------------//

static void IIC_START(void)
{
	SCL = 0;		// SCL���� ��ֹ���ܳ��ֵĸ�������
	delay1us();
	SDA = 1;		// SDA���� 
	SCL = 1;		// SCL���� ׼��������ʼ�ź�
	delay1us();		
	SDA = 0;		// SDA���� ������ʼ�ź�
	SCL = 0;		// SCL���� ��ʼ����
}

static void IIC_STOP(void)
{
	SCL = 0;		// SCL���� ��ֹ���ܳ��ֵĸ�������
	SDA = 0;		// SDA����
	SCL = 1;		// SCL���� ׼�����������ź�
	delay1us();		
	SDA = 1;		// SDA���� ���������ź�
}

static unsigned char IIC_WaitACK(void)
{
	bit s;
	SCL = 0;		// ����SCL
	delay1us();
	SDA = 1;		// ����SDA �����ͷ�����
	delay1us();
	SCL = 1;		// ����SCL 
	delay1us();		
	s = SDA;		// �ɼ�SDA�ź���״̬
	delay1us();		
	SCL = 0;		// ����SCL ����ѯ��ACK
	if(s)
		return 0;	// ��Ӧ��(ACK)
	else
		return 1;	// ��Ӧ��(ACK)	
}

static void IIC_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0; i<8; i++) 
	{
		SCL = 0; 			// ����SCL ׼��д����
		SDA = dat & 0X80;	// д����
		dat <<= 1;			// ���ݸ�ʽ:��λ��ǰ
		SCL = 1;			// ����SCL ��������
		delay1us();
		SCL = 0;			// ����SCL ��������
	}
}

static void delay1us(void)
{	

}

//---------------------------------------------------------------------------------//
//------------------------------------�������--------------------------------------//
//---------------------------------------------------------------------------------//

#endif
