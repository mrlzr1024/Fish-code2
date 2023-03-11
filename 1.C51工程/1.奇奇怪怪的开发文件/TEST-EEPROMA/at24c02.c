#include "at24c02.h"
#include "i2cB.h"

/*******************************************************************************
* 函 数 名         : void At24c02Write(unsigned char addr,unsigned char dat)
* 函数功能         : 往24c02的一个地址写入一个数据
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
    I2C_Start();
    I2C_SendByte(0xa0, 1);//发送写器件地址
    I2C_SendByte(addr, 1);//发送要写入内存地址
    I2C_SendByte(dat, 0);   //发送数据
    I2C_Stop();
}
/*******************************************************************************
* 函 数 名         : unsigned char At24c02Read(unsigned char addr)
* 函数功能         : 读取24c02的一个地址的一个数据
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
    unsigned char num;
    I2C_Start();
    I2C_SendByte(0xa0, 1); //发送写器件地址
    I2C_SendByte(addr, 1); //发送要读取的地址
    I2C_Start();
    I2C_SendByte(0xa1, 1); //发送读器件地址
    num=I2C_ReadByte(); //读取数据
    I2C_Stop();
    return num; 
}

