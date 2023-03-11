/*
 * @Author: your name
 * @Date: 2022-03-26 10:59:25
 * @LastEditTime: 2022-03-26 12:19:50
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\Car.c
 */
#include "Car.h"
int pin_A=0;
int pin_B=0;
int pin_C=0;
int pin_D=0;
void Init_Car(int pin_a, int pin_b, int pin_c, int pin_d)
{
	pin_A=pin_a;
	pin_B=pin_b;
	pin_C=pin_c;
	pin_D=pin_d;
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_a], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_b], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_c], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_d], F_50MHZ);
	LZR_GPIO_OUT(RC, GPIOC, LZR_PIN[13], F_50MHZ);
}
void forward(void){
	PBout(pin_A)=1;	
	PBout(pin_B)=0;
	PBout(pin_C)=1;
	PBout(pin_D)=0;
}
void left(void){
	PBout(pin_A)=0;
	PBout(pin_B)=1;
	PBout(pin_C)=1;
	PBout(pin_D)=0;
}
void right(void){
	PBout(pin_A)=1;
	PBout(pin_B)=0;
	PBout(pin_C)=0;
	PBout(pin_D)=1;
}
void back(void){
	PBout(pin_A)=0;
	PBout(pin_B)=1;
	PBout(pin_C)=0;
	PBout(pin_D)=1;
}
void stop(void){
	PBout(pin_A)=0;
	PBout(pin_B)=0;
	PBout(pin_C)=0;
	PBout(pin_D)=0;
}
