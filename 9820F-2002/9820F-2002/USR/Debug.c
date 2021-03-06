//==========================================================
//文件名称：Debug.c
//文件描述：调试设置子程序
//文件版本：Ver1.0
//创建日期：2015.10.26
//修改日期：2015.10.29 14:38
//文件作者：黄宏灵
//备注说明：无
//注意事项：无
//==========================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <absacc.h>
//#include <intrins.h>
#include "pbdata.h"
#include "Debug.h"
//Cal_TypeDef Cal[8];
//默认校准数据


const vu16 DefaultCalibrate[][2]=
{
	 1000, 1000, 
	 1000, 1000, 
	 5000, 3200, 
	 5000, 3200, 
	 5000, 3200, 
	 5000, 3200,
	 5000, 3200, 
	 5000, 3200,
};
//==========================================================
//校准值上、下限
const u16 CalibrateLimit[][2]=
{
	 4200, 3800,
	4200, 3800, 
	1100, 900, 
	 1100, 900, 
	 1100, 900, 
	 
	 600, 400, 
	 1100, 900, 
	 1100, 900, 
	 
	1100, 900, 
	1100, 900, 
	1100, 900, 
};
const u16 CalibrateLimitvalue[]=
{
	 4000, 
	 1000,  
	 1000,  
	 4000,  
	 500,  
	 1000,  
	 1000,  
	 1000, 
	1000,
	1000,
};
//const u8 Debug_Dot[]={1,2,3,3,2,1,3,2,1};
//==========================================================
//调试菜单
//==========================================================
//校正菜单
const u8 DebugMenu[][16+1]=
{
	"(1)AC4000V   ADJ",
	"(2)DC4000V   ADJ",
	"(3)R_1000V   ADJ",
	"(4)10.00mA   ADJ",
	"(5)1.000mA   ADJ",
	
	"(6)5.000mA   ADJ",
	"(7)1.000mA   ADJ",
	
	"(8)1.000M    ADJ",
	"(9)10.00M    ADJ",
	"(10)100.0M   ADJ",
//	"(11)1000 M   ADJ",
//	"(6)SAMPLE = ",
};
const u8 Debugext[16+1]=
{
	"<TEST> to Calibr",

};
const u8 Debugtext[20+1]=
{
	"<EXIT> to Save",

};
const u8 CalIrTab[][20+1]=
{
	"1.VOLADJ 500.0V ",
	"2.VOLADJ 50.00V ",
	"3.VOLADJ 5.000V ",
	"4.RESADJ 100.0K ",
	"5.RESADJ 1.000M ",
	"6.RESADJ 10.00M ",
	"7.RESADJ 100.0M ",
	"8.RESADJ 1.000G ",

};
const u8 CalTestTab[][16+1]=
{
	"1.4000 V   ",
	"2.4000 V   ",
	"3.1000 V   ",
	"4.10.00mA  ",
	"5.1.000mA  ",
	
	"6.5.00 mA  ",
	"7.1.000mA  ",
	
	"8.1.000 M  ",
	"9.10.00 M  ",
	"10.100.0 M ",
//	"11.1000 M  ",

};
//==========================================================
//确认提示
const u8 EnterTab1[16+1]=
{
	"Enter by <SET> "
};
//const u8 DebugMenu[][20+1]=
//{
//	"1.Res Calibrate     ",
//	"2.Vol Calibrate     ",
//	"3.Default Load      ",
//};
#define DEBUG_MENU_MAX (sizeof(DebugMenu)/sizeof(DebugMenu[0]))

//==========================================================
//函数名称：Disp_Debug_Menu
//函数功能：显示菜单
//入口参数：index:第几项
//出口参数：无
//创建日期：2015.10.29
//修改日期：2015.10.29 14:42
//备注说明：无
//==========================================================
void Disp_Debug_Menu(u8 index)
{
	//第一行
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8 *)&DebugMenu[index%DEBUG_MENU_MAX][0]);
	LcdAddr.x=9;LcdAddr.y=0;
	Lcd_SetAddr();
	
		
//	//第二行
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8 *)EnterTab1);//显示确认提示
}

