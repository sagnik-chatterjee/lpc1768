/**
 * Program to read a key from the matrix 
 * keyboard and display its key code on the lcd
 */ 

#include <LPC17xx.h>
#include "lcd_disp.c"

void scan(void)
{
    temp3 =LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000;
    if(temp3!=0)
    {
        flag=1;
        temp3>>=19;
        temp>>=10;
        key=temp3 | temp;
    }
}

unsigned char Msg1[13]={"KEY PRESSED"};
unsigned char row,var,flag,key;

unsigned long int i,var1,temp,temp1,temp2,temp3;

unsigned char SCANCODE[16]={0x11,0x21,0x41,
0x81,0x12,0x22,0x42,0x82,0x14,0x24,0x44,0x84,0x18
,0x28,0x48,0x88};

unsigned char ASCII_CODE[16]={'0','1','2','3'
,'4','5','6','7','8','9','A','B','C','D','E','F'};

unsigned char* b1;

int main(void)
{
    LPC_GPIO2->FIODIR |= 0X00003C00;
    LPC_GPIO1->FIODIR &=0XF87FFFFF;

    lcd_init();
    temp1=0x80;
    lcd_com();
    delay_lcd(800);
    lcd_puts(Msg1);

    while(1)
    {
        while(1)
        {
            for(row=1;row<5;row++)
            {
                    if(row==1)
                    {
                        var1=0x00000400;
                    }
                    else if(row==2)
                    {
                        var1=0x00000800;
                    }
                    else if(row==3)
                    {
                        var1=0x00001000;
                    }
                    else if(row==4)
                    {
                        var1=0x00002000;
                    }
            }
        }  
         temp =var1;
         LPC_GPIO2->FIOCLR=0X00003C00;
         LPC_GPIO2->FIOSET=var1;

         flag=0;
         scan();
         if(flag==1)
          {
             break;
          }
         if(flag==1)
          {
             break;
          }
        for(i=0;i<16;i++)
        {
            if(key==SCANCODE[i])
            {
                key=ASCII_CODE[i];
                break;
            }
        }
        temp1=0xc0;
        lcd_com();
        delay_lcd(800);
        lcd_puts(&key);
        
        
    }
}