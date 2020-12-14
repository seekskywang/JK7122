#ifndef _pbdata_H
#define _pbdata_H

#define _4094_STBL GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define _4094_STBH GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define _5618_CSL GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define _5618_CSH GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define _DS1302_CSL GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define _DS1302_CSH GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define _CPLD_CSL GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define _CPLD_CSH GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define _7706_CSL GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define _7706_CSH GPIO_SetBits(GPIOC,GPIO_Pin_12)

#define _SPI_SCLKL GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define _SPI_SCLKH GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define _SPI_DINL GPIO_ResetBits(GPIOC,GPIO_Pin_11)
#define _SPI_DINH GPIO_SetBits(GPIOC,GPIO_Pin_11)

#define _SPI_DOUT GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
//#define _SPI_DOUTH GPIO_SetBits(GPIOC,GPIO_Pin_10)

#define _FMQ_CSL GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define _FMQ_CSH GPIO_SetBits(GPIOD,GPIO_Pin_8)

#define _TESTLED_CSL GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define _TESTLED_CSH GPIO_SetBits(GPIOC,GPIO_Pin_9)



#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_i2c.h"
//#include "stm32f10x_fsmc.h"
#include "stdio.h"
#include "Lcd2002.h"
#include "gpio.h"
//#include "cpld.h"
//#include "4094.h"
#include "24c256.h"
#include "dac.h"
#include "adc.h"
#include "dma.h"
//#include "ad7706.h"
#include "debug.h"
#include "time.h"
#include "sys.h"
#include "exti.h"
#include "uart.h"
#include "disp.h"
#include "keyboard.h"
#include "user.h"
#include  "test.h"
#include  <string.h>
#include "flash_eerom.h"
#include "Hardware.h"
#include "Beep.h"
#include "myiic.h"

#define AD_BUF_LENGTH		(8)//A/D值缓冲区长度
#define HW_UART_SUPPORT 1
extern vu16 Vbuf[AD_BUF_LENGTH];//电压A/D值缓冲
extern vu16 Ibuf[AD_BUF_LENGTH];//电流A/D值缓冲
//定义变量

extern u8 dt;
extern vu8 SystemStatus;//系统状态
extern vu8 SystemMessage;//系统信息
extern vu8 MenuIndex;//待机菜单项
extern vu8 Range;//当前量程
extern vu8 ffit_data1;
extern vu16	count_ffit;
extern u8 fft_flag;

extern vu8 StepIndex;//步骤项
extern vu8 TotalStep;//测试总步骤
extern vu16 Current;//电流
extern vu16 TestTime;//时间
extern vu8 AdCount;//A/D值采样计数
extern vu16 RampStepYs;//缓升步进余数
extern vu16 RampStepFd;//缓升步进幅度
extern vu8 RampStepTime;//缓升步进时间
extern  vu16 TestOut;//测试输出值
extern  vu16 FullOut;//满载输出值
extern  u8 run_stemp;//运行步数   连接的时候用
//定义函数

void RCC_HSE_Configuration(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);
void SetSoftTimer(u8 id, u8 ticks);
bool GetSoftTimerOut(u8 id);

void Lcd2002_Gpio_Init(void);

extern const vu16 DefaultCalDaOut[];
//16bit数据的位操作定义
#define	SetD0	(1<<0)
#define	SetD1	(1<<1)
#define	SetD2	(1<<2)
#define	SetD3	(1<<3)
#define	SetD4	(1<<4)
#define	SetD5	(1<<5)
#define	SetD6	(1<<6)
#define	SetD7	(1<<7)
#define	SetD8	(1<<8)
#define	SetD9	(1<<9)
#define	SetD10	(1<<10)
#define	SetD11	(1<<11)
#define	SetD12	(1<<12)
#define	SetD13	(1<<13)
#define	SetD14	(1<<14)
#define	SetD15	(1<<15)

#define	ClrD0	(~(1<<0))
#define	ClrD1	(~(1<<1))
#define	ClrD2	(~(1<<2))
#define	ClrD3	(~(1<<3))
#define	ClrD4	(~(1<<4))
#define	ClrD5	(~(1<<5))
#define	ClrD6	(~(1<<6))
#define	ClrD7	(~(1<<7))
#define	ClrD8	(~(1<<8))
#define	ClrD9	(~(1<<9))
#define	ClrD10	(~(1<<10))
#define	ClrD11	(~(1<<11))
#define	ClrD12	(~(1<<12))
#define	ClrD13	(~(1<<13))
#define	ClrD14	(~(1<<14))
#define	ClrD15	(~(1<<15))