//==========================================================
//函数名称：Debug_Process
//函数功能：调试设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.10.29
//修改日期：2015.10.29 14:43
//备注说明：无
//==========================================================
void Debug_Process(void)
{
	vu8 key;
	vu8 index;
	u8 *pt;
	u8 *pt2;
	u8 i;
	u8 f_disp;

	index=0;
	f_disp=TRUE;//显示

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if(f_disp==TRUE)//显示更新
		{
			f_disp=FALSE;
			Disp_Debug_Menu(index);//显示界面	
			
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//设置键
			//case L_KEY_SET:	//长按设置键
				Disp_Clr( );//清屏
				Res_Calibrate(index);//电阻校准处理

				f_disp=TRUE;
				break;
	
			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
				if(index<(DEBUG_MENU_MAX-1))index++;
				else index=0;
				f_disp=TRUE;//显示
				break;

			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
				if(index>0)index--;
				else index=(DEBUG_MENU_MAX-1);
				f_disp=TRUE;//显示
				break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_TEST);//测试状态
//				break;
	
			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				i=11;
				pt=(u8*)(&SaveData.Calibrate);//校准值首地址
				pt2=(u8*)(&Cal);//更新通用校准值
				key=i*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//校验和保存校准数据
				StoreCalDate();//保存校准值
				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				//SetSystemStatus(SYS_STATUS_IDLE);//待机状态
				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//函数名称：Default_Calibrate
//函数功能：加载默认校准值
//入口参数：无
//出口参数：无
//创建日期：2015.02.13
//修改日期：2015.08.31 10:29
//备注说明：无
//==========================================================
void Default_Calibrate(void)
{
	u8 key;

	Disp_Clr();//清屏
	LcdAddr.x=5;LcdAddr.y=0;
	Disp_Str("恢复默认值?");//显示
	LcdAddr.x=1;LcdAddr.y=1;
	Disp_Str("按<确认>键恢复,<左,右>键返回");//显示

	while(SystemStatus==SYS_STATUS_DEBUG)
	{
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
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
//	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
//				break;
//
			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				return;
//				break;

			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				LoadDefaultCalibrate();//加载默认校准值
				LcdAddr.x=8;LcdAddr.y=20;
				Disp_Str("恢复默认值成功");//显示
//				Beep_One();//蜂鸣器响一声
//				Delay_100ms(12);//延时1.2s
				return;
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				return;
//				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//绝缘校准菜单

//==========================================================
//绝缘校准项
enum CalIrEnum
{	
	CAL_IR_1kV ,
	CAL_IR_500k ,
	CAL_IR_5M ,
	CAL_IR_50M ,
	CAL_IR_500M ,
};
const u8 Debug_Dot[11]=
{0,0,0,2,3,2,3,3,2,1,0};
//==========================================================
//函数名称：Res_Calibrate
//函数功能：电阻校准处理
//入口参数：无
//出口参数：无
//创建日期：2015.02.13
//修改日期：2015.08.31 10:29
//备注说明：无
//==========================================================
void Res_Calibrate(u8 num)
{
	u8 i;
	
	u8 key;
	u8 dot,lenth;
	u16 set_high,set_low;
	u8 F_Disp;//显示更新标志
	u8 *pt;
	u8 *pt2;
	F_Disp=TRUE;//显示更新
//	MenuSelect=0;//取当前项

	delay_ms(50);//硬件延�

	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)&DebugMenu[num][0]);//当前项高亮显示
	LcdAddr.y=1;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)Debugext);
	//CalibrateLimit	
	for(i=0;i<DEBUG_MENU_MAX;i++)
	{
		if((Cal[i].Num>CalibrateLimit[num][0])||(Cal[i].Num<CalibrateLimit[num][1]))
			Cal[i].Num=CalibrateLimitvalue[i];
	
	}
	pt=(u8*)(&SaveData.Calibrate);//校准值首地址
	pt2=(u8*)(&Cal);//更新通用校准值
	key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
	set_high=CalibrateLimit[num][0];//上限
	set_low=CalibrateLimit[num][1];//下限
	switch(num)
	{
		case 0:
			Range_Control(0);
			if(SaveData.Calibrate.AcwVol[0].Num>set_high||SaveData.Calibrate.AcwVol[0].Num<set_low)
				Cal[num].Num=4000;//4000v
			break;
		case 3:
			
		
			Range_Control(0);
			if(SaveData.Calibrate.AcwCur[0].Num>set_high||SaveData.Calibrate.AcwCur[0].Num<set_low)
				Cal[num].Num=1000;//10.00mA
		break;
		case 4:
			Range_Control(1);
			if(SaveData.Calibrate.AcwVol[1].Num>set_high||SaveData.Calibrate.AcwVol[1].Num<set_low)
				Cal[num].Num=1000;//2.000mA
			break;
		case 1:
			if(SaveData.Calibrate.DcwVol[0].Num>set_high||SaveData.Calibrate.DcwVol[0].Num<set_low)
				Cal[num].Num=4000;//DC4000V
		break;
		case 5:
			Range_Control(0);
			if(SaveData.Calibrate.DcwCur[0].Num>set_high||SaveData.Calibrate.DcwCur[0].Num<set_low)
				Cal[num].Num=500;//DC5.00mA
			break;
		case 6:
			Range_Control(1);
			if(SaveData.Calibrate.DcwCur[1].Num>set_high||SaveData.Calibrate.DcwCur[1].Num<set_low)
				Cal[num].Num=1000;//2.000mA
		break;
		case 2:
			if(SaveData.Calibrate.IrVol[0].Num>set_high||SaveData.Calibrate.IrVol[0].Num<set_low)
				Cal[num].Num=1000;//1000V
			break;
		case 7:
			Range_Control(1);
			if(SaveData.Calibrate.IrCur[0].Num>set_high||SaveData.Calibrate.IrCur[0].Num<set_low)
				Cal[num].Num=1000;//0.500M
		break;
		case 8:
			Range_Control(2);
			if(SaveData.Calibrate.IrCur[1].Num>set_high||SaveData.Calibrate.IrCur[1].Num<set_low)
				Cal[num].Num=1000;
			break;
		case 9:
			Range_Control(3);
			if(SaveData.Calibrate.IrCur[2].Num>set_high||SaveData.Calibrate.IrCur[2].Num<set_low)
				Cal[num].Num=1000;
		break;
		case 10:
			Range_Control(3);
			if(SaveData.Calibrate.IrCur[3].Num>set_high||SaveData.Calibrate.IrCur[3].Num<set_low)
				Cal[num].Num=1000;
			break;
		default:
		break;
	
	}

