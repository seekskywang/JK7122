//==========================================================
//文件名称：Test.c
//文件描述：测试程序
//文件版本：Ver1.0
//创建日期：2014.12.29
//修改日期：2015.09.06 15:06
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
////#include <absacc.h>
////#include <intrins.h>

////#include "TypeDefine.h"
//#include "GlobalValue.h"
//#include "Hardware.h"
//#include "Delay.h"
//#include "Interrupt.h"
//#include "Beep.h"
//#include "Keyboard.h"
//#include "Isp.h"
//#include "Lcd240128.h"
//#include "Disp.h"
//#include "Uart0.h"
//#include "Com.h"
//#include "User.h"
//#include "Test.h"
#include "pbdata.h"
#include <stdlib.h>
#include <stdio.h>
//==========================================================
#define POWERON_DISP_TIME ((u8)20)	//开机显示界面延时20*100mS=2S

void SendRes(void);
void SendRes1(void);	
const u8 IR_Range_dot[5]={3,2,1,0,0};
char sendbuff[20];
char sendbuffold[20];
char sendbuff1[20];
char sendbuff2[20];
char sendbuff3[20];
u8 strbuff[8];
u8 respond;
u8 multstep;
u8 sendflag;
u8 sendcheck;
char sendend[2] = {0x0d,0x0a};
union U1
{
    uint8_t s[4];
    float sendI;
};

union U1 USENDI;

union 
{
   u8 w_ma;
	
   struct 
   {
	   unsigned char  ARC:4;	   //电弧灵敏度0000，关闭电弧检测，1001最高
	   unsigned char  ACWF:1;    //交流耐压频率：1表示60Hz，0表示50Hz
	   unsigned char  ACDC:1;    //交流0，直流1
       unsigned char  item:2;    //测试项目
      
       
      
   }BIT_FLAG;
}U2;

//==========================================================
//函数名称：Power_Process
//函数功能：上电处理
//入口参数：无
//出口参数：无
//创建日期：2014.12.29
//修改日期：2015.08.18 10:20
//备注说明：开机长按SET进入校准调试模式
//==========================================================
void Power_Process(void)
{
	u8 i;
	u8 key;
	
	Hardware_Init();//硬件初始化
	Amp_Output_Off();//功放输出关闭
	Sin_Clk_Disable();//禁止正弦波频率输出

	InitGlobalValue();//初始化全局变量
	ReadGroup();
	ReadGroup();
	ReadSetByGroup();
	ReadPselect();
//	Readaddr();
	ReadCalData();//读取保存数据
	Parameter_valuecomp();//比较设置参数
	if(SaveData.Group>GROUP_MAX)
		SaveData.Group=0;
//	SaveData.Factory.BootNum++;//开机次数	
//	SaveFactory();//保存开机次数

	
	Beep_Long();//蜂鸣器长响一声
	Beep_Off();
	Disp_PowerOn_Menu();//显示开机界面

	MenuIndex=0;//待机菜单项
	i=0;//显示延时

	while(GetSystemStatus()==SYS_STATUS_POWER)
	{
		i++;
		if(i>POWERON_DISP_TIME)//延时20*100mS=2s后自动退出
			SetSystemStatus(SYS_STATUS_IDLE);//待测状态
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)

		switch(key)
		{
			case KEY_LEFT:
			case L_KEY_LEFT:
				SetSystemStatus(SYS_STATUS_DEBUG);//调试状态
				Beep_One();//蜂鸣器响一声
				
			break;
			case KEY_SET:		//设置键
			case L_KEY_SET:		//长按设置键
				
				break;
	
			case KEY_UP:		//上键
			case L_KEY_UP:		//长按上键
				break;
	
			case KEY_DOWN:		//下键
			case L_KEY_DOWN:	//长按下键
				break;
	
//			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
//				break;

			case KEY_RIGHT:		//右键
			case L_KEY_RIGHT:	//长按右键
				break;

			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				break;
	
			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				i=POWERON_DISP_TIME;//显示延时结束
				break;
			
			default:
				break;
		}
	}
	Amp_Output_On();//功放输出开
}

//==========================================================
//函数名称：Idle_Process
//函数功能：待测主程序
//入口参数：无
//出口参数：无
//创建日期：2014.12.15
//修改日期：2015.08.20 10:49
//备注说明：无
//==========================================================
void Idle_Process(void)
{
	u8 key;
	u8 index;

	//系统信息更新
	SetSystemMessage(MSG_IDLE);//系统信息-待机
	Disp_Idle_Menu();//显示待测界面
	Led_Fail_Off();
	Led_Pass_Off();
	run_stemp=0;
	
	while(GetSystemStatus()==SYS_STATUS_IDLE)
	{
		if(/*ComBuf.rec.end || */FacBuf.rec.end)
		{
			Uart_Process();//串口处理
		}
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
				SetSystemStatus(SYS_STATUS_SETUP);//设置状态
				break;
	
			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
				if(MenuIndex==0)//参数设置菜单
				{
//					if(Password_Check())//密码校验,TRUE有效
					{
						SaveData.Group++;
						if(SaveData.Group>SET_GROUP_MAX)
							SaveData.Group=0;
						ReadSetByGroup();//读取当前组别的测试参数
						Parameter_valuecomp();//比较设置参数
						SaveGroup();//保存组别
						Disp_Clr( );//清屏
						Disp_Idle_Menu();//显示待测界面
					}
				}
				break;
	
			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
				if(MenuIndex==0)//参数设置菜单
				{
//					if(Password_Check())//密码校验,TRUE有效
					{
						if(SaveData.Group)
							SaveData.Group--;
						else
							SaveData.Group=SET_GROUP_MAX;
						ReadSetByGroup();//读取当前组别的测试参数
						Parameter_valuecomp();//比较设置参数
						SaveGroup();//保存组别
						Disp_Clr( );//清屏
						Disp_Idle_Menu();//显示待测界面
					}
				}
				break;
	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
				index=MenuIndex?MenuIndex-1:(IDLE_MENU_MAX-1);
				MenuIndex=index;
//				Disp_Idle_List();//显示待机菜单列表
				break;

			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				index=(MenuIndex<(IDLE_MENU_MAX-1))?MenuIndex+1:0;
				MenuIndex=index;
//				Disp_Idle_List();//显示待机菜单列表
				break;

			case KEY_START:		//启动键
			case L_KEY_START:	//长按启动键
//				if(SaveData.System.Uart!=TRUE)//串口开始时启动键无效
					SetSystemStatus(SYS_STATUS_START);//启动测试状态
			F_Fail=0;
				break;
	
			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
//				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				MenuIndex=0;//待机菜单项
			F_Fail=0;
//				Disp_Idle_List();//显示待机菜单列表
				break;
			
			default:
				break;
		}
	}
}


//==========================================================
//函数名称：Setup_Process
//函数功能：设置程序
//入口参数：无
//出口参数：无
//创建日期：2015.01.06
//修改日期：2015.08.19 08:56
//备注说明：无
//==========================================================
void Setup_Process(void)
{
	
		
		Step_Setup();//步骤设置处理
	
	

}

//==========================================================
//函数名称：Start_Process
//函数功能：启动测试处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.26
//修改日期：2015.08.22 15:42
//备注说明：无
//注意事项：无
//==========================================================
void Start_Process(void)
{
	while(GetSystemStatus()==SYS_STATUS_START)
	{
		//全局变量处理
		StepIndex=0;//第一步开始
		TotalStep=0;//测试总步骤
		F_Fail=FALSE;//清测试失败标志

		//状态控制
		Da_Out(0);//主信号D/A输出关闭
		Sin_Clk_Disable();//禁止正弦波频率输出
		

		//系统状态更新
		SetSystemMessage(MSG_RAMP);//系统信息-缓升
		SetSystemStatus(SYS_STATUS_TEST);//系统状态-测试
	}
}

//==========================================================
//函数名称：Output_Off
//函数功能：输出关闭
//入口参数：无
//出口参数：无
//创建日期：2015.09.01 
//修改日期：2015.09.04 14:59
//备注说明：无
//==========================================================
void Output_Off(void)
{
	Da_Out(0);//主信号D/A输出关闭
	Sin_Clk_Disable();//禁止正弦波频率输出
	delay_ms(100);//延时100ms
	Led_HV_Off();//关闭高压灯
}

