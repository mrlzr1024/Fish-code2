#include"stm32f10x.h"
void Delay(u32 count)
{
	u32 i=10;
	for(;i<count;i++);
}
int main(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		//1����PB, PE�˿�ʱ��L
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		//LED0-->PB.5 ŵ��ӛ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//I0���� ��Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//��ʼ��GPIOB.5_
		GPIO_SetBits(GPIOB,GPIO_Pin_All);
		//PB.5�����
		GPIO_InitStructure. GPIO_Pin = GPIO_Pin_All;
		//LED1->PB.5�������
//		GPIO_Init (GPIOE, &GPIO_InitStructure) ;
		//��ʼ��GPIO
//		GPIO_SetBits(GPIOE,GPIO_Pin_All);
		//PE.5�����
		while(1)
			{
		GPIO_ResetBits(GPIOB,GPIO_Pin_All);
//		GPIO_SetBits(GPIOE, GPIO_Pin_All);
		Delay(3000000);
		GPIO_SetBits(GPIOB,GPIO_Pin_All);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_All);
		Delay(3000000);
			} 
}