//		Test_value.Test_I=Read_Channel(1);//电压AD值  channel1  电流
//		AD7705_init(0);
//		Test_value.Test_v.Test_v=Read_Channel(0);//电流AD值	
	i=1;
	//while(SystemStatus==SYS_STATUS_DEBUG)
	while(i)
	{
//		Read_Ad();
//		Get_Result();
		if(F_Disp==TRUE)
		{
			F_Disp=FALSE;//显示更新
			dot=Debug_Dot[num];
			lenth=4;
			Hex_Format(Cal[num].Num, dot, lenth, FALSE);
			LcdAddr.y=0;
			LcdAddr.x=10;
			Disp_StrAt(DispBuf);
			
			LcdAddr.y=0;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)&DebugMenu[num][0]);//当前项高亮显示
			LcdAddr.y=1;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)Debugext);
//			LcdAddr.x=15;
//			Lcd_SetAddr();

		}				
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
		switch(key)
		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				break;

//			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
//				break;
	
//			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
//				break;

			case KEY_UP:	//左键
				
//					if(Cal[num].Num>set_high)
//						Cal[num].Num=set_low;
//					
//					else
//						Cal[num].Num++;	
					F_Disp=TRUE;
			break;
			case L_KEY_UP:	//长按左键
//					if(Cal[num].Num>set_high)
//						Cal[num].Num=set_low;
//					
//					else
//					Cal[num].Num+=10;		
					F_Disp=TRUE;
//				if(MenuSelect>0)
//					MenuSelect--;
//				else
//					MenuSelect=sizeof(CalIrTab)/sizeof(CalIrTab[0])-1;
//				F_Disp=TRUE;//显示更新
				break;

			case KEY_DOWN:		//右键

				F_Disp=TRUE;
				break;
			case L_KEY_DOWN:	//长按右键

				F_Disp=TRUE;

				break;
	
			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
