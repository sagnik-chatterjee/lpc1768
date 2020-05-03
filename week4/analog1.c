#include <LPC17xx.h>
#include <stdio.h>
#include "lcd_disp.c" //refer this module for week3
#define Ref_Vtg  3.3
#define Full_Scale 0xFFF

int main(void)
{
	unsigned long adc_temp;
	unsigned int i;
	float in_vtg;
	unsigned char vtg[7],dval[7];
	unsigned char Msg1[11]={"ANALOG IP"};
	unsigned char Msg2[12]={"ADC O/P"};
	lcd_init();
	LPC_PINCON->PINSEL3=3<<30; //P1.31 as AD0.5
	LPC_SC->PCONP |=(1<<12);
	temp1=0x80;
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg1);
	temp1 = 0xC0;
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg2);
	
	while(1)
	{
		LPC_ADC->ADCR = 1<<5 | 1<<21 | 1<<24;
		
		while(!(adc_temp = LPC_ADC->ADDR5 & 0x80000000));
		
		adc_temp = LPC_ADC->ADDR5;
		adc_temp >>=4;
		adc_temp &=0x00000FFF;
		in_vtg = ((float)adc_temp * Ref_Vtg)/Full_Scale;
		sprintf(vtg,"%3.2fV",in_vtg);
		sprintf(dval,"%x",adc_temp);
		for(i=0;i<2000;i++);
		temp1=0x8A;
		lcd_com();
		delay_lcd(800);
		lcd_puts(&vtg[0]);
		
		for(i=0;i<2000;i++);
		
		temp1 = 0xC8;
		lcd_com();
		delay_lcd(800);
		lcd_puts(&dval[0]);
		
		for(i=0;i<2000;i++);
		
		for(i=0;i<7;i++)
		{
			vtg[i] = dval[i] = 0x00;
			adc_temp = 0;
			in_vtg=0;
		}
		
		
	}
	return 0;
}