//==========================================================
//函数名称：Test_Init
//函数功能：测试初始化
//入口参数：无
//出口参数：无
//创建日期：2015.01.25 
//修改日期：2015.08.26 13:48
//备注说明：耗时约100ms/12M
//==========================================================
void Test_Init(void)
{
	u8 i;
	u8 len;
	u8 *pt;
	u8 *pt2;
	u32 dat;
	u16 set_item;//设置的输出项目
	u16 set_out;//设置的输出值
	u16 set_ramp;//设置的缓升或延时时间
	vu8 set_arc;//设置的电弧等级
	vu8 set_acdc;//选择AD还是DC

	//系统信息更新
	SetSystemMessage(MSG_RAMP);//系统信息-缓升

	//读取设置值
	
	
	set_item=SaveData.Setup.Group_Item;//当前参数
	set_acdc=SaveData.Setup.Item;
	
	U2.BIT_FLAG.ACDC = SaveData.Setup.Item;//上位机返回w_ma:d5
	
	set_arc=(u8)SaveData.Setup.Arc;//电弧等级
	Arc_Out(0);
	//读取校准值
	if(set_item==W_SETUP)
	{
		Range=0;
		ra_flag=0;
		set_out=SaveData.Setup.Output*10;//设置的输出
		if(SaveData.Setup.RampDelay == 1)
		{
			set_ramp = 2;
		}else{
			set_ramp=SaveData.Setup.RampDelay;//缓升或延时时间
		}
		dat=set_out;
		i=3;//ACW
		rangelomit_low=240;
			rangr_limit_high=3800;
		if(set_acdc==0)//AC
		{
		
			//pt=(u8*)(&SaveData.Calibrate.AcwVol);//校准值首地址
			
			dat*=DefaultCalDaOut[0];
			dat/=SaveData.Calibrate.AcwVol[0].Num;
			
			
		}
		else
		{
			//pt=(u8*)(&SaveData.Calibrate.DcwVol);//校准值首地址
			dat*=DefaultCalDaOut[1];
			dat/=SaveData.Calibrate.DcwVol[0].Num;
		}
	}
	else if(set_item==I_SETUP)//绝缘
	{
		rangelomit_low=360;
			rangr_limit_high=3800;
		ra_flag=1;
		set_ramp=0;//缓升或延时时间
		set_out=SaveData.Setup.I_Volt*10;//设置的输出
		dat=set_out;
		i=5;//IR
		//pt=(u8*)(&SaveData.Calibrate.IrVol);//校准值首地址
		dat*=DefaultCalDaOut[2];
		dat/=SaveData.Calibrate.IrVol[0].Num;
		set_ramp=0;
		
	}
	else if(set_item==I_WSETUP)
	{
		set_out=SaveData.Setup.I_Volt*10;//设置的输出
		if(SaveData.Setup.RampDelay == 1)
		{
			set_ramp = 2;
		}else{
			set_ramp=SaveData.Setup.RampDelay;//缓升或延时时间
		}
		dat=set_out;
		if(run_stemp==0)
		{
			rangelomit_low=360;
			rangr_limit_high=3800;
			ra_flag=1;
		
			i=5;//IR
			set_ramp=0;//缓升或延时时间=0
			//pt=(u8*)(&SaveData.Calibrate.IrVol);//校准值首地址
			dat*=DefaultCalDaOut[2];
			dat/=SaveData.Calibrate.IrVol[0].Num;
			set_ramp=0;
		}
		else
		{
			Range=0;
			rangelomit_low=240;
			rangr_limit_high=3800;
			ra_flag=0;
			set_out=SaveData.Setup.Output*10;//设置的输出
			dat=set_out;
			
			i=3;//ACW
			if(set_acdc==0)//AC
			{
			
				//pt=(u8*)(&SaveData.Calibrate.AcwVol);//校准值首地址
				dat*=DefaultCalDaOut[0];
				dat/=SaveData.Calibrate.AcwVol[0].Num;
				
			}
			else
			{
				//pt=(u8*)(&SaveData.Calibrate.DcwVol);//校准值首地址
				dat*=DefaultCalDaOut[1];
				dat/=SaveData.Calibrate.DcwVol[0].Num;
			}
		
		}
		
	}
	else
	{
		if(run_stemp==0)
		{
			Range=0;
			rangelomit_low=240;
			rangr_limit_high=3800;
			if(SaveData.Setup.RampDelay == 1)
			{
				set_ramp = 2;
			}else{
				set_ramp=SaveData.Setup.RampDelay;//缓升或延时时间
			}
			set_out=SaveData.Setup.Output*10;//设置的输出
			dat=set_out;
			i=3;//ACW
			ra_flag=0;
			if(set_acdc==0)//AC
			{
				
				dat*=DefaultCalDaOut[0];
				dat/=SaveData.Calibrate.AcwVol[0].Num;
				//pt=(u8*)(&SaveData.Calibrate.AcwVol);//校准值首地址
				
			}
			else
			{
				dat*=DefaultCalDaOut[1];
				dat/=SaveData.Calibrate.DcwVol[0].Num;
				//pt=(u8*)(&SaveData.Calibrate.DcwVol);//校准值首地址
			}
		
		}else
		{
			rangelomit_low=360;
			rangr_limit_high=3800;
			set_ramp=0;//缓升或延时时间
			set_out=SaveData.Setup.I_Volt*10;//设置的输出
			dat=set_out;
			i=5;//IR
			ra_flag=1;
			//pt=(u8*)(&SaveData.Calibrate.IrVol);//校准值首地址
			dat*=DefaultCalDaOut[2];
			dat/=SaveData.Calibrate.IrVol[0].Num;
		
			set_ramp=0;
		}
		
	}
//	
	pt=(u8*)((&SaveData.Calibrate));
	len=11;
	pt2=(u8*)(&Cal);//更新通用校准值
	len=11*sizeof(Cal_TypeDef);
	for(i=0;i<len;i++)
	{
		*pt2++=*pt++;
	}

	//全局变量处理
	Voltage=0;//电压
	Current=0;//电流
	Resistance=0;//电阻
	TestTime=0;//时间
 	AdCount=0;//A/D值采样计数

	RampStepYs=0;//缓升步进余数
	RampStepFd=0;//缓升步进幅度
	RampStepTime=0;//缓升步进时间
	TestOut=0;//测试输出
	FullOut=0;//满载输出
	F_100ms=FALSE;//100ms定时
	
	//AD缓冲区清空
	for(i=0;i<(AD_BUF_LENGTH);i++)
	{
		Vbuf[i]=0;
		Ibuf[i]=0;
	}

	//满载D/A输出值计算
	
	
	
	FullOut=(u16)dat;

	//缓升值计算
	if(set_ramp)//缓升时间
	{
		RampStepTime=1;//缓升步进时间,100ms
		dat=FullOut;dat/=set_ramp;
		RampStepFd=(u16)dat;//缓升步进幅度
		dat=FullOut;dat%=set_ramp;
		RampStepYs=(u16)dat;//缓升步进余数
		if(RampStepFd<1)
		{
			RampStepTime=10;//缓升步进时间,1s
			dat=FullOut;dat*=10;dat/=set_ramp;
			RampStepFd=(u16)dat;//缓升步进幅度
			dat=FullOut;dat*=10;dat%=set_ramp;
			RampStepYs=(u16)dat;//缓升步进余数
			if(RampStepFd<1)
			{
				RampStepTime=100;//缓升步进时间,10s
				dat=FullOut;dat*=10;dat/=set_ramp;
				RampStepFd=(u16)dat;//缓升步进幅度
				dat=FullOut;dat*=10;dat%=set_ramp;
				RampStepYs=(u16)dat;//缓升步进余数
			}
		}
	}
//	Dma_Int();
	
	//输出控制
	switch(set_item)//参数
	{
		case I_SETUP:
			Dc_Output_On();//DC输出和采样
			Frequency_Control(FREQ_400);//输出频率控制
			SetSystemMessage(MSG_TEST);//系统信息-满载测试
		
		

			break;

		case W_SETUP:
			if(set_acdc)//直流
			{
				Dc_Output_On();//DC输出和采样
				Frequency_Control(FREQ_400);//输出频率控制
				Arc_Out(set_arc);//电弧等级输出
			}
			else
			{
				Dc_Output_Off();//DC输出和采样关闭
				if(SaveData.Setup.Freq)
					Frequency_Control(FREQ_60);//输出频率控制
				else
					Frequency_Control(FREQ_50);//输出频率控制
				Arc_Out(set_arc);//电弧等级输出
			
			}
			break;

		case I_WSETUP:
			if(run_stemp==0)
			{
				Dc_Output_On();//DC输出和采样
				Frequency_Control(FREQ_400);//输出频率控制
				SetSystemMessage(MSG_TEST);//系统信息-满载测试
				
			}
			else
			{
			
				if(set_acdc)//直流
				{
					Dc_Output_On();//DC输出和采样
					Frequency_Control(FREQ_400);//输出频率控制
					Arc_Out(set_arc);//电弧等级输出
				}
				else
				{
					Dc_Output_Off();//DC输出和采样关闭
					if(SaveData.Setup.Freq)
						Frequency_Control(FREQ_60);//输出频率控制
					else
						Frequency_Control(FREQ_50);//输出频率控制
					Arc_Out(set_arc);//电弧等级输出
				
				}
			}
			break;

		case W_ISETUP:
			if(run_stemp==0)
			{
				if(set_acdc)//直流
				{
					Dc_Output_On();//DC输出和采样
					Frequency_Control(FREQ_400);//输出频率控制
					Arc_Out(set_arc);//电弧等级输出
				}
				else
				{
					Dc_Output_Off();//DC输出和采样关闭
					if(SaveData.Setup.Freq)
						Frequency_Control(FREQ_60);//输出频率控制
					else
						Frequency_Control(FREQ_50);//输出频率控制
					Arc_Out(set_arc);//电弧等级输出
				
				}
			}else
				{
					Dc_Output_On();//DC输出和采样
					Frequency_Control(FREQ_400);//输出频率控制
					SetSystemMessage(MSG_TEST);//系统信息-满载测试
				}
			break;
	
		default:
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//测试暂停状态
			return;
			
	}	
	
	Da_Out(0);
	Sin_Clk_Enable();//输出正弦波频率
	Plc_Start_On();//开PLC启动
 	Range=0;//量程初始化
	Range_Control(Range);//量程控制
	

	//声光状态控制
	Led_Pass_Off();//关合格灯
	Led_Fail_Off();//关报警灯
	Led_HV_On();//开高压灯
//	if(SaveData.System.Beep)
//		Beep_One();//响一声

	//显示测试界面
	LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//	Disp_Str("测试中..",0);//显示测试状态
	//显示测试参数
	LcdAddr.x=TITLE_ADDR_X+14; LcdAddr.y=TITLE_ADDR_Y;
//	Disp_Str(&ItemTab[set_item],0);//显示参数

	//显示隔离线
//	Lcd_Draw_Line(0,TITLE_ADDR_Y+18,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	Lcd_Draw_Line(0,TITLE_ADDR_Y+20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度

	//显示步骤序号
	LcdAddr.x=STEP_ADDR_X; LcdAddr.y=STEP_ADDR_Y+TotalStep*HEIGHT_OF_STEP;
//	Disp_Str(&NumTab[TotalStep][0],0);//显示测试总步骤
//	Disp_Str(&ItemCharTab[set_item],0);//显示参数缩写字符

	//显示初始化
	LcdAddr.x=DATA_ADDR_X; LcdAddr.y=DATA_ADDR_Y+HEIGHT_OF_STEP*TotalStep;
	switch(set_item)//按项目显示
	{
		case ITEM_ACW:
		case ITEM_DCW:
//			Disp_Txt_Str("-----V -----mA -----s ");//显示测试值
			break;

		case ITEM_IR:
//			Disp_Txt_Str("----V  ----M  -----s ");//显示测试值
			break;

		case ITEM_GND:
//			Disp_Txt_Str("-----A ----m  -----s ");//显示测试值
			break;
		
		default:
			break;
	}

	//显示测试信息
	LcdAddr.x=MSG_ADDR_X;
	Disp_SysMessage();//显示信息

}

