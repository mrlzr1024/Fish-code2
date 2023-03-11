#include "at24c02.h"
#include "i2cB.h"

/*******************************************************************************
* �� �� ��         : void At24c02Write(unsigned char addr,unsigned char dat)
* ��������         : ��24c02��һ����ַд��һ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
    I2C_Start();
    I2C_SendByte(0xa0, 1);//����д������ַ
    I2C_SendByte(addr, 1);//����Ҫд���ڴ��ַ
    I2C_SendByte(dat, 0);   //��������
    I2C_Stop();
}
/*******************************************************************************
* �� �� ��         : unsigned char At24c02Read(unsigned char addr)
* ��������         : ��ȡ24c02��һ����ַ��һ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
    unsigned char num;
    I2C_Start();
    I2C_SendByte(0xa0, 1); //����д������ַ
    I2C_SendByte(addr, 1); //����Ҫ��ȡ�ĵ�ַ
    I2C_Start();
    I2C_SendByte(0xa1, 1); //���Ͷ�������ַ
    num=I2C_ReadByte(); //��ȡ����
    I2C_Stop();
    return num; 
}

