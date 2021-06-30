#include "ultrasonic.h"
#include "delay.h"

/**
	*@brief	超声波模块初始化
	*@param	无
	*@retval	无
	*/
void Ultrasonic_Init(void)
{
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//PC7初始化（Trig管脚）
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	
	//PC6初始化（Echo管脚）
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	
	//定时器4初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=9999;//计数器最大寄到10000，周期0.01s，每记一数10us
	TIM_TimeBaseInitStructure.TIM_Prescaler=719;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	
}


/**
	*@brief	超声波模块测距
	*@param	无
	*@retval	距离
	*测试距离=（高电平时间*声速（340m/s））/2
	*/
float Ultrasonic_Distance(void)
{
	u8 i;
	u16 Num=0,Temp;
	float Distance;
	for(i=0;i<5;i++)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		TIM_SetCounter(TIM4,0);
		
		GPIO_SetBits(GPIOC,GPIO_Pin_7);
		delay_us(40);
		GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0);
		TIM_Cmd(TIM4,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==1);
		Temp=TIM_GetCounter(TIM4);
		TIM_Cmd(TIM4,DISABLE);
		TIM_SetCounter(TIM4,0);
		
		Num+=Temp;	
	}
	Distance=((Num/5)*0.00001*Speed)/2;
	return Distance;
}