//==========================================================
//函数名称：Test_Process
//函数功能：测试主程序
//入口参数：无
//出口参数：无
//创建日期：2015.01.25 
//修改日期：2015.09.06 15:06
//备注说明：数值刷新8.4ms，状态刷新3.6ms，12MHz/12周期
//备注说明：缺少电弧中断、过流中断处理
//==========================================================
void Test_Process(void)
{
	vu8 key;
	vu8 max;//最大量程
	vu16 sortT;//分选延时
	vu8 stepT;//步进时间计时
	vu8 blinkT;//闪烁时间计时
//	char sendbuff[20];
	vu32 dat;
	vu32 temp;

	bool f_disp=FALSE;//显示更新标志
	bool f_msgdisp=FALSE;//消息显示标志

	bool f_sort=FALSE;//分选标志
	bool f_upper=FALSE;//量程过压标志
	bool f_below=FALSE;//量程欠压标志
	bool f_switch=FALSE;//量程切换标志

	vu16 set_item;//测试项目
//	vu16 set_time;//设置的测试时间
//	vu16 set_ramp;//设置的缓升或延时时间
//	vu16 set_high;//设置的上限
//	vu16 set_low;//设置的下限
	vu16 set_zero;//设置的零值

//	Check_Parameter_Limit(StepIndex);//当前步骤的参数设置值检查

	//更新设置值
	Test_mid.set_item=SaveData.Setup.Group_Item;//当前参数
//	set_high=SaveData.Setup[StepIndex].High;//设置的上限
//	set_low=SaveData.Setup[StepIndex].Low;//设置的下限
//	set_time=SaveData.Setup[StepIndex].TestTime;//测试时间
//	set_ramp=SaveData.Setup[StepIndex].RampDelay;//缓升或延时时间
//	set_zero=SaveData.Setup[StepIndex].Zero;//零值
//	
	//设置值处理
	switch(Test_mid.set_item)//项目
	{
		case I_SETUP://绝缘电阻测试
			U2.BIT_FLAG.item = 1;
			Test_mid.set_high=SaveData.Setup.I_High;
			Test_mid.set_low=SaveData.Setup.I_Low;
			Test_mid.set_time=SaveData.Setup.I_Delay;
			max=2;//最大量程-4档
			break;

		case W_SETUP://耐压测试
			U2.BIT_FLAG.item = 0;
			Test_mid.set_high=SaveData.Setup.High;
			Test_mid.set_low=SaveData.Setup.Low;
			Test_mid.set_time=SaveData.Setup.TestTime;
			if(SaveData.Setup.RampDelay == 1)
			{
				Test_mid.set_ramp = 2;
			}else{
				Test_mid.set_ramp=SaveData.Setup.RampDelay;
			}
			set_item=SaveData.Setup.Item;
		
//			max=1;//最大量程-2档
			max=0;
			break;

		case I_WSETUP://绝缘耐压测试
			U2.BIT_FLAG.item = 3;
			if(run_stemp==0)
			{
				Test_mid.set_high=SaveData.Setup.I_High;
				Test_mid.set_low=SaveData.Setup.I_Low;
				Test_mid.set_time=SaveData.Setup.I_Delay;
				max=2;//最大量程-4档
				
			}
			else
			{
				max=0;
//				max=1;
				Test_mid.set_high=SaveData.Setup.High;
				Test_mid.set_low=SaveData.Setup.Low;
				Test_mid.set_time=SaveData.Setup.TestTime;
				if(SaveData.Setup.RampDelay == 1)
				{
					Test_mid.set_ramp = 2;
				}else{
					Test_mid.set_ramp=SaveData.Setup.RampDelay;
				}
				
			}
			//set_zero=0;
			break;

		case W_ISETUP://耐压绝缘测试
			U2.BIT_FLAG.item = 2;
			if(run_stemp==0)
			{
				max=0;
//				max=1;//最大量程-1档
				Test_mid.set_high=SaveData.Setup.High;
				Test_mid.set_low=SaveData.Setup.Low;
				Test_mid.set_time=SaveData.Setup.TestTime;
				if(SaveData.Setup.RampDelay == 1)
				{
					Test_mid.set_ramp = 2;
				}else{
					Test_mid.set_ramp=SaveData.Setup.RampDelay;
				}
				
			}
			else
			{
				max=2;
				Test_mid.set_high=SaveData.Setup.I_High;
				Test_mid.set_low=SaveData.Setup.I_Low;
				Test_mid.set_time=SaveData.Setup.I_Delay;
				
			}
			break;

		case ITEM_NONE://无测试项目
			break;

		default:
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-暂停测试
			return;
			
	}		
	
	Test_Init();//测试初始化
	

	stepT=0;//步进时间计时
	sortT=0;//分选延时
	blinkT=0;//闪烁时间计时
	Test_Time=0;
	Test_value.Test_Time=0;
	TestOut=0;
	Range=max;
	Range_Control(Range+ra_flag);
	while(GetSystemStatus()==SYS_STATUS_TEST)
	{
		sendflag = 0;
		if(F_100ms==TRUE)//100ms定时处理
		{
			F_100ms=FALSE;
			f_disp=TRUE;//显示更新

			if(sortT<9999)sortT++;

			if(GetSystemMessage()==MSG_RAMP)//系统信息-缓升
			{
				stepT++;//步进时间计时
				if(stepT>=RampStepTime)//缓升步进时间
				{
					stepT=0;//步进时间计时
					TestOut+=RampStepFd;//测试输出值计算
//					if(RampStepYs)//缓升步进余数  错误
//					{
//						TestOut+=RampStepYs;//测试输出值计算
//					  	RampStepYs--;//缓升步进余数
//					}
				}
				

				if(Test_value.Test_Time>=Test_mid.set_ramp)//缓升时间判别
				{
					Test_value.Test_Time=0;//测试时间清零
					TestOut=FullOut;//测试输出值计算
					SetSystemMessage(MSG_TEST);//系统信息-满载测试
					f_msgdisp=TRUE;//消息显示标志
				}
			}
			else
			{
				TestOut=FullOut;//测试输出值计算
				if(Test_mid.set_time>0)//测试时间为0，连续测试
				{
					if(Test_value.Test_Time>=Test_mid.set_time)//测试时间判别
					{
						if(Test_mid.set_item == W_SETUP 
						|| (Test_mid.set_item == W_ISETUP && run_stemp == 0)
						|| (Test_mid.set_item == I_WSETUP && run_stemp == 1))
						{
							if(Voltage < SaveData.Setup.Output*0.8)
							{
								f_sort=TRUE;//分选标志
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = W_F_LO;
							}else{
								SetSystemStatus(SYS_STATUS_TEST_PAUSE);//测试暂停状态
								SetSystemMessage(MSG_PASS);//系统信息-测试合格
								f_msgdisp=TRUE;//消息显示标志
							}
						}else{
							if(Voltage < SaveData.Setup.I_Volt*0.8)
							{
								f_sort=TRUE;//分选标志
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = W_F_LO;
							}else{
								SetSystemStatus(SYS_STATUS_TEST_PAUSE);//测试暂停状态
								SetSystemMessage(MSG_PASS);//系统信息-测试合格
								f_msgdisp=TRUE;//消息显示标志
							}
						}
					}
				}
			}
			
			//信号输出控制
			Da_Out(TestOut);//信号D/A输出
			
			//测试灯闪烁控制
			blinkT++;//闪烁时间计时
			blinkT%=9;
			if(blinkT<5)//灯闪烁时间
				Led_Test_On();//开测试灯
			else
				Led_Test_Off();//关测试灯
			Disp_TestMessage();
		}

		//读取A/D值
		Read_Ad();//读取AD值
		Ad_Filter();//AD值滤波
		Get_Result();//计算测试值
		if(Test_mid.set_item == I_SETUP ||(Test_mid.set_item == W_ISETUP && run_stemp == 1) 
		|| (Test_mid.set_item == W_ISETUP && run_stemp == 1)
		|| (Test_mid.set_item == I_WSETUP && run_stemp == 0))
		{
			//量程自动换挡处理
			if(Current>rangr_limit_high)//高于量程上限
			{
				f_upper=TRUE;//量程过压标志
				f_below=FALSE;//量程欠压标志
			}
			else if(Current<rangelomit_low)//低于量程下限
			{
				f_below=TRUE;//量程低压标志
				f_upper=FALSE;//量程欠压标志
			}
			else
			{
				f_upper=FALSE;//量程过压标志
				f_below=FALSE;//量程欠压标志
			}

			f_switch=FALSE;//量程切换标志
			if((Range<max)&&(f_below==TRUE))//量程非最高且低压
			{
				Range++;
				f_switch=TRUE;//量程切换标志
			}
			if((Range>0)&&(f_upper==TRUE))//量程非最低且过压
			{
				Range--;
				f_switch=TRUE;//量程切换标志
			}
		}else{
//			Range=0;
//			Range_Control(Range);//量程控制
		}
		if(f_switch==TRUE)//量程切换标志
		{
			AdCount=0;//AD值缓冲次数
			for(key=0;key<(AD_BUF_LENGTH);key++)
			{
				Ibuf[key]=0;//AD缓冲区清空
			}
			//Range=1;
			Range_Control(Range+ra_flag);//量程控制
			
			delay_ms(50);//硬件延时
		}
		else
		{
			//零值处理和计算电阻值
			switch(Test_mid.set_item)//参数项
			{
				case W_SETUP://耐压
				//case ITEM_DCW:
					//档位换算
					if(Range==1)
						Test_value.Test_I/=10;
					//最大值判别
					//dat=ACW_CURRENT_MAX;
					if(set_item==1)
						dat=DCW_CURRENT_MAX;
					else
						dat=ACW_CURRENT_MAX;
					if(Test_value.Test_I>dat)//最大值判别
						Test_value.Test_I=TEST_VALUE_OVER;//电阻溢出
					else
					{
//						if(Current>set_zero)//零值处理
//							Current-=set_zero;
//						else
//							Current=0;
					}
//					if(f_switch==FALSE)
//					if(sortT>=Test_mid.set_ramp)//判别延时
//						f_sort=TRUE;//分选标志
					break;
	
				case I_SETUP://绝缘
					//档位换算
					if(Current)//电流值非零
					{
						if(Resistance>IR_RESISTANCE_MAX)//最大值判别
							Resistance=TEST_VALUE_OVER;//电阻溢出
					}
					else
					{
						Resistance=TEST_VALUE_OVER;//电阻溢出
					}
					if(f_switch==FALSE)
					if(Test_value.Test_Time>=SORT_TIME_MIN)//超过最小时间后才开始分选
					f_sort=TRUE;//分选标志
					break;
		
				case I_WSETUP:
					if(run_stemp==0)
					{
						if(Current)//电流值非零
						{
							//最大值判别
							if(Resistance>IR_RESISTANCE_MAX)//最大值判别
								Resistance=TEST_VALUE_OVER;//电阻溢出
						}
						else
						{
							Resistance=TEST_VALUE_OVER;//电阻溢出
						}
						if(f_switch==FALSE)
						if(Test_value.Test_Time>=SORT_TIME_MIN)//超过最小时间后才开始分选
							f_sort=TRUE;//分选标志
						
					}
					else
					{
						if(Range==1)
						Test_value.Test_I/=10;
						//最大值判别
						dat=ACW_CURRENT_MAX;
						if(set_item==1)
							dat=DCW_CURRENT_MAX;
						else
							dat=ACW_CURRENT_MAX;
						if(Test_value.Test_I>dat)//最大值判别
							Test_value.Test_I=TEST_VALUE_OVER;//电阻溢出
						else
						{
	//						if(Current>set_zero)//零值处理
	//							Current-=set_zero;
	//						else
	//							Current=0;
						}
//						if(f_switch==FALSE)
//						if(sortT>=Test_mid.set_ramp)//判别延时
//						f_sort=TRUE;//分选标志
					}
					break;
				case W_ISETUP:
					if(run_stemp==0)
					{
						if(Range==1)
							Test_value.Test_I/=10;
						//最大值判别
						dat=ACW_CURRENT_MAX;
						if(set_item==1)
							dat=DCW_CURRENT_MAX;
						else
							dat=ACW_CURRENT_MAX;
						if(Test_value.Test_I>dat)//最大值判别
							Test_value.Test_I=TEST_VALUE_OVER;//电阻溢出
						else
						{
	//						if(Current>set_zero)//零值处理
	//							Current-=set_zero;
	//						else
	//							Current=0;
						}
//						if(f_switch==FALSE)
//						if(sortT>=Test_mid.set_ramp)//判别延时
//						f_sort=TRUE;//分选标志
					}
					else
					{
						if(Current)//电流值非零
						{

							//最大值判别
							if(Resistance>IR_RESISTANCE_MAX)//最大值判别
								Resistance=TEST_VALUE_OVER;//电阻溢出
						}
						else
						{
							Resistance=TEST_VALUE_OVER;//电阻溢出
						}
						if(f_switch==FALSE)
						if(Test_value.Test_Time>=SORT_TIME_MIN)//超过最小时间后才开始分选
							f_sort=TRUE;//分选标志
					
					}
					break;
				default:
					break;
			}
		}


 		//上下限判别
		if(GetSystemMessage()==MSG_TEST)
		//if((f_sort==TRUE) )//非换挡
		if((f_sort==TRUE) && (f_switch==FALSE))//非换挡
		{
			switch(Test_mid.set_item)//参数项
			{
				case W_SETUP:
//					if(Test_value.Test_Time>=2)
//					{
						dat=Test_value.Test_I;
						if(dat>Test_mid.set_high)//超上限
						{
							if(SaveData.Setup.Item == 0)//AC
							{
								if(dat>1200)//超上限
								{
									SetSystemMessage(MSG_OFL);
								}else{
									SetSystemMessage(MSG_HIGH);
								}
							}
							
							if(SaveData.Setup.Item == 1)//DC
							{
								if(dat>5000)//超上限
								{
									SetSystemMessage(MSG_OFL);
								}else{
									SetSystemMessage(MSG_HIGH);
								}
							}
							
							
							sendbuff2[2] = W_F_HI;
						}
						if(dat<Test_mid.set_low)//超下限
						{
							SetSystemMessage(MSG_LOW);
							sendbuff2[2] = W_F_LO;
						}
//					}
					break;
				
				case I_SETUP:
//					if(Test_value.Test_Time>=5)
//					{
						dat=Resistance;
						switch(Range)
						{
							case 0:
								dat/=1000;
								break;
							case 1:
								dat/=100;
								break;
							case 2:
								dat/=10;
								break;
							default:
								break;
						
						}
						if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//超上限
						{
							SetSystemMessage(MSG_HIGH);
							sendbuff2[2] = I_HIGH;
						}
						if(dat<Test_mid.set_low)//超下限
						{
							SetSystemMessage(MSG_LOW);
							sendbuff2[2] = I_LO;
						}
//					}
					break;
				case I_WSETUP:
					if(run_stemp==0)
					{
//						if(Test_value.Test_Time>=5)
//						{
							dat=Resistance;
							switch(Range)
							{
								case 0:
									dat/=1000;
									break;
								case 1:
									dat/=100;
									break;
								case 2:
									dat/=10;
									break;
								default:
									break;
							
							}
							if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//超上限
							{
								SetSystemMessage(MSG_HIGH);
								sendbuff2[2] = I_HIGH;
							}else{
								sendbuff2[2] = I_PASS;
							}
							if(dat<Test_mid.set_low)//超下限
							{
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = I_LO;
							}else{
								sendbuff2[2] = I_PASS;
							}
//						}
					
					}
					else
					{
//						if(Test_value.Test_Time>=2)
//						{
							dat=Test_value.Test_I;
							if(dat>Test_mid.set_high)//超上限
							{
								if(SaveData.Setup.Item == 0)//AC
								{
									if(dat>1200)//超上限
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								
								if(SaveData.Setup.Item == 1)//DC
								{
									if(dat>5000)//超上限
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								sendbuff3[2] = W_F_HI;
							}
							if(dat<Test_mid.set_low)//超下限
							{
								SetSystemMessage(MSG_LOW);
								sendbuff3[2] = W_F_LO;
							}
//						}
					}
					break;
				case W_ISETUP:
					if(run_stemp==0)
					{
//						if(Test_value.Test_Time>=2)
//						{
							dat=Test_value.Test_I;
							if(dat>Test_mid.set_high)//超上限
							{
								if(SaveData.Setup.Item == 0)//AC
								{
									if(dat>1200)//超上限
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								
								if(SaveData.Setup.Item == 1)//DC
								{
									if(dat>5000)//超上限
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								sendbuff2[2] = W_F_HI;
							}else{
								sendbuff2[2] = W_PASS;
							}
							if(dat<Test_mid.set_low)//超下限
							{
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = W_F_LO;
							}else{
								sendbuff2[2] = W_PASS;
							}
//						}
					}
					else
					{
//						if(Test_value.Test_Time>=5)
//						{
							dat=Resistance;
							switch(Range)
							{
								case 0:
									dat/=1000;
									break;
								case 1:
									dat/=100;
									break;
								case 2:
									dat/=10;
									break;
								default:
									break;
							
							}
							if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//超上限
							{
								SetSystemMessage(MSG_HIGH);
								sendbuff3[2] = I_HIGH;
							}
							if(dat<Test_mid.set_low)//超下限
							{
								SetSystemMessage(MSG_LOW);
								sendbuff3[2] = I_LO;
							}
//						}
					}
					break;
			
				default:
					break;
			}
		}
		
		//上下限报警和过流处理
		if((GetSystemMessage()==MSG_HIGH)||(GetSystemMessage()==MSG_LOW)||
				(GetSystemMessage()==MSG_ARC)||(GetSystemMessage()==MSG_OVER)
			||(GetSystemMessage()==MSG_OFL))
		{
			F_Fail=TRUE;//测试失败标志
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-测试暂停
			f_disp=TRUE;//更新显示测试结果
			f_msgdisp=TRUE;//消息显示标志
		}

		if(f_disp==TRUE)//显示更新
		{
//			memset(sendbuff,0,20);
			f_disp=FALSE;//显示更新
			LcdAddr.x=DATA_ADDR_X; LcdAddr.y=1;//DATA_ADDR_Y+HEIGHT_OF_STEP*TotalStep;
			
			switch(Test_mid.set_item)//按测试项目显示
			{
				case W_SETUP:
					if(SaveData.Setup.Output>Voltage)
					{
						if(SaveData.Setup.Output-Voltage<=2)
						{
							Voltage=SaveData.Setup.Output;
							f_sort=TRUE;//分选标志
						}
					
					}
					else
					{
						if(Voltage-SaveData.Setup.Output<=2)
						{
							Voltage=SaveData.Setup.Output;
							f_sort=TRUE;//分选标志
						}
					}
					Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
					Disp_StrAt(DispBuf);//显示测试值
					memset(sendbuff,0,20);
					sendflag = 1;
					memcpy(sendbuff,DispBuf,4);
					strcat(sendbuff,"kV;");
					
					sendbuff2[4] = (u8)(Voltage >> 8);
					sendbuff2[5] = (u8)(Voltage);
					
					
					LcdAddr.x=9;
					Hex_Format(Test_value.Test_I,2,4,FALSE);//数据格式化到DispBuf
					if(Test_value.Test_I < 1000)
					{
						DispBuf[0] = DispBuf[1];
						DispBuf[1] = DispBuf[2];
						DispBuf[2] = DispBuf[3];
						DispBuf[3] = DispBuf[4];
						DispBuf[4] = 0;
					}
					strcat(sendbuff,(char*)DispBuf);
					
					if(GetSystemMessage()!=MSG_OVER && GetSystemMessage()!=MSG_OFL/*Current!=TEST_VALUE_OVER*/)
					{
						Disp_StrAt(DispBuf);//显示测试值
						USENDI.sendI = atof(DispBuf)*100;
						if(Test_value.Test_I < 1000)
						{
							Disp_Str((u8*)" mA");
						}else{
							Disp_Str((u8*)"mA");
						}
						sendbuff2[6] = USENDI.s[0];
						sendbuff2[7] = USENDI.s[1];
						sendbuff2[8] = USENDI.s[2];
						sendbuff2[9] = USENDI.s[3];
						strcat(sendbuff,"mA;");
					}
					else
					{
						if(GetSystemMessage()==MSG_OFL)
						{
	//						memcpy(DispBuf,"-----",5);
							memcpy(DispBuf,"OFL ",5);
							//Disp_StrAt("-----");//显示测试值
							Disp_StrAt(DispBuf);
							Disp_Str((u8*)"  ");
						}else if(GetSystemMessage()==MSG_OVER){
							memcpy(DispBuf,"BRK ",5);
							//Disp_StrAt("-----");//显示测试值
							Disp_StrAt(DispBuf);
							Disp_Str((u8*)"  ");
						}
						sendbuff2[6] = 0;
						sendbuff2[7] = 0;
						sendbuff2[8] = 0;
						sendbuff2[9] = 0;
					}
					
					
					
					sendflag = 0;
					sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
					sendbuff2[11] = (u8)(Test_value.Test_Time);
					break;
				case I_WSETUP:
					if(run_stemp==0)
					{
						multstep = 1;
						if(SaveData.Setup.I_Volt>Voltage)
						{
							if(SaveData.Setup.I_Volt-Voltage<=2)
								Voltage=SaveData.Setup.I_Volt;
						
						}
						else
						{
							if(Voltage-SaveData.Setup.I_Volt<=2)
								Voltage=SaveData.Setup.I_Volt;
						}
						Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
						Disp_StrAt(DispBuf);//显示测试值
						memset(sendbuff1,0,20);
						sendflag = 1;
						memcpy(sendbuff1,DispBuf,4);
						strcat(sendbuff1,"kV;");
						sendbuff2[4] = (u8)(Voltage >> 8);
						sendbuff2[5] = (u8)(Voltage);
						
						LcdAddr.x=9;
						if(Resistance>9999)
						{
							if(Range==2)
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,TRUE);//数据格式化到DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,TRUE);//数据格式化到DispBuf
						}
						else
							Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//数据格式化到DispBuf
						if(Resistance!=TEST_VALUE_OVER)
						{
							Disp_StrAt(DispBuf);//显示测试值
							strcat(sendbuff1,(char*)DispBuf);
							USENDI.sendI = atof(DispBuf);					
							sendbuff2[6] = USENDI.s[0];
							sendbuff2[7] = USENDI.s[1];
							sendbuff2[8] = USENDI.s[2];
							sendbuff2[9] = USENDI.s[3];
						}
						else{
							Disp_StrAt(">9999");//显示测试值
							strcat(sendbuff1,">999");
							USENDI.sendI = 10000;
							sendbuff2[6] = USENDI.s[0];
							sendbuff2[7] = USENDI.s[1];
							sendbuff2[8] = USENDI.s[2];
							sendbuff2[9] = USENDI.s[3];
//							sendbuff2[6] = 0xff;
//							sendbuff2[7] = 0xff;
//							sendbuff2[8] = 0xff;
//							sendbuff2[9] = 0xff;
						}
						
//						USENDI.sendI = atof(DispBuf);					
//						sendbuff2[6] = USENDI.s[0];
//						sendbuff2[7] = USENDI.s[1];
//						sendbuff2[8] = USENDI.s[2];
//						sendbuff2[9] = USENDI.s[3];
//						strcat(sendbuff,(char*)DispBuf);Ω
						strcat(sendbuff1,(char*)"M;");
						sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
						sendbuff2[11] = (u8)(Test_value.Test_Time);
						sendflag = 0;
					}
					else
					{
						multstep = 2;
						
						if(SaveData.Setup.Output>Voltage)
						{
							if(SaveData.Setup.Output-Voltage<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//分选标志
							}
						
						}
						else
						{
							if(Voltage-SaveData.Setup.Output<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//分选标志
							}
						}
						Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
						Disp_StrAt(DispBuf);//显示测试值
//						memcpy(sendbuff,DispBuf,4);
//						strcat(sendbuff,"kV;");
						
						memset(sendbuff,0,20);
						sendflag = 1;
						memcpy(sendbuff,DispBuf,4);
						strcat(sendbuff,"kV;");
						
//						sendbuff2[4] = (u8)(Voltage >> 8);
//						sendbuff2[5] = (u8)(Voltage);
						
						sendbuff3[4] = (u8)(Voltage >> 8);
						sendbuff3[5] = (u8)(Voltage);
						
						LcdAddr.x=9;
						Hex_Format(Test_value.Test_I,2,4,TRUE);//数据格式化到DispBuf
						if(Test_value.Test_I < 1000)
						{
							DispBuf[0] = DispBuf[1];
							DispBuf[1] = DispBuf[2];
							DispBuf[2] = DispBuf[3];
							DispBuf[3] = DispBuf[4];
							DispBuf[4] = 0;
						}
						strcat(sendbuff,(char*)DispBuf);
						
						
						if(GetSystemMessage()!=MSG_OVER && GetSystemMessage()!=MSG_OFL/*Current!=TEST_VALUE_OVER*/)
						{
							Disp_StrAt(DispBuf);//显示测试值
							USENDI.sendI = atof(DispBuf)*100;
							if(Test_value.Test_I < 1000)
							{
								Disp_Str((u8*)" mA");
							}else{
								Disp_Str((u8*)"mA");
							}							
							sendbuff3[6] = USENDI.s[0];
							sendbuff3[7] = USENDI.s[1];
							sendbuff3[8] = USENDI.s[2];
							sendbuff3[9] = USENDI.s[3];
							strcat(sendbuff,"mA;");
							sendflag = 0;
						}
						else
						{
							if(GetSystemMessage()==MSG_OFL)
							{
		//						memcpy(DispBuf,"-----",5);
								memcpy(DispBuf,"OFL ",5);
								//Disp_StrAt("-----");//显示测试值
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
								strcat(sendbuff,"mA;");
								sendflag = 0;
							}else if(GetSystemMessage()==MSG_OVER){
								memcpy(DispBuf,"BRK ",5);
								//Disp_StrAt("-----");//显示测试值
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
								strcat(sendbuff,"mA;");
								sendflag = 0;
							}				
							sendbuff3[6] = 0;
							sendbuff3[7] = 0;
							sendbuff3[8] = 0;
							sendbuff3[9] = 0;
						}
					
						
//						if(Current!=TEST_VALUE_OVER)
//						{
//							Disp_StrAt(DispBuf);//显示测试值
//							strcat(sendbuff1,(char*)DispBuf);
//							USENDI.sendI = atof(DispBuf);					
//							sendbuff3[6] = USENDI.s[0];
//							sendbuff3[7] = USENDI.s[1];
//							sendbuff3[8] = USENDI.s[2];
//							sendbuff3[9] = USENDI.s[3];
//						}
//						else
//						{
//							Disp_StrAt("-----");//显示测试值
//							strcat(sendbuff1,"-----");
//							sendbuff3[6] = 0xff;
//							sendbuff3[7] = 0xff;
//							sendbuff3[8] = 0xff;
//							sendbuff3[9] = 0xff;
//						}
						USENDI.sendI = atof(DispBuf);					
//						sendbuff2[6] = USENDI.s[0];
//						sendbuff2[7] = USENDI.s[1];
//						sendbuff2[8] = USENDI.s[2];
//						sendbuff2[9] = USENDI.s[3];
						
//						sendbuff3[6] = USENDI.s[0];
//						sendbuff3[7] = USENDI.s[1];
//						sendbuff3[8] = USENDI.s[2];
//						sendbuff3[9] = USENDI.s[3];
//						strcat(sendbuff,(char*)DispBuf);
//						strcat(sendbuff,"mA;");
						
//						strcat(sendbuff1,(char*)DispBuf);
//						strcat(sendbuff1,"mA;");
						sendbuff3[10] = (u8)(Test_value.Test_Time >> 8);
						sendbuff3[11] = (u8)(Test_value.Test_Time);
					}
					break;

				case I_SETUP:
					if(SaveData.Setup.I_Volt>Voltage)
					{
						if(SaveData.Setup.I_Volt-Voltage<=2)
							Voltage=SaveData.Setup.I_Volt;
					
					}
					else
					{
						if(Voltage-SaveData.Setup.I_Volt<=2)
							Voltage=SaveData.Setup.I_Volt;
					}
					Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
					Disp_StrAt(DispBuf);//显示测试值
					memset(sendbuff,0,20);
					sendflag = 1;
					memcpy(sendbuff,DispBuf,4);
					strcat(sendbuff,"kV;");
					sendbuff2[4] = (u8)(Voltage >> 8);
					sendbuff2[5] = (u8)(Voltage);
					
					LcdAddr.x=9;
					if(Resistance>9999)
					{
						if(Range==2)
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,FALSE);//数据格式化到DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,FALSE);//数据格式化到DispBuf
						}
					else
						Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//数据格式化到DispBuf
					if(Resistance!=TEST_VALUE_OVER)
					{
						Disp_StrAt(DispBuf);//显示测试值
						strcat(sendbuff,(char*)DispBuf);
						USENDI.sendI = atof(DispBuf);					
						sendbuff2[6] = USENDI.s[0];
						sendbuff2[7] = USENDI.s[1];
						sendbuff2[8] = USENDI.s[2];
						sendbuff2[9] = USENDI.s[3];
					}
					else{
						Disp_StrAt(">9999");//显示测试值
						strcat(sendbuff,">9999");
						USENDI.sendI = 10000;
						sendbuff2[6] = USENDI.s[0];
						sendbuff2[7] = USENDI.s[1];
						sendbuff2[8] = USENDI.s[2];
						sendbuff2[9] = USENDI.s[3];
//						sendbuff2[6] = 0xff;
//						sendbuff2[7] = 0xff;
//						sendbuff2[8] = 0xff;
//						sendbuff2[9] = 0xff;
					}
//					USENDI.sendI = atof(DispBuf);					
//					sendbuff2[6] = USENDI.s[0];
//					sendbuff2[7] = USENDI.s[1];
//					sendbuff2[8] = USENDI.s[2];
//					sendbuff2[9] = USENDI.s[3];Ω
					strcat(sendbuff,(char*)"M;");
					
					sendflag = 0;
					sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
					sendbuff2[11] = (u8)(Test_value.Test_Time);
					break;

				case W_ISETUP:
					if(run_stemp==0)
					{
						multstep = 1;
						if(SaveData.Setup.Output>Voltage)
						{
							if(SaveData.Setup.Output-Voltage<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//分选标志
							}
						
						}
						else
						{
							if(Voltage-SaveData.Setup.Output<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//分选标志
							}
						}
						Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
						Disp_StrAt(DispBuf);//显示测试值
						memset(sendbuff,0,20);
						sendflag = 1;
						memcpy(sendbuff,DispBuf,4);
						strcat(sendbuff,"kV;");
						sendbuff2[4] = (u8)(Voltage >> 8);
						sendbuff2[5] = (u8)(Voltage);
						
						LcdAddr.x=9;
						Hex_Format(Test_value.Test_I,2,4,TRUE);//数据格式化到DispBuf
						if(Test_value.Test_I < 1000)
						{
							DispBuf[0] = DispBuf[1];
							DispBuf[1] = DispBuf[2];
							DispBuf[2] = DispBuf[3];
							DispBuf[3] = DispBuf[4];
							DispBuf[4] = 0;
						}
//						if(Current!=TEST_VALUE_OVER)
//						{
//							Disp_StrAt(DispBuf);//显示测试值
//							strcat(sendbuff,(char*)DispBuf);
//							USENDI.sendI = atof(DispBuf);					
//							sendbuff2[6] = USENDI.s[0];
//							sendbuff2[7] = USENDI.s[1];
//							sendbuff2[8] = USENDI.s[2];
//							sendbuff2[9] = USENDI.s[3];
//						}
//						else
//						{
//							Disp_StrAt("-----");
//							memcpy(sendbuff,"-----",5);
//							sendbuff2[6] = 0xff;
//							sendbuff2[7] = 0xff;
//							sendbuff2[8] = 0xff;
//							sendbuff2[9] = 0xff;
//							//Disp_StrAt("-----");//显示测试值
//							
//						}
////						USENDI.sendI = atof(DispBuf);					
////						sendbuff2[6] = USENDI.s[0];
////						sendbuff2[7] = USENDI.s[1];
////						sendbuff2[8] = USENDI.s[2];
////						sendbuff2[9] = USENDI.s[3];
////						strcat(sendbuff,(char*)DispBuf);
//						strcat(sendbuff,"mA;");
						strcat(sendbuff,(char*)DispBuf);
						strcat(sendbuff,"mA;");
						sendflag = 0;
						if(GetSystemMessage()!=MSG_OVER && GetSystemMessage()!=MSG_OFL/*Current!=TEST_VALUE_OVER*/)
						{
							Disp_StrAt(DispBuf);//显示测试值
							USENDI.sendI = atof(DispBuf)*100;
							if(Test_value.Test_I < 1000)
							{
								Disp_Str((u8*)" mA");
							}else{
								Disp_Str((u8*)"mA");
							}
							sendbuff2[6] = USENDI.s[0];
							sendbuff2[7] = USENDI.s[1];
							sendbuff2[8] = USENDI.s[2];
							sendbuff2[9] = USENDI.s[3];
							
						}
						else
						{
							if(GetSystemMessage()==MSG_OFL)
							{
		//						memcpy(DispBuf,"-----",5);
								memcpy(DispBuf,"OFL ",5);
								//Disp_StrAt("-----");//显示测试值
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
							}else if(GetSystemMessage()==MSG_OVER){
								memcpy(DispBuf,"BRK ",5);
								//Disp_StrAt("-----");//显示测试值
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
							}	
							sendbuff2[6] = 0;
							sendbuff2[7] = 0;
							sendbuff2[8] = 0;
							sendbuff2[9] = 0;
						}
						
						sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
						sendbuff2[11] = (u8)(Test_value.Test_Time);
					}
					else
					{
						multstep = 2;
//						strcat(sendbuff,(char*)"PASS");
						if(SaveData.Setup.I_Volt>Voltage)
						{
							if(SaveData.Setup.I_Volt-Voltage<=2)
								Voltage=SaveData.Setup.I_Volt;
						
						}
						else
						{
							if(Voltage-SaveData.Setup.I_Volt<=2)
								Voltage=SaveData.Setup.I_Volt;
						}
						Hex_Format(Voltage,2,3,TRUE);//数据格式化到DispBuf
						Disp_StrAt(DispBuf);//显示测试值
//						memcpy(sendbuff,DispBuf,4);
//						strcat(sendbuff,"kV;");
						memset(sendbuff1,0,20);
						sendflag = 1;
						memcpy(sendbuff1,DispBuf,4);
						strcat(sendbuff1,"kV;");
						
//						sendbuff2[4] = (u8)(Voltage >> 8);
//						sendbuff2[5] = (u8)(Voltage);
						
						sendbuff3[4] = (u8)(Voltage >> 8);
						sendbuff3[5] = (u8)(Voltage);
						
						LcdAddr.x=9;
						if(Resistance>9999)
						{
							if(Range==2)
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,FALSE);//数据格式化到DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,FALSE);//数据格式化到DispBuf
							
						}
						else
							Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//数据格式化到DispBuf
						if(Resistance!=TEST_VALUE_OVER)
						{
							Disp_StrAt(DispBuf);//显示测试值
							strcat(sendbuff1,(char*)DispBuf);
							USENDI.sendI = atof(DispBuf);
							sendbuff3[6] = USENDI.s[0];
							sendbuff3[7] = USENDI.s[1];
							sendbuff3[8] = USENDI.s[2];
							sendbuff3[9] = USENDI.s[3];
						}
						else{
							Disp_StrAt(">9999");//显示测试值
//							Disp_StrAt("-----");//显示测试值
							strcat(sendbuff1,">9999");
							USENDI.sendI = 10000;
							sendbuff3[6] = USENDI.s[0];
							sendbuff3[7] = USENDI.s[1];
							sendbuff3[8] = USENDI.s[2];
							sendbuff3[9] = USENDI.s[3];
//							sendbuff3[6] = 0xff;
//							sendbuff3[7] = 0xff;
//							sendbuff3[8] = 0xff;
//							sendbuff3[9] = 0xff;
						}
						
//						USENDI.sendI = atof(DispBuf);					
//						sendbuff2[6] = USENDI.s[0];
//						sendbuff2[7] = USENDI.s[1];
//						sendbuff2[8] = USENDI.s[2];
//						sendbuff2[9] = USENDI.s[3];
						
//						sendbuff3[6] = USENDI.s[0];
//						sendbuff3[7] = USENDI.s[1];
//						sendbuff3[8] = USENDI.s[2];
//						sendbuff3[9] = USENDI.s[3];
//						strcat(sendbuff,(char*)DispBuf);
//						strcat(sendbuff,(char*)"MΩ;");
						
//						strcat(sendbuff1,(char*)DispBuf);Ω
						strcat(sendbuff1,(char*)"M;");
						sendbuff3[10] = (u8)(Test_value.Test_Time >> 8);
						sendbuff3[11] = (u8)(Test_value.Test_Time);
						sendflag = 0;
					}

					break;
				
				default:
					break;
			}
			//strcat(sendbuff,(char*)MsgTab[GetSystemMessage()]);
			
			//显示时间
			LcdAddr.x=10;LcdAddr.y=0;
			Hex_Format(Test_value.Test_Time,1,4,FALSE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);//显示测试值
//			sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
//			sendbuff2[11] = (u8)(Test_value.Test_Time);
			//显示信息
			if(f_msgdisp==TRUE)//消息显示标志
			{
//				f_msgdisp=FALSE;//消息显示标志
//				LcdAddr.x=MSG_ADDR_X;
//				Disp_SysMessage();//显示信息
			}
		}
		
//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//串口处理
//		}

		key=Key_Read();//读取按键
		switch(key)
		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				break;
	
			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
				break;
	
			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
				break;
	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
				break;

			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				break;

			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
//				break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				break;

			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				SetSystemMessage(MSG_PAUSE);//系统信息-暂停测试
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-暂停测试
				//break;
			Plc_Start_Off();
			return;
			
			default:
				break;
		}
	}
	run_stemp++;//走一步
	if(run_stemp == 1 && respond == 1)
	{
		if(Test_mid.set_item == W_ISETUP || Test_mid.set_item == I_WSETUP)
		{
			SendRes1();
		}
	}
	
	Plc_Start_Off();
}

