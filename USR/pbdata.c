#include "pbdata.h"


bool F_Fail;//测试失败标志
bool F_100ms;//100ms定时标志
bool F_Password;//密码有效标志
 vu8 SystemStatus;//系统状态
 vu8 SystemMessage;//系统信息
vu8 MenuIndex;//待机菜单项
vu8 Range;//当前量程
vu8 ffit_data1;
vu16 count_ffit;
//NumBox_TypeDef NumBox;//数值框
vu32 Voltage;//电压
vu32 Test_Time;//时间
vu32 Resistance;//电阻
NumBox_TypeDef NumBox;
Test_TypeDef Test_value;
Float_TypeDef Float;
Save_TypeDef SaveData;//保存值
Calibrate_TypeDef Calibrate;
Res_countTypeDef Res_count;
u8 dt=0;
//u8 fft_flag;
u8 SoftTimer[MAXTSOFTTIMER];//软定时器
float i_buff[FIT_INUM];		   //滤波值
vu16 Vbuf[AD_BUF_LENGTH];//电压A/D值缓冲
vu16 Ibuf[AD_BUF_LENGTH];//电流A/D值缓冲
vu8 StepIndex;//步骤项
vu8 TotalStep;//测试总步骤
vu16 Current;//电流
vu16 TestTime;//时间
vu8 AdCount;//A/D值采样计数
vu16 RampStepYs;//缓升步进余数
vu16 RampStepFd;//缓升步进幅度
vu8 RampStepTime;//缓升步进时间
vu16 TestOut;//测试输出值
vu16 FullOut;//满载输出值
u8 ra_flag;
u8 run_stemp;
Test_mid_Typedef Test_mid;
u16 rangelomit_low,rangr_limit_high;
Cal_TypeDef Cal[11];//校准值
vu8 groupflag;

//==========================================================
//默认校准输出值
const vu16 DefaultCalDaOut[]=
{
	 2430, //Acw-4kV
	 2800, //Dcw-4kV
	  610, //Ir -1kV
	 3000, //Gnd-25A
};

//==========================================================
//参数项(5项)
//typedef struct 
//{
//	vu8 Range;//量程模式(0-4，默认0自动)
//	vu8 ClrOn;//清零开关(0-1，默认关0)
//	vu8 Beep;//讯响模式(0-2，默认开1-PassOn)
//	vu8 ExTrig;//外部触发开关(0-1，默认关0)
//	vu8 UartOn;//串口开关(0-1，默认关0)
////	vu8 FastOn;//快速测试(0-1，默认关0)
//}Parameter_TypeDef;
//==========================================================
//配置项(3项)
//typedef struct 
//{
//	vu16 Password;//设置密码(0-9999，默认0)
//	vu16 BootNum;//开机次数(0-9999，默认0)
//	vu16 ProductId;//出厂编号(0-9999，默认0)
//}Config_TypeDef;


//==========================================================
//保存信息
//typedef struct 
//{
//	Parameter_TypeDef Parameter;//参数项
//	System_TypeDef System;//系统项
//	Config_TypeDef Config;//配置项
//	Calibrate_TypeDef Calibrate;//校准项
//	vu16 Crc16;//校验字
//}Save_TypeDef;

void RCC_HSE_Configuration(void) //HSE作为PLL时钟，PLL作为SYSCLK 
{ 
   RCC_DeInit(); /*将外设RCC寄存器重设为缺省值 */ 
   RCC_HSEConfig(RCC_HSE_ON); 	 /*设置外部高速晶振（HSE） HSE晶振打开(ON)*/ 

   if(RCC_WaitForHSEStartUp() == SUCCESS) {  /*等待HSE起振,  SUCCESS：HSE晶振稳定且就绪*/  

   RCC_HCLKConfig(RCC_SYSCLK_Div1);/*设置AHB时钟(HCLK)RCC_SYSCLK_Div1——AHB时钟 = 系统时*/  
   RCC_PCLK2Config(RCC_HCLK_Div1); /*设置高速AHB时钟(PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*设置低速AHB时钟(PCLK1)RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/      

   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/*设置PLL时钟源及倍频系数*/    
   RCC_PLLCmd(ENABLE); 	 /*使能PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*检查指定的RCC标志位(PLL准备好标志)设置与否*/ 
    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*设置系统时钟（SYSCLK） */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08：PLL作为系统时钟 */	    
 } 
} 

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);
}

/****************************************************************************
* 名    称：delay_us(u32 nus)
* 功    能：微秒延时函数
* 入口参数：u32  nus
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

/****************************************************************************
* 名    称：delay_ms(u16 nms)
* 功    能：毫秒延时函数
* 入口参数：u16 nms
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_ms(u16 nms)
{
     //注意 delay_ms函数输入范围是1-1864
	 //所以最大延时为1.8秒

	 u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

//==========================================================
//函数名称：SetSoftTimer
//函数功能：软定时器设置
//入口参数：软定时器id,定时节拍
//出口参数：无
//创建日期：2014.09.29
//修改日期：2014.10.21 15:08
//备注说明：无
//==========================================================
void SetSoftTimer(u8 id, u8 ticks)
{
	SoftTimer[id]=ticks;
}
//==========================================================
//函数名称：GetSoftTimerOut
//函数功能：软定时器溢出
//入口参数：软定时器id
//出口参数：True(定时到)/False
//创建日期：2014.09.29
//修改日期：2014.09.29 11:18
//备注说明：无
//==========================================================
bool GetSoftTimerOut(u8 id)
{
	return (SoftTimer[id]?FALSE:TRUE);
}
//==========================================================
//函数名称：Beep_On
//函数功能：开蜂鸣器
//入口参数：无
//出口参数：无
//创建日期：2015.01.12
//修改日期：2015.09.04 14:34
//备注说明：无
//==========================================================

