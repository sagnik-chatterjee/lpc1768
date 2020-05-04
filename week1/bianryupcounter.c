/**
 * @Date:   2020-05-04T16:55:11+05:30
 * @Last modified time: 2020-05-04T16:58:12+05:30
 */
/**
*C program to display 8bit binary upcounter on LED
*/

#include <LPC17xx.h>
unsigned int i,j;
unsigned long LED;

int main(void)
{
  LPC_GPIO0->FIODIR |= 0X00000FF0;
  while(1)
  {
    LED=0x00000010;
    for(i=1;i<9;i++)
    {
      LPC_GPIO0->FIOSET =LED;
      for(j=0;j<10000;j++);
      LED<<=1;
    }
    LED=0x00000010;
    for(i=0;i<9;i++)
    {
      LPC_GPIO0->FIOCLR=LED;
      for(j=0;j<10000;j++);
      LED<<=1;
    }
  }
}
