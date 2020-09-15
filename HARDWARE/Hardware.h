//==========================================================
//文件名称：Hardware.h
//文件描述：硬件控制头文件
//文件版本：Ver1.0
//创建日期：2014.12.29
//修改日期：2015.09.06 10:46
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
#ifndef __Hardware_H__
#define __Hardware_H__

//#include "STC89C5xRC_RDP.h"
//#include "Stc12c5A60s2.h"

//==========================================================
//全局变量定义
//extern idata vu8 N4_377_Buf;//N4-377输出缓冲
//extern idata vu8 N5_377_Buf;//N5-377输出缓冲

//==========================================================
#define Os_Enter_Critical() (EA=0)	//关中断
#define Os_Exit_Critical() 	(EA=1)	//开中断
#define Open_Uarts_Int() 	(ES=1)	//开启串口中断
#define Close_Uarts_Int() 	(ES=0)	//关启串口中断

//==========================================================
//Stc12系列 CPU ID ADDR (位于idata 区)
#define CPU_ID_ADDR (0xF1)

//==========================================================
//MCP3202管脚定义(SPI,12bit逐次逼近型A/D,2通道,2.7V-5.5V,50-100kbpb)
//sbit MCP3202_CS 	= P1^1;//低电平有效
//sbit MCP3202_DOUT	= P1^2;
//sbit MCP3202_DIN	= P1^3;
//sbit MCP3202_CLK	= P1^4;

//MCP3202通道控制字定义(启动位1,单端/差分配置1,通道配置1,数据方向配置1,空位1)
#define MCP3202_CH0	(0xD0)	
#define MCP3202_CH1	(0xF0)

//==========================================================
//TLC5618管脚定义(12bit D/A,2通道,1.2MHz,+5V供电)
//sbit TLC5618_CS 	= P1^5;//低电平有效
//sbit TLC5618_CLK	= P1^4;
//sbit TLC5618_DIN	= P1^3;

//TLC5618通道控制字定义
//#define TLC5618_CHA	(0x8000)	//D15=1：通道A
//#define TLC5618_CHB	(0x0000)	//D15=0：通道B
//#define TLC5618_MASK (0x0fff)	//12位掩码

//==========================================================
//CD4040复位控制信号，波形输出控制，CD4040-RST-11,RST=1时复位，输出全零
//sbit WaveOutEnable = P3^4;
#define Sin_Clk_Enable() 	(TIM_Cmd(TIM2,ENABLE))	//输出正弦波频率
#define Sin_Clk_Disable() 	(TIM_Cmd(TIM2,DISABLE))	//禁止正弦波频率输出

//==========================================================
//74LS377地址定义
//==========================================================
//#define N4_377_BUS  XBYTE[0xEFFF]	//A15
//--------------------------------------
//D7-FEED-LM324-FEED/PROC_C -1 (PROC_C-ULN2004-PLC RELAY)
//D6-PASS_C-ULN2004-PASS -1 (Led Pass/PLC RELAY)
//D5-FAIL_C-ULN2004-FAIL -1 (Led Fail/PLC RELAY)
//D4-HVDCKZ-LM324-HV-RY0/DCNYKZ -1 (HV RELAY1/4053_C)
//D3-HVACKZ-ULN2004-HV-RY1 -1 (HV RELAY0)
//D2-HUILU-ULN2004-HUILUKZ -1
//D1-NY-ULN2004-NYKZ -1
//D0-JD-ULN2004-JDKZ -1
//--------------------------------------
//N19_574_Buf
//--------------------------------------
//#define HW_PLC_START_MASK	((u8)(ClrD7))
//#define HW_PLC_START_ON		((u8)(SetD7))
#define HW_BEEP_MASK		((u8)(ClrD0))
#define HW_BEEP_ON			((u8)(SetD0))

#define HW_LED_PASS_MASK	((u8)(ClrD1))
#define HW_LED_PASS_ON		((u8)(SetD1))



#define HW_LED_HV_MASK		((u8)(ClrD3))
#define HW_LED_HV_ON		((u8)(SetD3))

//#define HW_RELAY_HV1_MASK	((u8)(ClrD3))
//#define HW_RELAY_HV1_ON		((u8)(SetD3))

#define HW_RELAY_RET_MASK	((u8)(ClrD1))//开机的时候功放输出
#define HW_RELAY_RET_ON		((u8)(SetD1))

//#define HW_AMP_ACW_MASK		((u8)(ClrD1))
//#define HW_AMP_ACW_ON		((u8)(SetD1))

//#define HW_AMP_GND_MASK		((u8)(ClrD0))
//#define HW_AMP_GND_ON		((u8)(SetD0))

//==========================================================
//#define N5_377_BUS  XBYTE[0xBFFF]	//A14
//==========================================================
//D7-
//D6-FMQ-9013 -1
//D5-HIGH_LED-ULN2004-HVLED -1
//D4-NYCYKZ-LM324-NYCYQH-4053_B/A
//D3-LC4-ULN2004-LCKZ4-RRY4_900  -1
//D2-LC3-ULN2004-LCKZ3-RRY3_9k   -1
//D1-LC2-ULN2004-LCKZ2-RRY2_90k  -1
//D0-LC1-ULN2004-LCKZ1-RRY1_900k -1
//--------------------------------------
//N42_574_Buf
//--------------------------------------




//#define HW_SAMPLE_NYIR_MASK	((u8)(ClrD6))
//#define HW_SAMPLE_NYIR		((u8)(SetD6))

