/**************************************************************************
                        PCA9685ģ���Ӧ��
                ƽ̨��STC89C52RC������11.0592
								V+===3.3v-5v
								Vcc====5v
								GND===GND
								SDA===SDA
								SCL===SCL
***************************************************************************/


#include"PCA9685.h"
//#define SERVO_ANGLE0  102 //0�ȶ�Ӧ4096���������ֵ
//#define SERVO_ANGLE180  476 //180�ȶ�Ӧ4096���������ֵ�����ݲ�ͬ����޸�
/**********************����������*********************************/
/*---------------------------------------------------------------
                  ������ʱ����
----------------------------------------------------------------*/
void delayms(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
      for(y=148;y>0;y--);
}
/*---------------------------------------------------------------
                �й�PCA9685ģ��ĺ���
----------------------------------------------------------------*/
/*---------------------------------------------------------------
                ��PCA9685�д��ַ��������
----------------------------------------------------------------*/
void PCA9685_write(uchar address,uchar date)
{
		start();
		write_byte(PCA9685_adrr);        //PCA9685��Ƭѡ��ַ
		ACK();                          
		write_byte(address);  //д��ַ�����ֽ�
		ACK();
		write_byte(date);          //д����
		ACK();
		stop();
}
/*---------------------------------------------------------------
            ��PCA9685��ĵ�ֵַ�С������ݡ�(�з���ֵ)
----------------------------------------------------------------*/
uchar PCA9685_read(uchar address)
{
		uchar date;
		start();
		write_byte(PCA9685_adrr); //PCA9685��Ƭѡ��ַ
		ACK();
		write_byte(address);
		ACK();
		start();
		write_byte(PCA9685_adrr|0x01);        //��ַ�ĵڰ�λ�������������򣬾���д���
		ACK();
		date=read_byte();
		stop();
		return date;
}
/*---------------------------------------------------------------
                        PCA9685����λ��
----------------------------------------------------------------*/
void reset(void) 
{
	PCA9685_write(PCA9685_MODE1,0x0);
}


void begin(void) 
{
	reset();
}
/*---------------------------------------------------------------
                  PCA9685���޸�Ƶ�ʡ�����
----------------------------------------------------------------*/
void setPWMFreq(float freq) 
{
		uint prescale,oldmode,newmode;
		float prescaleval;
		freq *= 0.92;  // Correct for overshoot in the frequency setting 
		prescaleval = 25000000;
		prescaleval /= 4096;
		prescaleval /= freq;
		prescaleval -= 1;
		prescale = floor(prescaleval + 0.5);//����ȡ��
		
		oldmode = PCA9685_read(PCA9685_MODE1);
		newmode = (oldmode&0x7F) | 0x10; // sleep
		PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
		PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
		PCA9685_write(PCA9685_MODE1, oldmode);
		delayms(2);
		PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); 
}
/*---------------------------------------------------------------
                                PCA9685���޸ĽǶȡ�����
num:���PWM�������0~15��on:PWM��������ֵ0~4096,off:PWM�½�����ֵ0~4096
һ��PWM���ڷֳ�4096�ݣ���0��ʼ+1�������Ƶ�onʱ����Ϊ�ߵ�ƽ������������offʱ
����Ϊ�͵�ƽ��ֱ������4096���¿�ʼ�����Ե�on������0ʱ������ʱ,��on����0ʱ��
off/4096��ֵ����PWM��ռ�ձȡ�2^12=4096;
----------------------------------------------------------------*/
void servo_control(uchar num, uchar angle) //num=�ܽź�
{
		uint off = 102.4+2.275555556*angle;//0�ȶ�Ӧ4096���������ֵ
		PCA9685_write(LED0_ON_L+4*num,0);//4=��100��B
		PCA9685_write(LED0_ON_H+4*num,0);
		PCA9685_write(LED0_OFF_L+4*num,off);
		PCA9685_write(LED0_OFF_H+4*num,off>>8);
}


