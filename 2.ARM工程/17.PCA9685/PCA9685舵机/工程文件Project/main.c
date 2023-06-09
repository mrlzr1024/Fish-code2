/**************************************************************************
                        PCA9685模块简单应用
                平台：STC89C52RC，晶振：11.0592
								V+===3.3v-5v
								Vcc====5v
								GND===GND
								SDA===SDA
								SCL===SCL
***************************************************************************/
#include"main.h"
/*---------------------------------------------------------------
                      主函数
----------------------------------------------------------------*/
void main()
{
		uint i,j;
		init();
		begin();
		setPWMFreq(50);  
		/*//例如要求舵机转到x度，这么算，x度对应的脉宽=0.5ms+(x/180)*(2.5ms-0.5ms)=1.1666ms(x=60)
		//利用占空比=1.1666ms/20ms=off/4096,off=239,50hz对应周期20ms
		//setPWM(num,0,239);;;;当然也可以利用SERVO000和SERVO180计算*/
		while(1) 
		{
				for(i=0;i<=180;i+=10)
				{
						servo_control(1,i);//num为管脚号
						delayms(10);
					for(j=0;j<=90;j++){
						servo_control(0,j);//num为管脚号
						delayms(10);
					}
				}
		}                
}