#define HW_SAMPLE_DC_MASK	((u8)(ClrD0))
#define HW_SAMPLE_DC_ON		((u8)(SetD0))

#define HW_LED_FAIL_MASK	((u8)(ClrD2))
#define HW_LED_FAIL_ON		((u8)(SetD2))

#define HW_RELAY_H_MASK	((u8)(ClrD5))
#define HW_RELAY_H 		((u8)(SetD5))

#define HW_RELAY_L_MASK	((u8)(ClrD6))
#define HW_RELAY_L 		((u8)(SetD6))

#define HW_RELAY_9K_MASK	((u8)(ClrD1))
#define HW_RELAY_9K 		((u8)(SetD1))


//==========================================================
//频率值
enum FreqEnum
{	
	FREQ_50 ,
	FREQ_60 ,
	FREQ_400 ,
};

//==========================================================
//系统时钟节拍
#define TICKS_PER_SEC 100	//系统时钟每秒节拍数，100x10mS(T0)=1S
#define TICKS_PER_SEC_SOFTTIMER 100	//软定时器时钟每秒节拍数，100x10mS=1S

//常数定义
#define SYSTEM_CLOCK (11059200)//11.0592MHz
//#define SYSTEM_CLOCK (12000000)//12MHz

#define TIMER0_TICKS (u16)(65535-SYSTEM_CLOCK/12/100) //10mS(100Hz)定时值,12T
#define TH0_TICKS	(u8)(TIMER0_TICKS>>8)	//10ms中断
#define TL0_TICKS	(u8)(TIMER0_TICKS)		

//#define TIMER1TICKS (u16)(65535-SYSTEM_CLOCK/12/20) //50mS(20Hz)定时值,12T
//#define TH1_TICKS	(u8)(TIMER1TICKS>>8)	//50ms中断
//#define TL1_TICKS	(u8)(TIMER1TICKS)		
//
#define BAUD_RATE_9600 (9600)
#define BAUD_TICKS (u8)(256-SYSTEM_CLOCK/12/32/BAUD_RATE_9600) //12T

//#define TIMER2TICKS_20mS (u16)(65535-SYSTEM_CLOCK/12/50) //20mS(50Hz)定时值,12T
//#define TIMER2TICKS_20mS (u16)(65535-SYSTEM_CLOCK/12/25) //40mS(25Hz)定时值,12T
//#define TH2_TICKS_20mS	(u8)(TIMER2TICKS_20mS>>8)
//#define TL2_TICKS_20mS	(u8)(TIMER2TICKS_20mS)		

//#define TIMER2TICKS_1mS (u16)(65535-SYSTEM_CLOCK/12/1000) //1mS(1kHz)定时值,12T
//#define TH2_TICKS_1mS	(u8)(TIMER2TICKS_1mS>>8)
//#define TL2_TICKS_1mS	(u8)(TIMER2TICKS_1mS)		

#define BAUD_RATE_9600 (9600)
#define UART0_BAUD_9600 (u16)(65536-SYSTEM_CLOCK/32/BAUD_RATE_9600)//T2-12T
#define BAUD_9600_TICKS_H	(u8)(UART0_BAUD_9600>>8)		
#define BAUD_9600_TICKS_L	(u8)(UART0_BAUD_9600)		

//==========================================================
//函数声明
void Da_Out(u16 dat);//主信号D/A输出
void Arc_Out(u8 arc);//电弧等级输出

u16 Read_Ad_Ch0(void);//读取通道0的A/D值
u16 Read_Ad_Ch1(void);//读取通道1的A/D值

//void Range_Control(u8 dat);//量程控制

void Frequency_Control(u8 dat);//输出频率控制

void Amp_Output_On(void);//功放输出开，按参数
void Amp_Output_Off(void);

void Dc_Output_On(void);//DC输出和采样
void Dc_Output_Off(void);

void Beep_On(void);//开蜂鸣器
void Beep_Off(void);//关蜂鸣器

void Led_HV_On(void);//开高压灯
void Led_HV_Off(void);//关高压灯

void Led_Fail_On(void);//开报警灯
void Led_Fail_Off(void);//关报警灯

void Led_Pass_On(void);//开合格灯
void Led_Pass_Off(void);//关合格灯


void Plc_Start_On(void);//开PLC启动
void Plc_Start_Off(void);//关PLC启动

//void Start_Timer0_Count(void);//开启T0为16位计数器
void Start_Timer0_10ms(void);//开启T0为10ms定时器
void Stop_Timer0(void);//关闭T0

//void Start_Timer1_Count(void);//开启T1为16位计数器
//void Start_Timer1_50ms(void);//开启T1为50ms定时器
void Start_Timer1_Baud(void);//开启T1为波特率发生器
void Stop_Timer1(void);//关闭T1

//void Start_Timer2_Baud_9600(void);//开启T2为波特率发生器
//void Start_Timer2_20ms(void);//开启T2为20ms定时器
//void Start_Timer2_1ms(void);//开启T2为1ms定时器
//void Stop_Timer2(void);//关闭T2

//void ReadCpuId(u8 *buf);//读取CPU序列号

void Start_Uart(void);//串口开启
void Stop_Uart(void);//串口关闭

void Cpu_Init(void);//单片机初始化

void Hardware_Init(void);//硬件初始化

void ResetSys(void);//系统复位


#endif
