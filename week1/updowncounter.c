/**
 * @Date:   2020-05-04T16:52:09+05:30
 * @Last modified time: 2020-05-04T16:54:53+05:30
 */
/**
*Simulate working of up/down counter using sw2
*/
#include <LPC17xx.h>
unsigned int i,j;
int c=0;

unsigned long LED=0x00000010;
int main(void)
{
  LPC_PINCON->PINSEL0 &=0xff0000ff;
  LPC_GPIO0->FIODIR |= 0X00000FF0;
  LPC_GPIO1->FIODIR =0;

  while(1)
  {
    if(LPC_GPIO2->FIOPIN &1<<12)
    {
      c++;
    }
    else c--;
    if(c==-1)c=0xff;
    if(c==0x100)c=0;

    LPC_GPIO0->FIOPIN=c<<4;
    for(j=0;j<50000;j++);
  }
}
