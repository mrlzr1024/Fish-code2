/**************************************************************************
                        PCA9685模块简单应用
                平台：STC89C52RC，晶振：11.0592
								V+===3.3v-5v
								Vcc====5v
								GND===GND
								SDA===SDA
								SCL===SCL
***************************************************************************/


#include"PCA9685.h"
//#define SERVO_ANGLE0  102 //0度对应4096的脉宽计数值
//#define SERVO_ANGLE180  476 //180度对应4096的脉宽计算值，根据不同舵机修改
/**********************函数的声明*********************************/
/*---------------------------------------------------------------
                  毫秒延时函数
----------------------------------------------------------------*/
void delayms(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
      for(y=148;y>0;y--);
}
/*---------------------------------------------------------------
                有关PCA9685模块的函数
----------------------------------------------------------------*/
/*---------------------------------------------------------------
                向PCA9685里【写地址】，数据
----------------------------------------------------------------*/
void PCA9685_write(uchar address,uchar date)
{
		start();
		write_byte(PCA9685_adrr);        //PCA9685的片选地址
		ACK();                          
		write_byte(address);  //写地址控制字节
		ACK();
		write_byte(date);          //写数据
		ACK();
		stop();
}
/*---------------------------------------------------------------
            从PCA9685里的地址值中【读数据】(有返回值)
----------------------------------------------------------------*/
uchar PCA9685_read(uchar address)
{
		uchar date;
		start();
		write_byte(PCA9685_adrr); //PCA9685的片选地址
		ACK();
		write_byte(address);
		ACK();
		start();
		write_byte(PCA9685_adrr|0x01);        //地址的第八位控制数据流方向，就是写或读
		ACK();
		date=read_byte();
		stop();
		return date;
}
/*---------------------------------------------------------------
                        PCA9685【复位】
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
                  PCA9685【修改频率】函数
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
		prescale = floor(prescaleval + 0.5);//向零取整
		
		oldmode = PCA9685_read(PCA9685_MODE1);
		newmode = (oldmode&0x7F) | 0x10; // sleep
		PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
		PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
		PCA9685_write(PCA9685_MODE1, oldmode);
		delayms(2);
		PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); 
}
/*---------------------------------------------------------------
                                PCA9685【修改角度】函数
num:舵机PWM输出引脚0~15，on:PWM上升计数值0~4096,off:PWM下降计数值0~4096
一个PWM周期分成4096份，由0开始+1计数，计到on时跳变为高电平，继续计数到off时
跳变为低电平，直到计满4096重新开始。所以当on不等于0时可作延时,当on等于0时，
off/4096的值就是PWM的占空比。2^12=4096;
----------------------------------------------------------------*/
void servo_control(uchar num, uchar angle) //num=管脚号
{
		uint off = 102.4+2.275555556*angle;//0度对应4096的脉宽计数值
		PCA9685_write(LED0_ON_L+4*num,0);//4=（100）B
		PCA9685_write(LED0_ON_H+4*num,0);
		PCA9685_write(LED0_OFF_L+4*num,off);
		PCA9685_write(LED0_OFF_H+4*num,off>>8);
}