//==========================================================
//函数名称：TestPause_Process
//函数功能：测试暂停处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.25 
//修改日期：2015.09.06 13:28
//备注说明：无
//==========================================================
void TestPause_Process(void)
{
//	u8 i;
	u8 key;
	u8 item;
	u16 time;//连接延时时间
	bool f_disp;//显示标志

	f_disp=FALSE;//显示标志
	item=SaveData.Setup.Group_Item;//当前参数

	//输出关闭控制
	Output_Off();//输出关闭
	
	if(GetSystemMessage()!=MSG_PAUSE)
	{
		switch(item)//项目
		{
			case I_SETUP://绝缘电阻测试
			case W_SETUP://耐压测试
				SetSystemStatus(SYS_STATUS_TEST_FINISH);//系统状态-测试结束
				break;
			case I_WSETUP://绝缘耐压测试
			case W_ISETUP://耐压绝缘测试
				if(run_stemp==1)
				{
					if(GetSystemMessage()==MSG_PASS)
						SetSystemStatus(SYS_STATUS_TEST);
					else
						SetSystemStatus(SYS_STATUS_TEST_FINISH);//系统状态-测试结束
					
				}
				else
					SetSystemStatus(SYS_STATUS_TEST_FINISH);//系统状态-测试结束
				break;
			case ITEM_NONE://无测试项目
				break;

			default:
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-暂停测试
				return;
				
		}	
	}else{
		switch(item)//项目
		{
			case I_SETUP://绝缘电阻测试
				
			break;
			case W_SETUP://耐压测试
				
			break;
			case I_WSETUP://绝缘耐压测试
				
			break;
			case W_ISETUP://耐压绝缘测试
				if(run_stemp==1)
				{
					if(GetSystemMessage()==MSG_PASS)
						SetSystemStatus(SYS_STATUS_TEST);
					else
						SetSystemStatus(SYS_STATUS_TEST_FINISH);//系统状态-测试结束
					
				}
				else
					SetSystemStatus(SYS_STATUS_TEST_FINISH);//系统状态-测试结束
				break;
			case ITEM_NONE://无测试项目
				break;

			default:
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-暂停测试
				return;
				
		}
		if(respond == 1)
		{
			SendRes();
			respond = 0;
		}
	}		
		
 
	//显示测试信息
	LcdAddr.x=MSG_ADDR_X; LcdAddr.y=0;
	Disp_SysMessage();//显示信息

 	//讯响控制
//	if(SaveData.System.Beep)
//	{
		Beep_One();//响一声
//	}

	//按步骤保存测试数据

	
	//连接延时和连接下一个步骤控制
	if(GetSystemMessage()==MSG_PAUSE)//暂停测试
	{
		//显示界面
		LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//		Disp_Str("测试暂停",0);//显示
		time=TEST_VALUE_OVER;//连接时间初始化
	}
	else
	{
		TotalStep++;//测试步骤计数
		if(StepIndex>=(STEP_MAX-1))//已是最大步骤
		{
			SetSystemStatus(SYS_STATUS_TEST_FINISH);//测试结束
			return;
		}

	}

	while(GetSystemStatus()==SYS_STATUS_TEST_PAUSE)
	{
		//显示连接时间，倒计时
		if(f_disp)//显示标志
		{
			f_disp=FALSE;//显示标志
			LcdAddr.x=TITLE_ADDR_X+6; LcdAddr.y=TITLE_ADDR_Y+2;
			Hex_Format(time,1,4,TRUE);//数值格式化，4位数值
			Disp_Str(DispBuf);//显示测试值
			Disp_Char('s');//显示s
		}

		if( GetSoftTimerOut(DISP_SOFTTIMER) && (GetSystemMessage()!=MSG_PAUSE) )//非暂停测试，等待延时结束
		{
			if(time!=TEST_VALUE_OVER)//无效的连接时间
			{
				f_disp=TRUE;//显示标志
				SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//设置延时时间，1000/10=100mS
				time--;
			}
		}

		if(time<1)//连接延时结束判别
		{
			SetSystemStatus(SYS_STATUS_TEST);//系统状态-测试开始，连接下一个步骤
		}

//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//串口处理
//		}
		
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/20);//等待按键(100*10ms/20=50ms)
		switch(key)
		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				break;
//	
//			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
//				break;
//	
//			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
//				break;
	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
				break;

			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				break;
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				if(GetSystemMessage()!=MSG_PAUSE)//暂停测试
				{
					if(time==TEST_VALUE_OVER)//无效的连接时间
					{
						SetSystemStatus(SYS_STATUS_IDLE);//系统状态-待机
					}
					else
					{
						SetSystemMessage(MSG_PAUSE);//系统信息-暂停测试
//						LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//						Disp_Str("暂停",0);//显示界面
					}
				}
				else
				{
					SetSystemStatus(SYS_STATUS_IDLE);//系统状态-待机
				}
			break;
			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_TEST);//测试开始
				break;
	
