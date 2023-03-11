#include "JQ8900.h"

int IO_JQ8X00_BusyCheck = 27;        //忙检测IO
int JQ8X00_BusyCheck = 1;     //忙检测，0表示不做忙检测，1表做忙检测

/******************函数定义区**************************/
/************************************************************************
  功能描述：起始码-指令类型-数据长度-数据-校验和
  入口参数：   *DAT：字符串指针,Len字符串长度
  返 回 值： none
  其他说明：
**************************************************************************/
void  JQ8x00_Command_Data(UartCommandData Command, unsigned char DATA)
{
    unsigned char Buffer[6] = {0xaa};
    unsigned char DataLen = 0;         //数据长度
    Buffer[1] = Command;       //指令类型
    if((Command != AppointTrack) && (Command != SetCycleCount) && (Command != SelectTrackNoPlay) && (Command != AppointTimeBack) && (Command != AppointTimeFast))        //只含一个数据指令
    {
        Buffer[2] = 1;      //数据长度
        Buffer[3] = DATA;       //数据
        Buffer[4] = Buffer[0] +  Buffer[1] +  Buffer[2] + Buffer[3];            //校验和
        DataLen = 5;
    }
    else                                                                                        //含两个数据指令
    {
        Buffer[2] = 2;      //数据长度
        Buffer[3] = DATA/256;       //数据
        Buffer[4] = DATA%256;       //数据
        Buffer[5] = Buffer[0] +  Buffer[1] +  Buffer[2] + Buffer[3] + Buffer[4];
        DataLen = 6;
    }
    
    if (JQ8X00_BusyCheck)
    {
        delay(10);
        while (digitalRead(IO_JQ8X00_BusyCheck) == HIGH);     //忙检测
    }
    
    Serial2.write(Buffer, DataLen);
}

/************************************************************************
  功能描述：播放根目录指定文件名的音频文件
  入口参数：JQ8X00_Symbol:系统盘符，*DATA:需要播放的文件名
  返 回 值： none
  其他说明：播放FLASH根目录下文件名为00001.mp3的音频，JQ_8x00_AppointPlay(JQ8X00_FLASH,"00001");
**************************************************************************/
void JQ8x00_AppointPlay(JQ8X00_Symbol MODE, char *DATA)
{
    unsigned char Buffer[30] = {0xaa, 0x08};
    unsigned char i, j;
    Buffer[2] = 1 + strlen(DATA) + 5;       //长度
    Buffer[3] = MODE;        //盘符
    Buffer[4] = '/';        //路径
    i = 5;
    while (*DATA)
    {
        Buffer[i++] =  *DATA;
        DATA++;
    }
    Buffer[i++] = '*';
    Buffer[i++] = '?';
    Buffer[i++] = '?';
    Buffer[i++] = '?';
    for (j = 0; j < i; j++)
    {
        Buffer[i] = Buffer[i] + Buffer[j];      //计算校验合
    }
    i++;

    if (JQ8X00_BusyCheck)
    {
        delay(10);
        while (digitalRead(IO_JQ8X00_BusyCheck) == HIGH);     //忙检测
    }
    
    Serial2.write(Buffer, i);
}

/************************************************************************
  功能描述：组合播报函数
  入口参数：   *DAT：字符串指针,Len字符串长度
  返 回 值： none
  其他说明： 将需要播报的文件名放入数组中作为形参即可,例：组合播放01,02文件，则DATA内容为[1, 2](int数组)，JQ8x00_ZuHeBoFang（DATA，2）
**************************************************************************/
void  JQ8x00_ZuHeBoFang(unsigned char *DATA, unsigned char Len)
{
    unsigned char CRC_data = 0, i = 3;
    unsigned char Buffer[30] = {0xaa, 0x1b};

    Buffer[2] = Len * 2;    //计算长度
    CRC_data = CRC_data + 0xaa + 0x1b + Buffer[2];
    while (Len--)
    {
        Buffer[i] = *DATA / 10 + 0x30;  //取出十位
        CRC_data = CRC_data + Buffer[i];
        i++;
        Buffer[i] = *DATA % 10 + 0x30;  //取出个位
        CRC_data = CRC_data + Buffer[i];
        i++;
        DATA++;
    }
    Buffer[i] = CRC_data;
    i++;

    if (JQ8X00_BusyCheck)
    {
        delay(10);
        while (digitalRead(IO_JQ8X00_BusyCheck) == HIGH);     //忙检测
    }
    
    Serial2.write(Buffer, i);
}
