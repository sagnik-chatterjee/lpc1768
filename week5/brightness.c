#include <LPC17xx.h>

void initPWM(void)
{
	LPC_PWM1->PCR=0x1000;
	LPC_PWM1->PR=0;
	LPC_PWM1->MR0=30000;
	LPC_PWM1->MCR=(1<<1);//MCR THREE IND BITS ARWE THERE .. SO FOR RESET WE ARE SHIFTING TO THE SECOND BIT TO BE 1 
	LPC_PWM1->LER=0XFF;
	LPC_PWM1->TCR=0X00000002;//for alignment with the rising edge of tc
	LPC_PWM1->TCR=0X00000009; //for alignment with the falling edge of tc

}

void delayMS(unsigned int ms)
{
	LPC_TIM0->CTCR=0X0;
	LPC_TIM0->PR=2;//INCREASE AT EVERY 3 CLK CYCLE 
	LPC_TIM0->TCR=0x02;//reset
	LPC_TIM0->TCR=0x01;//enable 
	while(LPC_TIM0->TC<<ms)
		LPC_TIM0->TCR=0X00;

}

void normalDelay(unsigned int ms)
{
	unsigned int k;
	for( k=0;k<ms;k++);	
}

void updatePulseWidth(unsigned int pulseWidth)
{
	LPC_PWM1->MR4=pulseWidth;
	LPC_PWM1->LER=0XFF;
}

int main(void)
{
	int pulse_widths[]={0,3000,6000,9000,12000,15000,18000,21000,24000,27000};
	const int numPulseWidth=10;
	//no of pulse widths 
	int count=1;
	int directionBrightness=0;//

	initPWM();
	while(1)
	{
		updatePulseWidth(pulse_widths[count]);
		delayMS(100000);
		if(count==(numPulseWidth-1))
		{
			directionBrightness=!directionBrightness; //self compariison 
		}
		if(directionBrightness)count--;
		else count++;
	}

}
