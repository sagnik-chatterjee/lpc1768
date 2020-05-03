#include <LPC17xx.h>

void initpwm(void);
void updatePulseWidth(unsigned int pulseWidth);
void delayMS(unsigned int milliseconds);
unsigned int count=4,ch=0;
int pulseWidths[]={3000,7500,15000,22500,9000};
int main(void)
{
		LPC_GPIO0->FIODIR|=0x00000F00;
		LPC_GPIO0->FIODIR&=0xFFFFFF0F;
		LPC_GPIO0->FIOSET=0x00000100;
		
		initpwm();
		while(1)
		{
			//LPC_GPIO0->FIOCLR=0x000000E0;
			LPC_GPIO0->FIOSET=0x00000100;
			while(1)
			{
			ch=((LPC_GPIO0->FIOPIN&0x000000F0)>>4);
			delayMS(10000);
				switch(ch)
				{
					case 1:
						count=0;
					updatePulseWidth(3000);
						break;
					case 2:
						count=1;
					updatePulseWidth(7500);
						break;
					case 4:
						count=2;
					updatePulseWidth(15000);
						break;
					case 8:
						count=3;
					updatePulseWidth(22500);
						break;
					default:
						count=4;
					updatePulseWidth(0);
				}
				delayMS(10000);
			}
		}
}
void updatePulseWidth(unsigned int pulseWidth)
{
	LPC_PWM1->MR4=pulseWidth;
	LPC_PWM1->LER=0xFF;
}
void initpwm(void)
{
	LPC_PINCON->PINSEL3 |=0x8000;
	LPC_PWM1->PCR=0x1000; //Output at P1.4
	LPC_PWM1->PR=0;	//TC++ every clock cycle
	LPC_PWM1->MR0=30000; //TC goes from 0 to 30k
	LPC_PWM1->MCR=(1<<1); //Reset TC
	LPC_PWM1->LER=0xFF; //Write from shadow
	LPC_PWM1->TCR=0x00000002; //Counter reset
	LPC_PWM1->TCR = 0x00000009;
	
}
void delayMS(unsigned int milliseconds) //using timer
{
	LPC_TIM0->CTCR=0x0;
	LPC_TIM0->PR=2;
	LPC_TIM0->TCR=0x02;
	LPC_TIM0->TCR=0x01;
	while(LPC_TIM0->TC<milliseconds);
	LPC_TIM0->TCR=0x00;
}
