/*
 * @Author: your name
 * @Date: 2021-12-10 07:57:51
 * @LastEditTime: 2021-12-10 08:13:18
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \工程文件Project\RADMain.c
 */
/*************************************************************************************

*
实验现象：下载程序后，数码管显示红外遥控键值数据

接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->红外接收模块
				P32-->J11
		   2，单片机-->动态数码管模块
				J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)

注意事项：红外遥控器上的电池绝缘隔片要拿掉


**************************************************************************************

*/

#include "reg52.h" //此文件中定义了单片机的一些特殊功能寄存器
#include "redmod.h"

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 DisplayData[8];
u8 code smgduan[17] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0X76};
// 0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F、H的显示码

/*******************************************************************************
 * 函 数 名         : delay
 * 函数功能		   : 延时函数，i=1时，大约延时10us
 *******************************************************************************/
void delay(u16 i)
{
	while (i--)
		;
}

/*******************************************************************************
 * 函数名         :DigDisplay()
 * 函数功能		 :数码管显示函数
 * 输入           : 无
 * 输出         	 : 无
 *******************************************************************************/
void DigDisplay()
{
	u8 i;
	for (i = 0; i < 3; i++)
	{
		switch (i) //位选，选择点亮的数码管，
		{
		case (0):
			LSA = 1;
			LSB = 1;
			LSC = 1;
			break; //显示第0位
		case (1):
			LSA = 0;
			LSB = 1;
			LSC = 1;
			break; //显示第1位
		case (2):
			LSA = 1;
			LSB = 0;
			LSC = 1;
			break; //显示第2位
		}
		P0 = DisplayData[i]; //发送数据
		delay(100);			 //间隔一段时间扫描
		P0 = 0x00;			 //消隐
	}
}

/*******************************************************************************
 * 函 数 名       : main
 * 函数功能		 : 主函数
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void main()
{
	IrInit();
	while (1)
	{
		DisplayData[0] = smgduan[IrValue[2] / 16];
		DisplayData[1] = smgduan[IrValue[2] % 16];
		DisplayData[2] = smgduan[16];
		DigDisplay();
	}
}
