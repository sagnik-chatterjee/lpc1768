/**
 * @Date:   2020-05-03T17:14:47+05:30
 * @Last modified time: 2020-05-04T16:51:53+05:30
 */



/**
 * Program to simulate a 8bit ring counter using key press (sw2)
*/

#include <LPC17xx.h>
unsigned int i,c ;
int main(void)
{
	LPC_PINCON->PINSEL0 &=0xff0000ff;
	LPC_GPIO0->FIODIR |=0X00000FF0;

	LPC_GPIO2->FIODIR =0;
	c=1;
	while(1)
	{
		if(c==0X100)
		{
			c=1;
		}
		LPC_GPIO0->FIOPIN =c<<4;
		for(i=0;i<50000;i++);
		if(!(LPC_GPIO2->FIOPIN & 1<<12))c*=2;
	}
}
