/*
 * @Author: your name
 * @Date: 2019-09-10 10:33:36
 * @LastEditTime: 2021-12-05 17:04:23
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USERc:\Users\��֥��\Desktop\��������\����������ͼ���\������ԭ�ӡ�STM32F103��Сϵͳ������\4������Դ��\1����׼����-�Ĵ����汾\ʵ��3 ����ʵ��\HARDWARE\LED\led.h
 */
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//LED�˿ڶ���
#define LED0 PBout(5)	// DS0
#define LED1 PEout(5)	// DS1	

void LED_Init(void);	//��ʼ��		 				    
#endif

















