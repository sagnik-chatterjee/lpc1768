/**
 * Program to simulate a 8bit ring counter
*/

#include <LPC17xx.h>
unsigned int i,j, c=1;
unsigned long LED;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	//LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR|=0x00000FF0;
	LPC_GPIO2->FIODIR|=0x0;
	while(1)
	{
		if(LPC_GPIO2->FIOPIN & 1<<12)
		{
			for(i=0;i<30000;i++);
			LPC_GPIO0->FIOPIN=c<<4;
			c<<=1;
			if(c==0x100)
				c=1;
		}
		else
		{
			for(i=0;i<30000;i++);
			LPC_GPIO0->FIOPIN=c<<4;
			c>>=1;
			if(c==0x00)
				c=0x100;
		}
	}
}

