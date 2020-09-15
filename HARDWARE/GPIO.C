#include "pbdata.h"
//#define BEEP GPIO_SetBits()
u8 IC19_574buff,IC42_574buff;
void PORT_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5
	|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
}
//GPIO_WriteHigh(GPIOx,a)


void Led_Test_Off(void)//关测试灯
{
	Led_HV_Off();
}
void Led_Test_On(void)//开测试灯
{
	Led_HV_On();
	
}

//void Led_HV_On(void)//开高压灯
//{
//	GPIO_SetBits(GPIOC,GPIO_Pin_9);

//}
//void Led_HV_Off(void)//关高压灯
//{
//	GPIO_ResetBits(GPIOC,GPIO_Pin_9);

//}
