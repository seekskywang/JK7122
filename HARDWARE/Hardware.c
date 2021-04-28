//==========================================================
//文件名称：Hardware.c
//文件描述：硬件控制初始化
//文件版本：Ver1.0
//创建日期：2014.12.29
//修改日期：2015.09.06 10:46
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
//#include <absacc.h>
//#include <intrins.h>

//#include "TypeDefine.h"
//#include "GlobalValue.h"
//#include "Delay.h"
//#include "Beep.h"
//#include "Keyboard.h"
//#include "Interrupt.h"
//#include "Lcd240128.h"
//#include "Hardware.h"
#include "pbdata.h"
//==========================================================
//全局变量定义


//==========================================================
//函数名称：Write_TLC5618
//函数功能：12位D/A转换
//入口参数：D/A数值
//出口参数：无
//创建日期：2014.04.01
//修改日期：2014.04.01
//备注说明：(MSB~LSB)
//==========================================================


//==========================================================
//函数名称：Da_Out
//函数功能：主信号D/A输出
//入口参数：u16 dat = D/A值
//出口参数：无
//创建日期：2014.04.01
//修改日期：2015.08.26 08:58 
//备注说明：通道1=电压/电流DA输出值
//==========================================================
void Da_Out(u16 dat)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, dat);
	
}

//==========================================================
//电弧幅度值
const u16 ArcLevel[]=
{
//	0xFFF,	//5.00V-0
//	0xEE2,	//4.65V-1
//	0xE66,	//4.50V-2
//	0xDC2,	//4.30V-3
//	0xCCD,	//4.00V-4
//	0xBAE,	//3.65V-5
//	0xAB8,	//3.35V-6
//	0x9EB,	//3.10V-7
//	0x666,	//2.00V-8
//	0x333,	//1.00V-9
	
	0xFFF,	//5.00V-0
	
	0x999,	//2.24V-1
	0x8F5,	//1.50V-2
	0x75B,	//1.30V-3
	0x666,	//1.10V-4
	0x570,	//1.00V-5
	0x47A,	//0.80V-6
	0x333,	//0.60V-7
	0x1EB,	//0.30V-8
	0x147,	//0.10V-9
	
//	0xFFF,	//5.00V-0
//	0xAE0,	//3.40V-1
//	0x9EB,	//3.10V-2
//	0x428,	//2.70V-3
//	0x385,	//1.90V-4
//	0x333,	//1.60V-5
//	0x28F,	//1.10V-6
//	0x1EB,	//0.80V-7
//	0x0F5,	//0.60V-8
//	0x052,	//0.40V-9

//	0xFFF,	//5.00V-0
//	0x72A,	//2.24V-1
//	0x4CC,	//1.50V-2
//	0x428,	//1.30V-3
//	0x385,	//1.10V-4
//	0x333,	//1.00V-5
//	0x28F,	//0.80V-6
//	0x1EB,	//0.60V-7
//	0x0F5,	//0.30V-8
//	0x052,	//0.10V-9
};

//==========================================================
//函数名称：Arc_Out
//函数功能：电弧等级电压幅度输出
//入口参数：u8 level = 电弧电击
//出口参数：无
//创建日期：2014.04.01
//修改日期：2015.08.26 08:53
//备注说明：通道0 = 耐压电弧幅度/电压限定
//==========================================================
void Arc_Out(u8 arc)
{
	DAC_SetChannel2Data(DAC_Align_12b_R, ArcLevel[arc]);
}	

//==========================================================
//函数名称：Read_MCP3202
//函数功能：通道 A/D转换
//入口参数：通道控制字
//出口参数：12位AD
//创建日期：2014.04.01
//修改日期：2014.04.01
//备注说明：数据方向配置1=MSB~LSB，也可配置成0:=LSB~MSB
//==========================================================


//==========================================================
//读取通道0的A/D值
//==========================================================
u16 Read_Ad_Ch0(void)
{
	return( Get_Adc(ADC1,1));
}

