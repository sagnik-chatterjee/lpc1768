#include <LPC17xx.h>

unsigned char SCANCODE[4]={0x11,0x21,0x41,0x81};
unsigned int pulse_widths[]={3000,7500,15000,22500};

unsigned char row,var,flag;
unsigned int key,count;
unsigned long int i,var1,temp,temp1,temp2,temp3;

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

void updatePulseWidth(unsigned int pulseWidth)
{
	LPC_PWM1->MR4=pulseWidth;
	LPC_PWM1->LER=0XFF;
}
void scan(void)
{
	temp3 = LPC_GPIO1->FIOPIN;
	temp3 &=0x07800000;
	if(temp3 != 0)
	{
		flag = 1;
		temp3 >>=19;
		temp >>=10;
		key = temp3 | temp;
	}

}


int main(void)
{
	
	LPC_GPIO0->FIODIR =0xf00;
		initPWM();
	while(1)
	{	
		while(1){

			for(row = 1;row<5;row++)
			{
				if(row == 1)
				{
					var1 = 0x00000400;
				}
				else if (row == 2)
					var1 = 0x00000800;
				else if (row ==3)
					var1 = 0x00001000;
				else if (row == 4)
					var1 = 0x00002000;
				
				temp = var1;
				
				LPC_GPIO0->FIOSET = var1;
				
				flag = 0;
				scan();
				
				if(flag == 1)
				break;
			}
			
			if(flag == 1)
				break;				
				
		}
		
		
		for(i=0;i<4;i++)
		{
			if (key == SCANCODE[i])
			{
				key = pulse_widths[i];
				break;
				
			}
		}	
		updatePulseWidth(key);
				delayMS(10000);
		
	}

}
