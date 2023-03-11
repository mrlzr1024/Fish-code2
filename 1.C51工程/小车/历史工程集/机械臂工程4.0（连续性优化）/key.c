#include"key.h"
/***************************************************
 * 函数名称：key
 * 入口参数：无
 * 输出：无
 * 功能：识别KEY0,KEY1
 * 备注：阻滞性识别
 * *************************************************/
int key(void)
{
    while(key0==1&&key1==1)
        ;
    if (key0 == 0)
    {
        return 1;
    }
    else if (key1 == 0)
    {
        return 2;
    }
    return 0;
}
/***************************************************
 * 函数名称：key_continue
 * 入口参数：无
 * 输出：无
 * 功能：识别KEY0,KEY1
 * 备注：连续性识别
 * *************************************************/
int key_continue(void)
{
    if (key0 == 0)
    {
        return 1;
    }
    else if (key1 == 0)
    {
        return 2;
    }
    return 0;
}
/***************************************************
 * 函数名称：key4x4
 * 入口参数：无
 * 输出：无
 * 功能：识别4x4矩阵按键
* 备注：连续性识别,以左下角为原点
 * *************************************************/
int key4x4(void){
  int val=0;
  KEY = 0xf0;//1111 0000
	if(KEY!=0xf0)
	{
		switch(KEY)     //行扫描
		{
			case 0xe0://1110 0000(4,4)
				val = 0; break;	
			case 0xd0://1101 0000(3,4)
				val = 1; break;	
			case 0xb0://1011 0000(2,4)
				val = 2; break;
			case 0x70://0111 0000(1,4)
				val = 3; break;
		}	
		KEY = 0x0f;
		switch(KEY)       //列扫描
		{
			case 0x0e:
				val += 0; break;	
			case 0x0d:
				val += 4; break;	
			case 0x0b:
				val += 8; break;
			case 0x07:
				val += 12; break;
		}
		if(val==7||val==6||val==8){
		while(KEY!=0x0f);   //等待按键松开
		}
    return val;
	}
  return -1;
}