//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				break;
	
			
			
			default:
				break;
		}
	}

	//清空连接时间显示区
//	LcdAddr.x=TITLE_ADDR_X+6; LcdAddr.y=TITLE_ADDR_Y+2;
//	Disp_Str("      ",0);//显示
}

//==========================================================
//函数名称：TestFinish_Process
//函数功能：测试结束处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.26
//修改日期：2015.08.22 16:04
//备注说明：无
//注意事项：无
//==========================================================
void TestFinish_Process(void)
{
	u8 key;
	bool f_disp;//显示标志

	f_disp=TRUE;//显示标志

	Led_HV_Off();//关闭高压灯
	if(SaveData.Setup.Group_Item == W_ISETUP || SaveData.Setup.Group_Item == I_WSETUP)
	{
		if(respond == 1 && run_stemp == 2)
		{
			SendRes();
			respond = 0;
		}
	}else{
		if(respond == 1)
		{
			SendRes();
			respond = 0;
		}
	}
//	Amp_Output_Off();//功放输出关闭
	while(GetSystemStatus()==SYS_STATUS_TEST_FINISH)
	{
		if(f_disp==TRUE)//显示标志
		{
			f_disp=FALSE;//显示标志

			//显示测试界面
//			LcdAddr.x=TITLE_ADDR_X; LcdAddr.y=TITLE_ADDR_Y;
//			Disp_Str("测试完成",0);//显示

			//显示分选结果和讯响控制
			LcdAddr.x=TITLE_ADDR_X+14;LcdAddr.y=TITLE_ADDR_Y;
			if(F_Fail)//测试失败标志
			{
//				Disp_Str("分选失败",1);//显示
				Beep_On();//开蜂鸣器
				Led_Pass_Off();//关合格灯
				Led_Fail_On();//开报警灯
		//		if(SaveData.Setup.Beep==BEEP_FAIL)
		//			Beep_On();//开蜂鸣器
		//		else
		//			Beep_Off();//关蜂鸣器
				
				//gtickon=10;
				//Beep_One();
			}
			else
			{
				Beep_Two();//蜂鸣器响两声
//				Disp_Str("分选合格",1);//显示
				if(GetSystemMessage()==MSG_PASS)
				{
					Led_Fail_Off();//关报警灯
					Led_Pass_On();//开合格灯
				}
		//		if(SaveData.Setup.Beep==BEEP_PASS)
		//			Beep_On();//开蜂鸣器
		//		else
		//			Beep_Off();//关蜂鸣器
				
			}
			
		}

//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//串口处理
//		}
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/50);//等待按键(100*10ms/50=20ms)
		switch(key)
		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				SetSystemStatus(SYS_STATUS_SETUP);//设置状态
//				break;
//	
//			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
//				break;
//	
//			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
//				break;
	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
				break;

			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				break;

			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_START);//启动测试
				break;
	
			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				SetSystemStatus(SYS_STATUS_IDLE);//待机
				Beep_Off();
				break;
			
			default:
				break;
		}
	}
	F_Fail=0;
	//gtickon=0;
}