#define HW_HW_PGA_MASK		((u8)((ClrD7&ClrD6)))
#define HW_PGA_1K 			((u8)(SetD6|SetD7))
#define HW_PGA_10K 			((u8)(SetD7))
#define HW_PGA_100K 		((u8)(SetD6))
#define HW_PGA_103K			((u8)(ClrD7&ClrD6))
#define HW_PGA_104K			((u8)(SetD3))
#define HW_PGA_105K			((u8)(SetD4))
#define HW_FD_TEST			((u8)(SetD7))//测试
#define HW_FD_NOTEST		((u8)(~SetD7))//放电

//u21
#define HW_HW_GYB_MASK		((u8)((ClrD1&ClrD2&ClrD3&ClrD7)))

#define HW_GYB_10V 			((u8)(SetD0|SetD7))
#define HW_GYB_100V 		((u8)(SetD0))
#define HW_GYB_1000V 		((u8)(ClrD0&ClrD7))

#define HW_GYB_1000VFEEDMASK ((u8)(ClrD2&ClrD1))
#define HW_GYB_1000VFEED	((u8)(SetD1|SetD2))
#define HW_GYB_100VFEED		((u8)(SetD2))
#define HW_GYB_10VFEED		((u8)(SetD1))

#define HW_GYBFD_ON			((u8)(SetD3))
#define HW_GYBFD_OFF		((u8)(ClrD3))
#define HW_HW_GYBDZ_MASK	((u8)((ClrD5&ClrD4)))

#define HW_GYB_0R			((u8)(SetD4|SetD5))//测试
#define HW_GYB_10KR			((u8)(ClrD4&ClrD5))//测试
#define HW_GYB_100KR		((u8)(SetD4))//测试

//==========================================================

#define FIT_INUM    12  //滤波次数
#define STEP_MAX			(4)//最大步骤(0-3)

#define GROUP_MAX			(8)//最大组别

#define IDLE_MENU_MAX  		(4)//最大待机菜单
#define IDLE_MENU_PAGE 		(4)//每页待机菜单

#define PARAMETER_MENU_MAX	(13)//最大参数菜单
#define PARAMETER_MENU_PAGE	(4)//每页参数菜单

#define PARAMETER_ACW_MAX	(8)//ACW参数项(0-7)
#define PARAMETER_DCW_MAX	(8)//DCW参数项(0-7)
#define PARAMETER_IR_MAX	(6)//IR参数项(0-5)
#define PARAMETER_GND_MAX	(7)//ACW参数项(0-6)

#define SYSTEM_MENU_MAX		(10)//最大系统菜单(0-5)
#define SYSTEM_MENU_PAGE	(4)//每页系统菜单

#define CONFIG_MENU_MAX		(3)//最大配置项(0-2)

#define PW_LENGTH 			(4)//最大密码位数

#define AD_BUF_LENGTH		(8)//A/D值缓冲区长度


#define MAXTSOFTTIMER (2)		//软定时器数目


//==========================================================
//软件版本：10
#define SOFTWARE_VERSION		(0x10)

//==========================================================
//默认出厂编号(0)
#define DEFAULT_MACHINE_ID 		(0)

//默认出厂密码(0)
#define DEFAULT_PASSWORD 		(0)

//默认开机次数(0)
#define SET_BOOT_DEFAULT		(0)





//AD值滤波配置，增加数据稳定度
#define AD_FILTER_SUPPORT		(_DEBUG_CONFIG_TRUE)

//==========================================================
#define SETUP_MENU_MAX  	(2)//最大设置菜单

//#define PARAMETER_MENU_MAX	(5)//最大参数菜单

//#define SYSTEM_MENU_MAX		(2)//最大系统菜单

#define CONFIG_MENU_MAX		(3)//最大配置项(0-2)

#define PW_LENGTH 			(4)//最大密码位数

#define RANGE_MAX 			(5-1)//最大量程

#define AD_BUF_LENGTH		(8)//A/D值缓冲区长度

//==========================================================
#define OHM 				(0xF4)	//CGROM中有Ω字符，编码为0xF4

//==========================================================
//显示分区的X坐标
#define MSG_ADDR_X 			(0)
#define AUTO_ADDR_X 		(12)
#define RANGE_ADDR_X 		(17)
#define GROUP_ADDR_X 		(7)
#define TIME_ADDR_X 		(10)
#define V_ADDR_X 			(0)

#define RES_ADDR_X 			(9)
#define VOL_ADDR_X 			(V_ADDR_X)
#define TIM_ADDR_X 			(TIME_ADDR_X)
#define RAN_ADDR_X			(7)

#define AD_MAX (4095) //12bit=4096-1

//电流量程上下限
#define RANGR_LIMIT_HIGH (3800)
#define RANGR_LIMIT_LOW  (360)
//==========================================================
//标准电压DA   50V   500V
//==========================================================
#define  CAL_50V		(3000)
#define  CAL_500V		(3000)

