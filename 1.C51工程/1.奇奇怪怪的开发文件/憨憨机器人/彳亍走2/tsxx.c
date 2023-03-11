#include<reg51.h>
sbit p1_0=P1^0;
void main(void)
{
while(1){
	p1_0=1;
}
}