//==========================================================
//函数名称：Reset_Process
//函数功能：系统复位处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.25 
//修改日期：2015.01.25 10:29
//备注说明：无
//==========================================================
void Reset_Process(void)
{
	while(SystemStatus==SYS_STATUS_RESET)
	{
		Hardware_Init();//硬件初始化
		ReadCalData();//读取保存数据
		SetSystemStatus(SYS_STATUS_IDLE);//待测状态
	}
}

//==========================================================
//函数名称：Error_Process
//函数功能：系统错误处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.25 
//修改日期：2015.01.25 10:27
//备注说明：无
//==========================================================
void Error_Process(void)
{
	u8 i;

	while(GetSystemStatus()==SYS_STATUS_ERROR)
	{
		LcdAddr.x=10; LcdAddr.y=2;
//		Disp_Str("-Error-",0);//显示错误
//		Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
		LcdAddr.x=4;LcdAddr.y=50;
//		Disp_Str("System Will Reboot!",0);//显示重启
	
		for(i=0;i<10;i++)
		{
			Beep_Two();//响两声
			delay_ms(3);//延时300ms
		}
		SetSystemStatus(SYS_STATUS_RESET);//系统复位
		ResetSys();//软件复位
	}
}

//协议2测试通过、测试中止或测试失败返回12字节数据
void SendRes(void)
{
	u8 i;
	sendbuff2[0] = UART_SEND_BEGIN20;
	sendbuff2[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	sendbuff3[0] = UART_SEND_BEGIN20;
	sendbuff3[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	
	U2.BIT_FLAG.ACWF = SaveData.Setup.Freq;//w_ma:d4
	U2.BIT_FLAG.ARC = SaveData.Setup.Arc;//w_ma:d3d2d1d0,电弧
	sendbuff2[3] = U2.w_ma;
	sendbuff3[3] = U2.w_ma;
	
	if(!F_Fail)
	{
		if(Test_mid.set_item == W_SETUP/* || Test_mid.set_item == I_WSETUP*/)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_PAUSE://耐压测试终止
				{
					sendbuff2[2] = W_STOP;
				}break;
			}
		}else if(Test_mid.set_item == I_SETUP/* || Test_mid.set_item == W_ISETUP*/){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					sendbuff2[2] = I_STOP;
				}break;
			}		
		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = I_PASS;
					sendbuff3[2] = W_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					if(run_stemp == 1)
					{
						sendbuff2[2] = I_STOP;
					}else if(run_stemp == 2){
						sendbuff3[2] = W_STOP;
					}						
				}break;
			}
			
		}else if(Test_mid.set_item == W_ISETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
					sendbuff3[2] = I_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					if(run_stemp == 1)
					{
						sendbuff2[2] = W_STOP;
					}else if(run_stemp == 2){
						sendbuff3[2] = I_STOP;
					}			
				}break;
			}
			
		}
	}
	if(F_Fail)
	{
		if(Test_mid.set_item == W_SETUP)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_HIGH://耐压漏电过大
				{
					sendbuff2[2] = W_F_HI;
				}break;
				case MSG_LOW://耐压漏电过小
				{
					sendbuff2[2] = W_F_LO;
				}break;
				case MSG_PAUSE://耐压测试终止
				{
					sendbuff2[2] = W_STOP;
				}break;
				case MSG_ARC://耐压电弧失败
				{
					sendbuff2[2] = W_ARC;
				}break;
				case MSG_OVER://耐压测试崩溃
				{
					sendbuff2[2] = W_OVER;
				}break;
			}

		}else if(Test_mid.set_item == I_SETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://绝缘测试通过
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_HIGH://绝缘电阻过大
				{
					sendbuff2[2] = I_HIGH;
				}break;
				case MSG_LOW://绝缘电阻过小
				{
					sendbuff2[2] = I_LO;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					sendbuff2[2] = I_STOP;
				}break;
			}
		}
	}
