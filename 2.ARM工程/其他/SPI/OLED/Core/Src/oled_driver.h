#ifndef __OLED_DRIVER_H
#define	__OLED_DRIVER_H

#include "main.h"
#include "oled_config.h"
#include "oled_basic.h"

//-----------------OLED端口定义----------------  					   
#define OLED_CS_Clr()			HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()			HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET)
#define OLED_DC_Clr()			HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)//DC
#define OLED_DC_Set()			HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)
//#define OLED_RES_Clr()		HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_RESET)//CS
//#define OLED_RES_Set()		HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_SET)
//-----------------字库端口定义---------------- 
#define ZK_CS_Clr()     HAL_GPIO_WritePin(ZK_CS_GPIO_Port, ZK_CS_Pin, GPIO_PIN_RESET)//CS2
#define ZK_CS_Set()     HAL_GPIO_WritePin(ZK_CS_GPIO_Port, ZK_CS_Pin, GPIO_PIN_SET)

//#define OLED_RST    PBout(10) //RS
//#define OLED_RS 	  PBout(13) //DC
//#define OLED_SCLK 	PBout(14) //D0 
//#define OLED_SDIN 	PBout(12) //D1

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//void I2C_Configuration(void);
//void I2C_WriteByte(uint8_t addr,uint8_t data);
//void SPI_Configuration(void);
unsigned char OLED_Get_Type(u8 first, u8 second);
void OLED_Get_front(u8 first, u8 second, u8 *pbuff, u8 type);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_WR_Plenty_Dat(u8 *dat,u16 lenth);
void OLED_Init(void);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_FILL(unsigned char BMP[]);

#endif

