/**
 * Die tossing on LCD and interrupt using SW2
 */

#include <LPC17xx.h>
#include "lcd_disp.c"
#include <stdio.h>
#include <stdlib.h>

void scan(void);

unsigned char Msg1[13]={"RANDOM"};
unsigned char row,var,flag,key;
unsigned long int i,var1,temp,temp1,temp2,temp3;

unsigned char ASCII_CODE[6]={'6','1','2','3','4','5'};

int main(void)
{
    lcd_init();
    while(1)
    {
        while(LPC_GPIO2->FIOPIN & 1<<2==0 )
        {
            temp1=0x80;
            lcd_com();
            delay_lcd(80000);
            key=rand()%6;
            key=ASCII_CODE[key];
            lcd_puts(key);
        }
    }
}