//	for(i=0;i<12;i++)
//	{
//		USART_SendData(USART1, sendbuff2[i]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	}
	
	if(Test_mid.set_item == I_WSETUP || Test_mid.set_item == W_ISETUP)
	{
		for(i=0;i<12;i++)
		{
			USART_SendData(USART1, sendbuff3[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		}
	}else{
		for(i=0;i<12;i++)
		{
			USART_SendData(USART1, sendbuff2[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		}
	}
}

void SendRes1(void)
{
	u8 i;
	sendbuff2[0] = UART_SEND_BEGIN20;
	sendbuff2[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	sendbuff3[0] = UART_SEND_BEGIN20;
	sendbuff3[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	
	U2.BIT_FLAG.ACWF = SaveData.Setup.Freq;//w_ma:d4
	U2.BIT_FLAG.ARC = SaveData.Setup.Arc;//w_ma:d3d2d1d0,电弧
	sendbuff2[3] = U2.w_ma;
	sendbuff3[3] = U2.w_ma;
	
	if(!F_Fail)
	{
		if(Test_mid.set_item == W_SETUP/* || Test_mid.set_item == I_WSETUP*/)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_PAUSE://耐压测试终止
				{
					sendbuff2[2] = W_STOP;
				}break;
			}
		}else if(Test_mid.set_item == I_SETUP/* || Test_mid.set_item == W_ISETUP*/){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					sendbuff2[2] = I_STOP;
				}break;
			}		
		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = I_PASS;
					sendbuff3[2] = W_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					if(run_stemp == 1)
					{
						sendbuff2[2] = I_STOP;
					}else if(run_stemp == 2){
						sendbuff3[2] = W_STOP;
					}						
				}break;
			}
			
		}else if(Test_mid.set_item == W_ISETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
					sendbuff3[2] = I_PASS;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					if(run_stemp == 1)
					{
						sendbuff2[2] = W_STOP;
					}else if(run_stemp == 2){
						sendbuff3[2] = I_STOP;
					}			
				}break;
			}
			
		}
	}
	if(F_Fail)
	{
		if(Test_mid.set_item == W_ISETUP)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://耐压测试通过
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_HIGH://耐压漏电过大
				{
					sendbuff2[2] = W_F_HI;
				}break;
				case MSG_LOW://耐压漏电过小
				{
					sendbuff2[2] = W_F_LO;
				}break;
				case MSG_PAUSE://耐压测试终止
				{
					sendbuff2[2] = W_STOP;
				}break;
				case MSG_ARC://耐压电弧失败
				{
					sendbuff2[2] = W_ARC;
				}break;
				case MSG_OVER://耐压测试崩溃
				{
					sendbuff2[2] = W_OVER;
				}break;
			}

		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://绝缘测试通过
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_HIGH://绝缘电阻过大
				{
					sendbuff2[2] = I_HIGH;
				}break;
				case MSG_LOW://绝缘电阻过小
				{
					sendbuff2[2] = I_LO;
				}break;
				case MSG_PAUSE://绝缘测试终止
				{
					sendbuff2[2] = I_STOP;
				}break;
			}
		}
	}
	for(i=0;i<12;i++)
	{
		USART_SendData(USART1, sendbuff2[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
	
//	if(Test_mid.set_item == I_WSETUP || Test_mid.set_item == W_ISETUP)
//	{
//		for(i=0;i<12;i++)
//		{
//			USART_SendData(USART1, sendbuff3[i]);
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//		}
//	}
}
//==========================================================
//函数名称：Uart_Process
//函数功能：串口处理
//入口参数：无
//出口参数：无
//创建日期：2015.02.02 
//修改日期：2015.02.10 10:15
//备注说明：无
//==========================================================
void Uart_Process(void)
{
//	u8 strbuff[8];
	u8 sec_king,i;
#if HW_UART_SUPPORT
	u8 kind=0xff;
	u8 lenth = 0;
	u8 recbuf[30];
#if DEBUG_SUPPORT
	 u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//收发数据缓冲
#else
	 u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//收发数据缓冲
#endif
if(FacBuf.rec.end)//通讯协议选择
{
	SaveData.pselect = FacBuf.rec.buf[2];
//	SaveData.devaddr = FacBuf.rec.buf[3];
	memset(FacBuf.rec.buf,'\0',30);//清空缓冲
	FacBuf.rec.end=FALSE;//接收缓冲可读标志复位
	FacBuf.rec.ptr=0;//接收指针清零
	
	SavePselect();
//	Saveaddr();
}
if(SaveData.pselect == 0)//通讯协议1
{
	//	if(SaveData.System.Uart)//串口有效
	//	{
			if (ComBuf.rec.end)//接收数据结束
			{
				memset(str,'\0',(FRAME_LEN_MAX-FRAME_LEN_MIN+1));//清空缓冲
				{
					memcpy(str,&ComBuf.rec.buf[PDATASTART],(FRAME_LEN_MAX-FRAME_LEN_MIN)+1);//ComBuf.send.len-FRAME_LEN_MIN);//数据包
					kind=ComBuf.rec.buf[PFRAMEKIND];//命令字
					sec_king=ComBuf.rec.buf[PDATASTART];
				}
				//准备接收下一帧数据
				ComBuf.rec.end=FALSE;//接收缓冲可读标志复位
				ComBuf.rec.ptr=0;//接收指针清零
	//		}
	//	}

		switch(kind)
		{
			case FRAME_READ_RESULT://读取结果
				//串口发送测试数据:电压(5)+电阻(6)+时间(4)+分选(1)=16字节
				switch (GetSystemMessage())//系统信息
				{
					case MSG_IDLE:
						memcpy(strbuff,"----",5);
						break;
					case MSG_PAUSE:
						memcpy(strbuff,"----",5);
						//kind=0x9B;//测试中止
						break;
					case MSG_PASS:
						//kind=0x91;//测试通过
						memcpy(strbuff,"PASS",5);
						break;
					case MSG_HIGH:
						//kind=0x92;//上限报警
						memcpy(strbuff,"HIGH",5);
						break;
					case MSG_LOW:
						//kind=0x92;//下限报警
						memcpy(strbuff,"LOW ",5);
						break;
					case MSG_OVER:
						memcpy(strbuff,"BRK ",5);
						break;
					case MSG_ARC:
						memcpy(strbuff,"ARC ",5);
						break;
					case MSG_OFL://过流报警
						memcpy(strbuff,"HIGH",5);
						break;
					default:
						//kind=0x90;//正常测试
						memcpy(strbuff,"TEST",5);
						break;
				}	
				
				

				if(SaveData.Setup.Group_Item == W_ISETUP || SaveData.Setup.Group_Item == I_WSETUP)
				{
					if(sendflag == 0)
					{
						sendflag = 1;
						memset(ComBuf.send.buf,0,40);
		//				ComBuf.send.buf[0]=0xAA;
		//				ComBuf.send.begin=FALSE;
						if(GetSystemMessage() == MSG_IDLE)
						{
							strcat((char*)ComBuf.send.buf,(char*)sendbuff);
	//						memcpy(&ComBuf.send.buf[0],sendbuff,14);
							strcat((char*)ComBuf.send.buf,(char*)strbuff);
						}else{
							if(multstep == 1)
							{
								strcat((char*)ComBuf.send.buf,(char*)sendbuff);
	//							memcpy(&ComBuf.send.buf[0],sendbuff,14);
								if(SaveData.Setup.Group_Item == W_ISETUP)
								{
									strcat((char*)ComBuf.send.buf,(char*)strbuff);
								}else if(SaveData.Setup.Group_Item == I_WSETUP){
									strcat((char*)ComBuf.send.buf,"----");
								}
							}else{
								if(SaveData.Setup.Group_Item == W_ISETUP)
								{
									if(sendbuff[13] == 0x3b)
									{
										memcpy(&sendbuff[14],"PASS",4);
									}else if(sendbuff[14] == 0x3b){
										memcpy(&sendbuff[15],"PASS",4);
									}
//									strcat((char*)sendbuff,"PASS");
									memcpy(&ComBuf.send.buf[0],sendbuff,18);
								}else if(SaveData.Setup.Group_Item == I_WSETUP){
//									strcat((char*)sendbuff,"mA;");
									if(sendbuff[13] == 0x3b)
									{
										memcpy(&sendbuff[14],strbuff,4);
									}else if(sendbuff[14] == 0x3b){
										memcpy(&sendbuff[15],strbuff,4);
									}
//									strcat((char*)sendbuff,(char*)strbuff);
									strcat((char*)ComBuf.send.buf,(char*)sendbuff);
//									memcpy(&ComBuf.send.buf[0],sendbuff,18);
								}							
							}
						}
	//					memset(ComBuf1.send.buf,0,21);
	//					ComBuf1.send.buf[0]=0xAA;
	//					ComBuf1.send.begin=FALSE;
	//					memcpy(&ComBuf1.send.buf[1],sendbuff1,16);
						
						strcat((char*)ComBuf.send.buf,";");
						strcat((char*)ComBuf.send.buf,(char*)sendbuff1);
						if(multstep == 1)
						{
	//						strcat((char*)ComBuf.send.buf,"----");
							if(SaveData.Setup.Group_Item == W_ISETUP)
							{
								strcat((char*)ComBuf.send.buf,"----");
							}else if(SaveData.Setup.Group_Item == I_WSETUP){
								strcat((char*)ComBuf.send.buf,(char*)strbuff);
							}
						}else{
							if(SaveData.Setup.Group_Item == W_ISETUP)
							{
								strcat((char*)ComBuf.send.buf,(char*)strbuff);
							}else if(SaveData.Setup.Group_Item == I_WSETUP){
								strcat((char*)ComBuf.send.buf,"PASS");
							}
							
						}
						strcat((char*)ComBuf.send.buf,(char*)sendend);//尾部增加回车和换行符
						for(i=0;i<39;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
						ComBuf.rec.end=FALSE;//接收缓冲可读标志复位
	//					USART_SendData(USART1, 0xBB);
	//					while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	//					break;
					}else{
						for(i=0;i<39;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
						ComBuf.rec.end=FALSE;//接收缓冲可读标志复位
					}
				}else{
					if(sendflag == 0)
					{
						sendflag = 1;
						memset(ComBuf.send.buf,0,40);
		//				ComBuf.send.buf[0]=0xAA;
		//				ComBuf.send.begin=FALSE;
						memcpy(&ComBuf.send.buf[0],sendbuff,14);
						strcat((char*)ComBuf.send.buf,(char*)strbuff);
						
						strcat((char*)ComBuf.send.buf,(char*)sendend);//尾部增加回车和换行符
						
						for(i=0;i<20;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
					}else{
						for(i=0;i<20;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
					}
				}
				

				
				
				
				break;
			
			case FRAME_START://启动
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_START);//系统状态-启动测试
				break;

			case FRAME_RESET://复位
				if(GetSystemStatus() == SYS_STATUS_TEST){
					SetSystemMessage(MSG_PAUSE);//系统信息-暂停测试
					SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-待机
					Plc_Start_Off();
				}else{
					SetSystemStatus(SYS_STATUS_IDLE);//系统状态-待机
				}
				break;

			case FRAME_WRITE_SN://写序列号
				break;
			
			case FRAME_CLR_BOOT_NUM://清开机次数
				break;
			case FRAME_ITEM://设置测试项目
				switch(sec_king)
				{
					case 0x00:
						SaveData.Setup.Group_Item=0;
						break;
					case 0x01:
						SaveData.Setup.Group_Item=1;
						break;
					case 0x10:
						SaveData.Setup.Group_Item=2;
						break;
					case 0x11:
						SaveData.Setup.Group_Item=3;
						break;
					default:
						break;
				}
				SaveGroup();//保存组别
				Store_set_flash();
				Disp_Idle_Menu();//显示待测界面
				break;
			case FRAME_DATA://数据帧
				SaveData.Group=str[1]-1;
				switch(sec_king)
				{
					case 0xAC:
						SaveData.Setup.Item=0;
						SaveData.Setup.Output=(u16)BCDtoHex1(str[2],1)*100+BCDtoHex1(str[3],1);
						SaveData.Setup.High=(u16)BCDtoHex1(str[4],1)*100+BCDtoHex1(str[5],1);
						SaveData.Setup.Low=(u16)BCDtoHex1(str[6],1)*100+BCDtoHex1(str[7],1);
						SaveData.Setup.RampDelay=(u16)BCDtoHex1(str[8],1)*100+BCDtoHex1(str[9],1);
						SaveData.Setup.TestTime=(u16)BCDtoHex1(str[10],1)*100+BCDtoHex1(str[11],1);
						SaveData.Setup.Arc=str[12];
						if(str[13]==0x50)
							SaveData.Setup.Freq=0;
						else
							SaveData.Setup.Freq=1;
						break;
					case 0xDC:
						SaveData.Setup.Item=1;
						SaveData.Setup.Output=(u16)BCDtoHex1(str[2],1)*100+BCDtoHex1(str[3],1);
						SaveData.Setup.High=(u16)BCDtoHex1(str[4],1)*100+BCDtoHex1(str[5],1);
						SaveData.Setup.Low=(u16)BCDtoHex1(str[6],1)*100+BCDtoHex1(str[7],1);
						SaveData.Setup.RampDelay=(u16)BCDtoHex1(str[8],1)*100+BCDtoHex1(str[9],1);
						SaveData.Setup.TestTime=(u16)BCDtoHex1(str[10],1)*100+BCDtoHex1(str[11],1);
						SaveData.Setup.Arc=str[12];
						break;
					case 0xAD:
						SaveData.Setup.I_Volt=(u16)BCDtoHex1(str[2],1)*100+BCDtoHex1(str[3],1);
						SaveData.Setup.I_High=(u16)BCDtoHex1(str[4],1)*100+BCDtoHex1(str[5],1);
						SaveData.Setup.I_Low=(u16)BCDtoHex1(str[6],1)*100+BCDtoHex1(str[7],1);
						SaveData.Setup.I_Delay=(u16)BCDtoHex1(str[8],1)*100+BCDtoHex1(str[9],1);
						
						break;
					
				
				}
				SaveGroup();//保存组别
				Store_set_flash();
				Disp_Idle_Menu();//显示待测界面
				break;
			case FRAME_SELECT_GROUP:
				SaveData.Group=sec_king-1;
				SaveGroup();
				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
				ReadSetByGroup();
				Parameter_valuecomp();//比较设置参数
				Disp_Idle_Menu();//显示待测界面
				break;		
			default:
				break;
			
		}
//	Disp_Idle_Menu();//显示待测界面
	}
}else if(SaveData.pselect == 1){//通讯协议2
	if (ComBuf.rec.end)//接收数据结束
	{
		memcpy(recbuf,&ComBuf.rec.buf[0],30);
		lenth=recbuf[2];//数据长度
		kind=recbuf[3];//命令字
		ComBuf.rec.end=FALSE;//接收缓冲可读标志复位
		ComBuf.rec.ptr=0;//接收指针清零
	}
	
	switch(kind)
	{
		case TEST_RST://测试/复位命令
		{
			if(lenth == 2)
			{
				if(recbuf[4] == 'T')//测试命令
				{
					run_stemp=0;
					SetSystemStatus(SYS_STATUS_START);//系统状态-启动测试
					respond = 1;
				}else if(recbuf[4] == 'R'){//复位命令
					if(GetSystemStatus() == SYS_STATUS_TEST){
						SetSystemMessage(MSG_PAUSE);//系统信息-暂停测试
						SetSystemStatus(SYS_STATUS_TEST_PAUSE);//系统状态-待机
						Plc_Start_Off();
						respond = 1;
					}else{
						SetSystemStatus(SYS_STATUS_IDLE);//系统状态-待机
					}
				}else if(recbuf[4] == 'S'){//读数据命令
					SendRes();
				}
			}else if(lenth == 3){
				if(recbuf[4] == 't')//选择组别并测试命令
				{
					run_stemp=0;
					SaveData.Group=recbuf[5];
					SaveGroup();
					SetSystemStatus(SYS_STATUS_IDLE);//待机状态
					ReadSetByGroup();
					Parameter_valuecomp();//比较设置参数					
					SetSystemStatus(SYS_STATUS_START);//系统状态-启动测试
				}
			}
		}break;
		case GROUPSET://组别设置
		{
			SaveData.Group=recbuf[4];
			SaveGroup();
			SetSystemStatus(SYS_STATUS_IDLE);//待机状态
			ReadSetByGroup();
			Parameter_valuecomp();//比较设置参数
			Disp_Idle_Menu();//显示待测界面
		}break;
		case BASICSET:	//设置组别参数
		{
			U2.w_ma = recbuf[4];
			SaveData.Setup.Group_Item = U2.BIT_FLAG.item;//测试项目
			SaveData.Setup.Item = U2.BIT_FLAG.ACDC;//交直流
			SaveData.Setup.Freq = U2.BIT_FLAG.ACWF;//频率
			SaveData.Setup.Arc = U2.BIT_FLAG.ARC;//电弧
			
			SaveData.Setup.I_Volt = recbuf[5];//绝缘测试输出电压
			SaveData.Setup.Output = (u16)(recbuf[6]<<8) + recbuf[7];//耐压测试输出电压
			SaveData.Setup.High=(u16)(recbuf[8]<<8) + recbuf[9];//耐压测试漏电上限
			SaveData.Setup.Low=(u16)(recbuf[10]<<8) + recbuf[11];//耐压测试漏电下限
			SaveData.Setup.RampDelay=(u16)(recbuf[12]<<8) + recbuf[13];//耐压缓升时间
			SaveData.Setup.TestTime=(u16)(recbuf[14]<<8) + recbuf[15];//耐压测试时间
			SaveData.Setup.I_High=(u16)(recbuf[16]<<8) + recbuf[17];//绝缘上限
			SaveData.Setup.I_Low=(u16)(recbuf[18]<<8) + recbuf[19];//绝缘下限
			SaveData.Setup.I_Delay=(u16)(recbuf[20]<<8) + recbuf[21];//延时判定
			
			SaveGroup();//保存组别
			Store_set_flash();
			Disp_Idle_Menu();//显示待测界面
		}break;
	}
}
#endif
}

//==========================================================
//函数名称：Read_Ad
//函数功能：读取A/D值
//入口参数：无
//出口参数：无
//创建日期：2014.11.08 
//修改日期：2015.08.26 10:32
//备注说明：无
//==========================================================
void Read_Ad(void)
{
	vu8 i;
	vu32 vol;
	vu32 cur;

	vol=0;
	cur=0;
	for(i=0;i<16;i++)
	{
		vol+=Read_Ad_Ch0();//读取通道0的A/D值
		cur+=Read_Ad_Ch1();//读取通道1的A/D值
	}
	Voltage=(u16)(vol>>4);//累加平均
	Current=(u16)(cur>>4);//累加平均
}

//==========================================================
//函数名称：Ad_Filter
//函数功能：A/D值滤波
//入口参数：无
//出口参数：无
//创建日期：2014.11.08 
//修改日期：2015.08.26 10:35
//备注说明：Voltage，Current的AD值滤波处理
//==========================================================
void Ad_Filter(void)
{
	vu8 i;
	vu32 sum;

	static vu16 LastVoltage;//上次值
	static vu16 LastCurrent;//上次值

	if(AdCount<AD_BUF_LENGTH)//缓冲完成判别
		AdCount++;//AD值计数

	//左移更新缓冲，出一个进一个
	for(i=(AD_BUF_LENGTH-1);i>0;i--)
	{
		Vbuf[i]=Vbuf[i-1];
	}
	Vbuf[0]=Voltage;//更新最新值

	//取平均值
	sum=0;
	i=AdCount;
	while(i--)
	{
		sum+=Vbuf[i];//累加
	}
	sum/=AdCount;//平均
	Voltage=(u16)sum;
	
	//跳动范围内取上次值作为本次值
//	if(abs(Voltage-LastVoltage)<2)//跳动范围判别
//		Voltage=LastVoltage;
//	else
//		LastVoltage=Voltage;

	//左移更新缓冲，出一个进一个
	for(i=(AD_BUF_LENGTH-1);i>0;i--)
	{
		Ibuf[i]=Ibuf[i-1];
	}
	Ibuf[0]=Current;//更新最新值

	//取平均值
	sum=0;
	i=AdCount;
	while(i--)
	{
		sum+=Ibuf[i];//累加
	}
	sum/=AdCount;//平均
	Current=(u16)sum;
	
	//跳动范围内取上次值作为本次值
//	if(abs(Current-LastCurrent)<2)//跳动范围判别
//		Current=LastCurrent;
//	else
//		LastCurrent=Current;
}

//==========================================================
//函数名称：Get_Result
//函数功能：计算测试值结果
//入口参数：无
//出口参数：无
//创建日期：2014.11.08 
//修改日期：2015.08.27 14:43
//备注说明：更新Voltage
//==========================================================
void Get_Result(void)
{
	u32 dat;

	//最大AD值判别
	if(Voltage>AD_MAX)//最大AD值判别
		Voltage=AD_MAX;


	//最大AD值判别
	if(Current>AD_MAX)//最大AD值判别
		Current=AD_MAX;
	switch(Test_mid.set_item)
	{
		case I_SETUP:
			//dat=Voltage*10;//放大10倍
			
			dat=jisuandianzu(Cal[7+Range].Num,Cal[7+Range].NumAd,Current,Voltage,Cal[2].NumAd);
			Resistance=/*(u16)*/dat;
		
			if(Resistance > 900)
			{
				dat=jisuandianzu(Cal[7+3].Num,Cal[7+3].NumAd,Current,Voltage,Cal[2].NumAd);
			}
			Resistance=/*(u16)*/dat;
			
			dat=Voltage*10;//放大10倍
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//四舍五入
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			//校准处理
			break;
		case W_SETUP:
			dat=Current*10;//放大10倍	
			if(SaveData.Setup.Item==0)
			{
				dat*=Cal[3+Range].Num;
				dat/=Cal[Range+3].NumAd;
				if(dat%10>4)dat+=10;
					dat/=10;
				Test_value.Test_I=dat;
				
				
				dat=Voltage*10;//放大10倍
				dat*=Cal[0].Num;
				dat/=Cal[0].NumAd;

				//四舍五入
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
							
			}
			else
			{
				dat*=Cal[5+Range].Num;
				dat/=Cal[Range+5].NumAd;
				if(dat%10>4)dat+=10;
					dat/=10;
				Test_value.Test_I=dat;
				
				dat=Voltage*10;//放大10倍
				dat*=Cal[1].Num;
				dat/=Cal[1].NumAd;

				//四舍五入
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			}

			//四舍五入
			
			break;
		case W_ISETUP:
			if(run_stemp==0)
			{
				dat=Current*10;//放大10倍	
				if(SaveData.Setup.Item==0)
				{
					dat*=Cal[3+Range].Num;
					dat/=Cal[Range+3].NumAd;
					//四舍五入
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//放大10倍
					
					dat*=Cal[0].Num;
					dat/=Cal[0].NumAd;

					//四舍五入
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
					
				}
				else
				{
					dat*=Cal[5+Range].Num;
					dat/=Cal[Range+5].NumAd;
					//四舍五入
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//放大10倍
					dat*=Cal[1].Num;
					dat/=Cal[1].NumAd;

					//四舍五入
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
				
				}
				
			
			}else
			{
				//dat=jisuandianzu(Cal[Range].Num,Cal[Range].NumAd,Current,Voltage,Cal[0].NumAd);
				dat=jisuandianzu(Cal[7+Range].Num,Cal[7+Range].NumAd,Current,Voltage,Cal[2].NumAd);
				Resistance=dat;
				
				if(Resistance > 900)
				{
					dat=jisuandianzu(Cal[7+3].Num,Cal[7+3].NumAd,Current,Voltage,Cal[2].NumAd);
				}
				Resistance=/*(u16)*/dat;
				dat=Voltage*10;//放大10倍
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//四舍五入
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			
			}
			break;
		case I_WSETUP:
			if(run_stemp==0)
			{
				//dat=jisuandianzu(Cal[Range].Num,Cal[Range].NumAd,Current,Voltage,Cal[0].NumAd);
				dat=jisuandianzu(Cal[7+Range].Num,Cal[7+Range].NumAd,Current,Voltage,Cal[2].NumAd);
				Resistance=dat;
				if(Resistance > 900)
				{
					dat=jisuandianzu(Cal[7+3].Num,Cal[7+3].NumAd,Current,Voltage,Cal[2].NumAd);
				}
				Resistance=/*(u16)*/dat;
				dat=Voltage*10;//放大10倍
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//四舍五入
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			
			}else
			{
				dat=Current*10;//放大10倍	
				if(SaveData.Setup.Item==0)
				{
					dat*=Cal[3+Range].Num;
					dat/=Cal[Range+3].NumAd;
					//四舍五入
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//放大10倍
					
					dat*=Cal[0].Num;
					dat/=Cal[0].NumAd;

					//四舍五入
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
					
				}
				else
				{
					dat*=Cal[5+Range].Num;
					dat/=Cal[Range+5].NumAd;
					//四舍五入
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//放大10倍
					dat*=Cal[1].Num;
					dat/=Cal[1].NumAd;

					//四舍五入
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
				
				}
			
			}
			break;
		default:
			break;
	
	
	}
	
	
		//校准处理
	
	
	//Resistance= jisuandianzu(u16 bzdzn,u16 bzdzadn,u16 I_ad,u16 dianya);
}



//==========================================================
//END
//==========================================================
