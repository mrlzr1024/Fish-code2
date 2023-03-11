/*
 * @Author: your name
 * @Date: 2021-11-05 18:51:53
 * @LastEditTime: 2021-11-05 18:57:33
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \串口通信A1\src\main.c
 */
#include<reg52.h>
unsigned char dio(void){
    unsigned char dat;
    while(RI=!0);
    RI=0;
    dat=SBUF;
    return dat;
}
void main(void){
    TMOD=0x20;
    SCON=0x50;
    PCON=0x00;//波特率=9600
    TH1=0xfd;
    TL1=TH0;
    TR1=1;
    REN=1;
    while(1){
        P1=dio();
    }

}