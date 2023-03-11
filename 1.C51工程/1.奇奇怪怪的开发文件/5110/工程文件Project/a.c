#include<stdio.h>
#include"spi.h"
#include<reg52.h>
#include<malloc.h>
struct body {
	int x;
	int y;
	struct  body* next;
};
struct body* creat(int i) {
	struct body* head;
	struct body* piont;
	struct body* piont2;
	//piont = (struct body*)malloc(sizeof(struct body));
	head = (struct body*)malloc(sizeof(struct body));
	piont = (struct body*)malloc(sizeof(struct body));
	head->x = 9;
	head->y = 8;
	head->next = piont;
	while (i>=0) {
		piont2 = (struct body*)malloc(sizeof(struct body));
		piont->next = piont2;
		i--;
		if (i <= 0) { piont2->next = NULL; break; }
		piont = (struct body*)malloc(sizeof(struct body));
		piont2->next = piont;
		i--;
		if (i <= 0) { piont->next = NULL; break; }
	}
	piont = head;
	return piont;
}
void change(body* unch,int i) {//change from head,not include head
	int h = 0;
	struct body *c_piont=unch;
	while (i > 0) {
		c_piont = c_piont->next;
		i--;
	}
}
void display(body* unch) {
	int tempx=0,tempy=0;
	struct body *c_piont1 ;
	c_piont1 = unch;
	/*tempx = c_piont1->x;
	tempy = c_piont1->y;*/
	while (c_piont1 != NULL) {
		tempx = c_piont1->x;
		tempy = c_piont1->y;
		cout<< c_piont1->x;
		cout<< c_piont1->y;
		c_piont1 = c_piont1->next;
		c_piont1->x = tempx;
		c_piont1->y = tempy;
	}
}
//void main(void) {
//	struct body* lunch;
//	struct body* dinner;
//	lunch=creat(10);
//	display(lunch);
//}