//软定时器定义
#define KEYBOARD_SOFTTIMER	(0) //按键延时软定时器
#define DISP_SOFTTIMER 		(1) //显示延时软定时器

//==========================================================
//标题长度
#define LIST_TITLE_LEN		(8)
#define TITLE_LEN_MAX		(8)
#define SetSystemStatus(status) (SystemStatus=status)
#define GetSystemStatus() (SystemStatus)
#define GetSystemMessage() (SystemMessage)
#define SetSystemMessage(msg) (SystemMessage=msg)

#define SET_GROUP_MAX GROUP_MAX
//==========================================================
//系统状态
enum SysStatusEnum
{	
	SYS_STATUS_ERROR ,			//异常
	SYS_STATUS_RESET ,			//复位
	SYS_STATUS_POWER ,			//开机
	SYS_STATUS_IDLE ,			//待机
	SYS_STATUS_SETUP ,			//设置
	SYS_STATUS_START ,			//启动
	SYS_STATUS_TEST ,			//测试
	SYS_STATUS_TEST_PAUSE ,		//暂停
	SYS_STATUS_TEST_FINISH ,	//结束
	SYS_STATUS_DEBUG ,			//调试
};
enum Setup_Group_Item
{
	I_SETUP=1,
	W_SETUP=0,
	I_WSETUP=3,
	W_ISETUP=2,

};
//==========================================================
//系统消息
enum SysMessageEnum_I
{
	MSG_IDLE=0 , 
	MSG_RAMP , 
	MSG_TEST , 
	MSG_PAUSE , 
	MSG_PASS ,
	MSG_ARC , 
	MSG_HIGH , 
	MSG_LOW , 
	MSG_OVER , 
	MSG_ERROR ,
	MSG_OFL ,
};

//上位机返回状态消息
enum UartMessageEnum
{
	W_PASS=0 , 
	W_STOP, 
	W_F_HI , 
	W_F_LO , 
	W_ARC,
	W_OVER,
	I_PASS,
	I_STOP,
	I_HIGH,
	I_LO,

};

extern u16 rangelomit_low,rangr_limit_high;
//数值框属性定义
typedef struct
{
	vu8 *Title;//标题
	vu16 Num;//数值
	vu8  Dot;//小数点(0-3: xxxx xxx.x xx.xx x.xxx)
	//vu8  Unit;//单位(0-2: MΩ  GΩ  TΩ)
	vu16 Max;//最大值
	vu16 Min;//最小值
	vu16 Len;//显示的数据长度
}NumBox_TypeDef;
extern NumBox_TypeDef NumBox;//数值框

//项目值																					   
enum ItemEnum
{	
	ITEM_ACW ,
	ITEM_DCW ,
	ITEM_IR ,
	ITEM_GND ,
	ITEM_NONE ,
};
//==========================================================
//浮点数转换  
typedef struct
{
	u8 Sign;//正负号
	u32 Digit;//尾数
	s8 Exponent;//阶码

}Float_TypeDef;
extern Float_TypeDef Float;
//==========================================================
//校正值
typedef struct 
{
	vu16 Num;  //输出值
	vu16 NumAd;//输出A/D值
}Cal_TypeDef;
extern Cal_TypeDef Cal[11];//校准值
//校正项
typedef struct 
{
//	Cal_TypeDef IRVol[2];//绝缘电压档  0  50V  1  500V
//	Cal_TypeDef IRCur[8];// 0 1K采样电阻档 1  10K  2  100K  3  1000K   4 10M   5  80M 6 64M   7  128M
    Cal_TypeDef AcwVol[1];//交流耐压电压值-1档
	
	Cal_TypeDef DcwVol[1];//只流耐压电压值-1档
	Cal_TypeDef IrVol[1];//绝缘电阻电压值-1档
	Cal_TypeDef AcwCur[2];//交流耐压电流值-2档
	
	Cal_TypeDef DcwCur[2];//直流耐压电流值-2档
	
	Cal_TypeDef IrCur[4];//绝缘电阻电流值-4档
//	Cal_TypeDef GndVol[1];//接地电阻电压值-1档
//	Cal_TypeDef GndCur[1];//接地电阻电流值-1档
	
}Calibrate_TypeDef;
extern Calibrate_TypeDef Calibrate;
typedef struct
{
	vu16 set_item;//测试项目
	vu16 set_time;//设置的测试时间
	vu16 set_ramp;//设置的缓升或延时时间
	vu16 set_high;//设置的上限
	vu16 set_low;//设置的下限

}Test_mid_Typedef;
extern Test_mid_Typedef Test_mid;
//==========================================================
//配置项(3项)
typedef struct 
{
	vu16 BootNum;//开机次数(0-9999，默认0)
	vu16 ProductId;//出厂编号(0-9999，默认0)
	vu16 Password;//设置密码(0-9999，默认0)
}Factory_TypeDef;
//==========================================================
//系统项(2项)
typedef struct 
{ 
	vu16 value;	//数值
	vu8 dot;	//小数点 0 1 2 3    xxxx   xxx.x  xx.xx x.xxx
	vu8 unit;	//单位 0 1 2 3   MΩ    GΩ   TΩ  
	

}SystemRes_TypeDef;
//==========================================================
//系统项(4项)
//typedef struct 
//{
//	vu16 Vol_Out;	//输出电压(10-1000 V)
//	vu16 Set_Time;	//测试时间(0-999.9s)
//	vu16 Res_Hi;	//上限(xxxx MΩ)
//	vu16 Res_Lo;	//下限(xxxx MΩ)

