#include "stm32f10x.h" // Device heade
#include "LED.h"
#include "delay.h"
#include "ultrasonic.h"
int main()
{
	float Distance;
	LED_Init();
	delay_init();
	Ultrasonic_Init();
	while(1)
	{
		Distance=Ultrasonic_Distance();
		if(Distance<=0.1)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
	}
}

