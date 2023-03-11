#include<reg52.h>
sbit P2_0 = P2^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P2_1 = P2^1;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
void main()
{
	while(1)
	{
		if(P2_0 == 0)
		{
  				P1_1=0;
				P1_2=1;
 		}
 		 else if (P2_0 ==1)
		 {
				P1_1=1;
				P1_2=0;			 
		  }
		  if(P2_1 == 0)
		{
  				P1_3=0;
				P1_4=1;
 		}
 		 else if (P2_1 ==1)
		 {
				P1_3=1;
				P1_4=0;			 
		  }
	 }
 }
  