//==========================================================
//读取通道1的A/D值
//==========================================================
u16 Read_Ad_Ch1(void)
{
	return(Get_Adc(ADC2,2));
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
void Beep_On(void)//
{
	//IC42_574buff
	IC42_574buff|=HW_BEEP_ON;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
	
}
//==========================================================
void Beep_Off(void)
{
	IC42_574buff&=HW_BEEP_MASK;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
}
void Led_Fail_Off(void)//关不合格
{
	IC19_574buff&=HW_LED_FAIL_MASK;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
}
void Led_Fail_On(void)//开不合格
{
	

	IC19_574buff|=HW_LED_FAIL_ON;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
}
//==========================================================
//函数名称：Led_HV_On
//函数功能：开高压灯
//入口参数：无
//出口参数：无
//创建日期：2015.01.12
//修改日期：2015.09.04 14:45
//备注说明：无
//==========================================================
void Led_HV_On(void)
{
	IC42_574buff|=HW_LED_HV_ON;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
	
}

//==========================================================
void Led_HV_Off(void)
{
	IC42_574buff&=HW_LED_HV_MASK;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;

}

void Plc_Pass_On(void)
{
	IC19_574buff|=HW_LED_HV_ON;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;

}
//==========================================================
void Plc_Pass_Off(void)
{
	IC19_574buff&=HW_LED_HV_MASK;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
}
//==========================================================
//函数名称：Led_Pass_On
//函数功能：开合格灯
//入口参数：无
//出口参数：无
//创建日期：2015.01.12
//修改日期：2015.09.04 14:47
//备注说明：同时控制PLC的输出,合格继电器导通
//==========================================================
void Led_Pass_On(void)
{
	IC42_574buff|=HW_LED_PASS_ON;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
	Plc_Pass_On();
	
}

//==========================================================
void Led_Pass_Off(void)
{
	IC42_574buff&=HW_LED_PASS_MASK;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
	Plc_Pass_Off();
}



//==========================================================
//函数名称：Plc_Start_On
//函数功能：PLC启动继电器导通
//入口参数：无
//出口参数：无
//创建日期：2015.01.12
//修改日期：2015.09.04 14:42
//备注说明：同时释放反馈端硬件输出控制保护
//==========================================================
void Plc_Start_On(void)
{
	PDout(6)=0;

}
//==========================================================
void Plc_Start_Off(void)
{
	PDout(6)=1;
}




//===============================================
//函数名称：Amp_Output_On
//函数功能：功放输出继电器闭合
//入口参数：u8 dat：参数
//出口参数：无
//创建日期：2014.04.01
//修改日期：2015.09.04 15:26
//备注说明：同时控制回路端、采样信号
//===============================================
void Amp_Output_On(void)
{
	IC19_574buff|=HW_RELAY_RET_ON;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
}
//===============================================
void Amp_Output_Off(void)
{
	IC19_574buff&=HW_RELAY_RET_MASK;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
	
}

//===============================================
//函数名称：Dc_Output_On
//函数功能：DC输出和采样
//入口参数：无
//出口参数：无
//创建日期：2014.04.01
//修改日期：2015.09.04 15:15
//备注说明：高压继电器RY0、RY1控制，AC、DC采样控制
//===============================================
void Dc_Output_On(void)
	

{
	IC19_574buff|=HW_SAMPLE_DC_ON;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
	PDout(7)=1;
	
}
//===============================================
void Dc_Output_Off(void)
{
	IC19_574buff&=HW_SAMPLE_DC_MASK;
	PDout(5)=0;
	GPIO_WriteHigh(GPIOD,IC19_574buff);
	PDout(5)=1;
	PDout(7)=0;
	
}

//===============================================
//函数名称：Frequency_Control
//函数功能：输出频率控制
//入口参数：u8 dat
//出口参数：无
//创建日期：2015.09.05
//修改日期：2015.09.06 14:00
//备注说明：T1输出(P3.5),256点
//===============================================
//#define FREQ_12K  (256-SYSTEM_CLOCK/2/12/12800)
//#define FREQ_15K  (256-SYSTEM_CLOCK/2/12/15360)
//#define FREQ_102K (256-SYSTEM_CLOCK/2/12/102400)
//===============================================
void Frequency_Control(u8 dat)
{


	if(dat==FREQ_50)
	{
		TIM2_Configuration(3,1405);
	}
	else if(dat==FREQ_60)
	{
		TIM2_Configuration(3,1171);
	}
	else
	{
		TIM2_Configuration(3,175);
	}

}

//==========================================================
//TMOD:
//D7    D6   D5  D4	 D3    D2   D1  D0
//GATE1 C/T	 M1	 M0	 GATE0 C/T	M1	M0
//TCON:
//D7  D6   D5   D4	 D3   D2   D1   D0
//TF1 TR1  TF0	TR0	 IE1  IT1  IE0	IT0=1,下降沿中断
//==========================================================
//函数名称：Start_Timer0_Count
//函数功能：开启T0为16位计数器
//入口参数：无
//出口参数：无
//创建日期：2014.09.25
//修改日期：2014.09.25 16:47
//备注说明：下降沿计数，GATE信号使能时，外部INT0=1计数
//==========================================================
//void Start_Timer0_Count(void)
//{
//	TMOD &= 0xF0;		//清除Time0模式位
//	TMOD |= 0x0D;		//设定Time0为16位计数，GATE=1
//	TH0 = 0x00;
//	TL0 = 0x00;
//	TF0 = 0;
//	ET0 = 1;//开T1中断
//	TR0 = 1;//启动T0
//}

//==========================================================
//函数名称：Start_Timer0_10ms
//函数功能：开启T0为10ms定时器
//入口参数：无
//出口参数：无
//创建日期：2014.09.24
//修改日期：2014.09.24 15:01
//备注说明：系统时基
//==========================================================
//void Start_Timer0_10ms(void)
//{
//	
//}
////==========================================================
//void Stop_Timer0(void)
//{
//	
//}

//==========================================================
//函数名称：Start_Timer1_Count
//函数功能：开启定时器T1，16位计数器
//入口参数：无
//出口参数：无
//创建日期：2014.09.25
//修改日期：2014.09.25 16:47
//备注说明：外部GATE信号使能，INT1=1时计数
//==========================================================
//void Start_Timer1_Count(void)
//{
//	TMOD &= 0x0F;	//清除Time1模式位
//	TMOD |= 0xD0;	//设定Time1为16位计数，GATE=1
//	TH1 = 0x00;
//	TL1 = 0x00;
//	TF1 = 0;
//	ET1 = 0;
//	TR1 = 1;//启动T1
//}

//==========================================================
//函数名称：Start_Timer1_50ms
//函数功能：开启定时器T1，16位定时器，50ms
//入口参数：无
//出口参数：无
//创建日期：2014.09.25
//修改日期：2014.09.25 16:01
//备注说明：软定时器时基
//==========================================================
//void Start_Timer1_50ms(void)
//{
//	TMOD &= 0x0F;		//清除Time1模式位
//	TMOD |= 0x10;		//设定Time1为16位定时
//	TH1 = TH1_TICKS;	//50mS
//	TL1 = TL1_TICKS;
//	ET1 = 1;//开T1中断
//	TR1 = 1;//启动T1
//}

//==========================================================
//函数名称：Start_Timer1_Baud
//函数功能：定时器T1作为波特率发生器
//入口参数：无
//出口参数：无
//创建日期：2014.09.25
//修改日期：2014.09.25 16:01
//备注说明：无
//==========================================================
//void Start_Timer1_Baud(void)
//{
//	
//}

//////==========================================================
//void Stop_Timer1(void)
//{
//	
//}

//==========================================================
//T2MOD:
//D7   D6   D5   D4	 D3   D2   D1   D0
//                             T2OE DCEN
//T2CON:
//D7   D6   D5   D4	  D3    D2   D1   D0
//TF2  EXF2	RCLK TCLK EXEN2 TR2	 C/T  CP/RL
//==========================================================
//函数名称：Start_Timer2_Baud_9600
//函数功能：开启定时器T2，波特率发生器，9600
//入口参数：无
//出口参数：无
//创建日期：2014.09.27
//修改日期：2014.09.27 15:15
//备注说明：无
//==========================================================
//void Start_Timer2_Baud_9600(void)
//{
////	T2MOD |= 0x02;	//D1:T2OE=1，T2时钟输出(P1.0)允许;D0：DCEN=0，加计数;
//	T2CON  = 0x30;	//T2作为波特率发生器
//	RCAP2H = BAUD_9600_TICKS_H;
//	RCAP2L = BAUD_9600_TICKS_L;
//	ET2 = 0;//关T2中断
//	TR2 = 1;//启动T2
//}

//==========================================================
//函数名称：Start_Timer2_20ms
//函数功能：开启定时器T2，16位定时器，20ms
//入口参数：无
//出口参数：无
//创建日期：2014.09.27
//修改日期：2014.09.27 15:15
//备注说明：无
//==========================================================
//void Start_Timer2_20ms(void)
//{
////	T2MOD = 0x00;//D1:T2OE=0，T2时钟输出(P1.0)禁止;D0：DCEN=0，加计数;
//	T2CON = 0x00;//D7:TF2=0;D2:TR2=0;D1:C/T2=0,定时;D0:CP=0:重载;
//	TH2 = TH2_TICKS_20mS;
//	TL2 = TH2_TICKS_20mS;
//	RCAP2H = TH2_TICKS_20mS;
//	RCAP2L = TH2_TICKS_20mS;
//	ET2 = 1;//开启T2中断
//	TR2 = 1;//启动T2
//}
////==========================================================
//void Start_Timer2_1ms(void)
//{
////	T2MOD = 0x00;//D1:T2OE=0，T2时钟输出(P1.0)禁止;D0：DCEN=0，加计数;
//	T2CON = 0x00;//D7:TF2=0;D2:TR2=0;D1:C/T2=0,定时;D0:CP=0:重载;
//	TH2 = TH2_TICKS_1mS;
//	TL2 = TH2_TICKS_1mS;
//	RCAP2H = TH2_TICKS_1mS;
//	RCAP2L = TH2_TICKS_1mS;
//	ET2 = 1;//开启T2中断
//	TR2 = 1;//启动T2
//}
//==========================================================
//void Stop_Timer2(void)
//{
//	TR2 = 0;//关T2
//	ET2 = 0;//关T2中断
//}

//==========================================================
//函数名称：Start_Uart
//函数功能：串口开启
//入口参数：无
//出口参数：无
//创建日期：2015.09.06
//修改日期：2015.09.06 14:46
//备注说明：无
//==========================================================
void Start_Uart(void)
{
	
}
//===============================================
void Stop_Uart(void)
{

}

//===============================================
//函数名称：ReadCpuId
//函数功能：读取芯片的ID号
//入口参数：buf:数据缓冲
//出口参数：无
//创建日期：2014.09.27
//修改日期：2014.09.27 15:48
//备注说明：共7个字节
//===============================================
//void ReadCpuId(u8 *buf)
//{
//	u8 i=7;
//	u8 idata *addr;
//
//	addr=CPU_ID_ADDR;
//	while(i--)
//	{
//		*buf = *addr;
//		buf++;
//		addr++;
//	}
//}

//==========================================================
//函数名称：Cpu_Init
//函数功能：单片机初始化
//入口参数：无
//出口参数：无
//创建日期：2014.09.27
//修改日期：2014.09.27 16:20
//备注说明：无
//==========================================================
void Cpu_Init(void)
{

}

//===============================================
//函数名称：Hardware_Init
//函数功能：硬件初始化
//入口参数：无
//出口参数：无
//创建日期：2014.09.27
//修改日期：2015.09.04 14:53
//备注说明：无
//===============================================
void Hardware_Init(void)
{
//	Cpu_Init();	//CPU初始化
	RCC_Configuration();
	GPIO_UART();
	USART_Configuration(9600);
	PORT_Gpio_Init();//GPIO配置
	EXTIX_Init();
	Lcd_Init();	//液晶初始化
	Keyboard_Init();
	Key_Init();//按键初始化
	Beep_Init();//蜂鸣器初始化
	AT24CXX_Init();
	Plc_Start_Off();//关远控启动
	Led_Pass_Off();//关闭合格灯
	Led_Fail_Off();//关闭失败灯
	Led_HV_Off();//关闭高压灯
    ADC_Configuration();
    DAC_Configuration();
	
	
	
	TIM3_Configuration( );
	Dma_Int();
	
	
	
//	Stop_Timer0();//关闭T0
//	Start_Timer0_10ms();//开启定时器T0-10ms系统时基

//	if(SaveData.System.Uart==1)
//		Start_Uart();//串口开启
//	else
//		Stop_Uart();//串口关闭
}

//==========================================================
//函数名称：ResetSys
//函数功能：系统复位
//入口参数：无
//出口参数：无
//创建日期：2014.09.24
//修改日期：2014.09.24 15:01
//备注说明：无
//==========================================================
void ResetSys(void)
{
//	Os_Enter_Critical();//关中断
//	(*(void(*)())0)(); //零代码
//	Os_Exit_Critical();//开中断
}

//==========================================================
//END
//==========================================================
