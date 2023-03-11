#include<main.h>
void main(void){
A=1;
C=1;
init();
write_com(0x38 );
write_com(0x0E);
write_com(0x06);
write_com(0x80 );
delay(6);
write_data('E');
delay(20);
while(1)
;}