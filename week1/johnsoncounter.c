/**
 * @Date:   2020-05-04T16:46:33+05:30
 * @Last modified time: 2020-05-04T16:48:44+05:30
 */
/**Program to simualte a 8bit Johnson counter
*/

#include <LPC17xx.h>
unsigned int i,j,c=0;
unsigned long LED;

int main(void)
{
  LPC_GPIO0->FIODIR |= 0X00000FF0;
  while(1)
  {
    c++;
    LPC_GPIO0->FIOPIN = c<<4;
    for(i=0;i<30000;i++);
    if(c==0XFF)
    {
      c=0;
    }
  }
}
