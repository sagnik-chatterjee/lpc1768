/**
 * @Date:   2020-05-04T16:58:30+05:30
 * @Last modified time: 2020-05-04T17:00:34+05:30
 */
/**
*Program to simualte a 8 bit ring counter
*/

#include<LPC17xx.h>
unsigned int i,j,c=1;
unsinged long LED;
int main(void)
{
  LPC_GPIO0->FIODIR |= 0X000000F0;
  while(1)
  {
    for(i=0;i<10000;i++);
    LPC_GPIO0->FIOPIN=c<<4;
    c<<=1;
    if(c==0x80)c=1;
  }
}
