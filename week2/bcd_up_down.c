/**
 * C program for 4 digits BCD up/down 
 * counter on 7 segment display using a 
 * switch and timer with a delay of 1 s 
 * between each count
 */ 


#include <LPC17xx.h>
unsigned int i,i1,j,j1;
unsigned int flag;
unsigned long LED,led1;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR|=0x00000FF0;
	LPC_PINCON->PINSEL4 &=0XFCFFFFFF;
	LPC_GPIO2->FIODIR &=0X0;//|
	
	/*if(LPC_GPIO2->FIOPIN & 1<<12)
		i=4096;
	else
		i=0;*/
	i=0xFF;
	while(1){
	while(LPC_GPIO2->FIOPIN & 1<<12)
	{
		LED=i<<4;
		if(i==0) flag=1;
		else flag=0;
		for(j=0;j<15000;++j);
		LPC_GPIO0->FIOPIN=LED;
		//led1=~i;
		//LPC_GPIO0->FIOCLR=led1;
		--i;
		if(flag==1)
			i=0xFF;
	}
	while(!(LPC_GPIO2->FIOPIN & 1<<12))
	{
		LED=i<<4;
		for(j=0;j<15000;++j);
		LPC_GPIO0->FIOPIN=LED;
		//led1=~i;
		//LPC_GPIO0->FIOCLR=led1;
		++i;
		if(i==0x100)
			i=0;
	}
}
}