//				Disp_Clr( );
//				dot=Debug_Dot[num];
////				if(num==4)
////					lenth=5;
////				else
//				lenth=4;
//				Hex_Format(Cal[num].Num, dot, lenth, 0);
//				LcdAddr.y=1;
//				LcdAddr.x=9;
//				if(num<4)
//				Disp_StrAt("RES:");
//				else
//				Disp_StrAt("VOL:");	
//				Disp_StrAt(DispBuf);
//				if(num==0||num==1)
//					Disp_Char('m');
//				else
//					Disp_Char(' ');	
//				if(num<4)
//					Disp_Char(OHM);
//				else
//					Disp_Char('V');	
//				
////				Cal[num].NumAd=Res.Real;
//				if(num==4)
//					lenth=5;
//				else
//					lenth=4;
////				Hex_Format(Cal[num].NumAd, 0, lenth, 0);
//				LcdAddr.y=1;
//				LcdAddr.x=0;
//				Disp_StrAt("AD:");
//				Disp_StrAt(DispBuf);
				return;
//				break;
	
			case KEY_START:		//启动键
			case L_KEY_START:	//长按启动键
				CalTest_Process(num);//校准测试处理
				Disp_Clr( );//清屏
				F_Disp=TRUE;//显示更新
			i=0;
				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				return;
//				break;
			
			default:
				break;
		}
		
	}
	
}

//==========================================================
//函数名称：CalTest_Process
//函数功能：校准测试处理
//入口参数：无
//出口参数：无
//创建日期：2015.08.31
//修改日期：2015.08.31 10:29
//备注说明：无
//==========================================================
void CalTest_Process(u8 num)
{
	u8 *pt;
	u8 *pt2;
	
	u8 i;
	u8 blinkT;
	vu8 key;
	u8 count;//步进计数器
	
	vu16 dat;
	vu32 temp;

	u8 f_disp=FALSE;//显示更新标志

//	bool f_sort=FALSE;//分选标志
//	bool f_upper=FALSE;//量程过压标志
//	bool f_below=FALSE;//量程欠压标志
//	bool f_switch=FALSE;//量程切换标志

	vu16 set_high;//测试值上限
	vu16 set_low;//测试值下限
	vu16 ad_high;//AD值上限
	vu16 ad_low;//AD值下限

	Disp_Clr( );//清屏

	//读取校准值上下限
//	i=MenuSelect;//当前选择项
//	i*=4;//每项4字节
	set_high=CalibrateLimit[i][0];//上限
	set_low=CalibrateLimit[i][1];//下限
//	i++;
//	ad_high=CalibrateLimit[i][0];//上限
//	ad_low=CalibrateLimit[i][1];//下限

	//读取当前项目的校准值
		i=11;//IR
	pt=(u8*)(&SaveData.Calibrate);//校准值首地址
	pt2=(u8*)(&Cal);//更新通用校准值
	key=i*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
//	Electro_Test(1);
	//全局变量处理
	Voltage=0;//电压
	Current=0;//电流
	Resistance=0;//电阻
 	Range=0;//量程初始化
	F_100ms=FALSE;//100ms定时


	//声光状态控制
	Led_Pass_Off();//关合格灯
	Led_Fail_Off();//关报警灯
	Led_HV_On();//开高压灯
	Beep_One();//响一声

	count=0;//步进计数器
	SetSystemMessage(MSG_TEST);//系统信息
	SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//设置延时时间，1000/10=100mS
	LcdAddr.y=1;
	LcdAddr.x=2;
	Disp_StrAt((u8 *)Debugtext);
	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)CalTestTab[num]);
	Da_Out(0);
	switch(num)
	{
		case 0://交流
			Dc_Output_Off();//DC输出和采样
			Frequency_Control(FREQ_50);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			Da_Out(DefaultCalDaOut[0]);//4000V的DA值2430
			//Range_Control(0);
			break;
		case 1:
			Dc_Output_On();//DC输出和采样
			Frequency_Control(FREQ_400);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			Da_Out(DefaultCalDaOut[1]);//4000V的DA值
			
			break;
		case 2:
			Dc_Output_On();//DC输出和采样
			Frequency_Control(FREQ_400);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			Da_Out(DefaultCalDaOut[2]);

			break;
		case 3://直流
			
			//break;
		case 4:
			Dc_Output_Off();//DC输出和采样
			Frequency_Control(FREQ_50);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			//Da_Out(610);//610
			Da_Out(DefaultCalDaOut[2]);
		break;
		case 5:
			Dc_Output_On();//DC输出和采样
			Frequency_Control(FREQ_400);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			Da_Out(360);
		break;
		case 6:

		case 7:
		case 8:
		case 9:
		case 10:
			Dc_Output_On();//DC输出和采样
			Frequency_Control(FREQ_400);//输出频率控制
			Sin_Clk_Enable();//输出正弦波频率
			Plc_Start_On();//开PLC启动
			Da_Out(DefaultCalDaOut[2]);
			//Da_Out(610);//610
			break;
		default:
		Da_Out(0);
			break;
	
	}

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if( GetSoftTimerOut(DISP_SOFTTIMER) )//等待延时结束
		{
			F_100ms=TRUE;
			SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//设置延时时间，1000/10=100mS
		}

		if(F_100ms==TRUE)//100ms定时处理
		{
			
			F_100ms=FALSE;
			f_disp=TRUE;//显示更新

			//测试灯闪烁控制
			blinkT++;//闪烁时间计时
			blinkT%=9;
			if(blinkT<5)//灯闪烁时间
				Led_HV_On();//开测试灯
			else
				Led_HV_Off();//关测试灯

		}

		//读取A/D值
		Test_value.Test_I=Read_Ad_Ch1();//电压AD值  channel1  电流
		Test_value.Test_v.Test_v=Read_Ad_Ch0();//电流AD值	
		//Read_Ad();//读取AD值
		if(num==0||num==1||num==2)
			Cal[num].NumAd=Test_value.Test_v.Test_v;
		else if(num==3||num==6||num==4|num==5)
		{
			Cal[num].NumAd=Test_value.Test_I;
		
			
		}else
		{
				
			Res_count.v=Test_value.Test_v.Test_v*10;
			if(Test_value.Test_I<10)
				Test_value.Test_I=10;
			Res_count.i=(u32)Test_value.Test_I;
			
			Res_count.rate=RANGE_RATE[num-7];
			Get_Res();
			Get_FFT();
			
			Cal[num].NumAd=Res_count.i;
		
		}


 		//上下限判别
