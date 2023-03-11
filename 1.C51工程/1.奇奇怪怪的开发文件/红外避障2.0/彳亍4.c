#include <reg52.h>

//�����������l298nģ��������뵥Ƭ����������
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit IN3 = P1^2;
sbit IN4 = P1^3;

//�������ģ��
sbit out1 = P2^0;
sbit out2 = P1^6;


/*��������*/
void go();			//ǰ��
void back();		//����
void left();		//����
void right();		//����
void stop();		//ֹͣ


void main()
{
	
	while(1)
	{
		if(out2 == 0)											//��⵽�ұ����ϰ���ʱ�������ƶ�
		{
			left();
		}
		else if(out1 == 0)								//��⵽��߱����ϰ���ʱ�������ƶ�
		{
			right();
		}
		else if(out1 == 1 && out2 == 1)		//��⵽��û�����ϰ���ʱ����ǰ�ƶ�
		{
			go();
		}
	}
}

//ǰ��
void go()
{
	IN1=1; 
	IN2=0; 
	IN3=1; 
	IN4=0;
}

//����
void back()
{
	IN1=0; 
	IN2=1; 
	IN3=0; 
	IN4=1;
}

//����
void left()
{
	IN1=0; 
	IN2=0; 
	IN3=0; 
	IN4=1;
}

//����
void right()
{
	IN1=1; 
	IN2=1; 
	IN3=1; 
	IN4=0;
}

//ֹͣ
void stop()
{
	IN1=0; 
	IN2=0; 
	IN3=0; 
	IN4=0;
}

