#include <LPC17XX.h>

#define true 1
#define DAC_BIAS (0x1 <<16)
#define DATA_LENGTH 	0X400

void DAC_Init(void)
{
	LPC_DAC -> DACCNTVAL =0X00FF;
	LPC_DAC -> DACCTRL =(0X1<<1)|(0X1<<2);
	return;
}

int main(void)
{
	unsigned int m,i=0;

	DAC_Init();
	while(true)
	{
		LPC_DAC ->DACR =(i<<6);
		i+=50;
		for(m=100;m>1;m--);
		if(i==DATA_LENGTH)
		{
			i=0;
		}	

	}
}