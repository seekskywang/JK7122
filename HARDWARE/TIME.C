#include "pbdata.h"
u32 disp_time;
void TIM3_Configuration(void)//20ms
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	TIM_TimeBaseStruct.TIM_Period=100;//初值
	TIM_TimeBaseStruct.TIM_Prescaler=7199;//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	 
}


void TIM2_Configuration(u32 Period,u32 Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	
	//TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseStruct.TIM_Period=Period;//初值
	TIM_TimeBaseStruct.TIM_Prescaler=Prescaler;//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	//TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
//	TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
//	//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	TIM_Cmd(TIM2,ENABLE);	

	TIM_DMACmd( TIM2, TIM_DMA_Update, ENABLE);
	//TIM_Cmd(TIM2,ENABLE);	
}