//}System_TypeDef;
typedef struct 
{
	vu32 Test_v;	//测试电压(10-1000 V)
	vu8 dot;	//小数点位

}Test_VTypeDef;
typedef struct
{
	float v;
	float i;
	float r;
	u32 rate;

}Res_countTypeDef;
extern Res_countTypeDef Res_count;
typedef struct 
{
	vu16 Test_Res;	//测试电压(10-1000 V)
	vu8 dot;	//小数点位
	vu8 unit;

}Test_RESTypeDef;
//==========================================================
//系统项(2项)
typedef struct 
{
	Test_VTypeDef Test_v;	//测试电压(10-1000 V)
	vu16 Test_Time;	//测试时间(0-999.9s)
	Test_RESTypeDef Test_Res;	//测试电阻(xxxx MΩ)
	vu16 Test_I;

}Test_TypeDef;
extern Test_TypeDef Test_value;
//==========================================================
//
//==========================================================
//配置项(3项)
typedef struct 
{
	vu16 Password;//设置密码(0-9999，默认0)
	vu16 BootNum;//开机次数(0-9999，默认0)
	vu16 ProductId;//出厂编号(0-9999，默认0)
}Config_TypeDef;
//==========================================================
//参数项(5项)
typedef struct 
{
	vu8 Range;//量程模式(0-7，默认0自动)
	vu8 Beep;//讯响模式(0-2，默认开1-PassOn)
	vu8 ClrOn;//清零开关(0-1，默认关0)
	
	vu8 ExTrig;//外部触发开关(0-1，默认关0)
	vu8 UartOn;//串口开关(0-1，默认关0)
//	vu8 FastOn;//快速测试(0-1，默认关0)
}Parameter_TypeDef;

//数值框属性定义
//系统项(6项)
typedef struct 
{
	vu8 Uart;//串口开关(0-1，默认关0)
	vu8 Freq60;//交流频率(0-1，默认0-50Hz)
	vu8 Connect;//连接开关(0-1，默认开1)
	vu8 ConnectTime;//连接时间(xxx.x S)

	vu8 Beep;//讯响开关(0-1，默认开1)
	vu8 FailPause;//失败暂停开关(0-1，默认关0)
//	vu8 BarScan;//条码扫描开关(0-1，默认关0)

}System_TypeDef;
//通用参数项(8项)
typedef struct 
{
	vu16 Group_Item;//选择测试项目包括连接
	vu16 Item;//项目 选择AD/DC
	vu16 Output;//电压输出
	vu16 High;//上限
	vu16 Low;//下限
	vu16 RampDelay;//缓升时间/判别延时(xxx.x S)
	vu16 TestTime;//测试时间(xxx.x S)
	vu16 Freq;//频率选择
	//vu16 Connect=1;
	//vu16 Zero;//零值
	vu16 Arc;//电弧等级(0-9，默认0-关闭)
	vu16 I_Volt;
	vu16 I_High;
	vu16 I_Low;
	vu16 I_Delay;

}Setup_TypeDef;
//==========================================================
//保存信息
typedef struct 
{
    u8 Group;//组别
    Setup_TypeDef Setup; //各步骤的设置项
    //System_TypeDef System;//系统项
    //Factory_TypeDef Factory;//出厂项
	//Parameter_TypeDef Parameter;//参数项
	//Config_TypeDef Config;//配置项
	Calibrate_TypeDef Calibrate;//校准项
	//vu16 Crc16;//校验字
	u8 pselect;
	u8 devaddr;
	
}Save_TypeDef;
extern bool F_Fail;//测试失败标志
extern bool F_100ms;//100ms定时标志
extern bool F_Password;//密码有效标志
extern Save_TypeDef SaveData;//保存值
extern vu32 Voltage;//电压
extern vu32 Test_Time;//电流
extern vu32 Resistance;//电阻
extern u8 SoftTimer[MAXTSOFTTIMER];
extern u8 ra_flag;
extern float i_buff[FIT_INUM];		   //滤波值
#endif