//		if(f_sort==TRUE)
		{
//					if(MenuSelect==0)
//						dat=Voltage;
//					else
//						dat=Resistance;

			//上下限报警
			if((dat>set_high)||(dat<set_low))//超上下限
			{
//				Beep_One();//蜂鸣器响一声
			}
		}

		if(f_disp==TRUE)//显示更新
		{
			f_disp=FALSE;//显示更新
			LcdAddr.x=10; LcdAddr.y=0;

			Hex_Format(Cal[num].Num,Debug_Dot[num],4,TRUE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);
//			LcdAddr.x=DATA_ADDR_X+WIDTH_OF_VALUE;
//			Hex_Format(Current,2,4,1);//数据格式化到DispBuf
		}
		
		key=Key_Read();//读取按键
		switch(key)
		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				break;
	
			case KEY_UP:	//上键
				count=0;//步进计数器
				Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_UP:	//长按上键
				count++;//步进计数器
				if(count>10)//步进计数器
					Cal[num].Num+=10;
				else
					Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_DOWN:		//下键
				count=0;//步进计数器
				Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_DOWN:	//长按下键
				count++;//步进计数器
				if(count>10)//步进计数器
					Cal[num].Num-=10;
				else
					Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
				count=0;//步进计数器
				break;

			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
				count=0;//步进计数器
				break;

			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				Sin_Clk_Disable();//输出正弦波频率
				Plc_Start_Off();//开PLC启动
				Da_Out(0);//4000V的DA值
//				Output_Off();//输出关闭
				Led_HV_Off();
				//更新当前项目的校准值
					//i=5;//IR
//					pt=(u8*)(&SaveData.Calibrate);//校准值首地址
//				pt2=(u8*)(&Cal);//更新通用校准值
				pt=(u8*)(&SaveData.Calibrate);//校准值首地址
				pt2=(u8*)(&Cal);//更新通用校准值
				key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//校验和保存校准数据
//				SaveCalibrate();//保存校准值
				StoreCalDate();
				Led_HV_Off();
				return;
//				break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				break;

			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				Sin_Clk_Disable();//输出正弦波频率
				Plc_Start_Off();//开PLC启动
				Da_Out(0);//4000V的DA值
//				Output_Off();//输出关闭
				Led_HV_Off();
//				Electro_discharge(0);
				return;
//				break;
			
			default:
				break;
		}
	}
	
}

//==========================================================
//END
//==========================================================

