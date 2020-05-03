/**
 * Program to implement a calculator using matrix buttons
 */

#include <LPC17xx.h>
#include "lcd_disp.c"
void scan(void);

unsigned char row,flag,key;
unsigned long int i,var1,temp1,temp2,temp3;

unsigned char SCAN_CODE[16]={0x11,0x21,0x41,0x81
,0x12,0x22,0x42,,0x82,0x14,0x24,0x44,0x84,
0x18,0x28,0x48,0x88};

unsigned char ascii_code[16]={'0','1','2','3','4
','5','6','7','8','9','A','B','+','-','*','/'};

int index=1;
int ans=0;

unsigned char asciians[3]={'0','0','\0'};
int a=0;int b=0;char op;int count=0;

int main(void)
{

    LPC_GPIO2->FIODIR |=0X3C00;
    
    LPC_GPIO1->FIODIR &=0XF87FFFFF;

    lcd_init();
    temp1=0x80;
    lcd_com();
    delay_lcd(800);
    while(count<3)
    {
        while(1)
        {
            for(row=1;row<5;row++)
            {
                if(row==1)
                var1=0x400;
                else if(row==2)
                var1=0x800;
                else if(row==3)
                var1=0x1000;
                else if(row==4)
                var1=0x2000;

                temp=var1;
                
                LPC_GPIO2->FIOCLR=0X3C00;
                LPC_GPIO2->FIOSET=var1;
                flag=0;
                scan();
                if(flag==0)
                {
                    count++;
                    break;
                }
                if(flag==1)
                {
                    break;
                }
                for(i=0;i<16;i++)
                {
                    if(key==SCAN_CODE[i])
                    {
                        key = ascii_code[i];
                        lcd_puts(&key);
                        delay_lcd(100000);
                        if(count==1)
                        a=key-48;
                        else if(count==2)
                        op=key;
                        else if(count==3)
                        b=key-48;
                        break;
                    }
                }

           }

           
         
        }
        temp1=0xc0;
           lcd_com();
           delay_lcd(800);
           switch(op)
           {
               case '+':ans=a+b;break;
               case '-':ans=a-b;break;
               case '*':ans=a*b;break;
               case '/':ans=a/b;break;
           }
    }
    while(ans!=0)
    {
        asciians[index--]=(ans%10)+48;
        ans=/10;
    }
    lcd_puts(&asciians[0]);
    return 0;
}