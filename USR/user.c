//==========================================================
//文件名称：User.c
//文件描述：菜单设置子程序
//文件版本：Ver1.0
//创建日期：2014.12.15
//修改日期：2015.09.06 11:15
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
////#include <math.h>
////#include <absacc.h>
////#include <intrins.h>
#include "pbdata.h"
//#include <absacc.h>

//#include "TypeDefine.h"
//#include "GlobalValue.h"
//#include "Hardware.h"
//#include "Delay.h"
//#include "Interrupt.h"
//#include "Lcd240128.h"
//#include "Disp.h"
//#include "Keyboard.h"
//#include "Beep.h"
//#include "Isp.h"
//#include "Uart0.h"
//#include "Com.h"
//#include "User.h"

//==========================================================
const u8 Sin[]=
{
	0x80,0x83,0x86,0x89,0x8C,0X8F,0x92,0X95,
	0x97,0x9A,0x9D,0xA0,0xA3,0xA7,0xAA,0xAD,
	0xB0,0xB3,0xB6,0xB9,0xBC,0xBE,0xC1,0xC4,
	0xC6,0xC9,0xCB,0xCE,0xD0,0xD3,0xD5,0xD7,
	0xDA,0xDC,0xDE,0xE0,0xE2,0xE4,0xE6,0xE8,
	0xEA,0xEB,0xED,0xEE,0xF0,0xF1,0xF3,0xF5,
	0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFC,
	0xFD,0xFD,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,
	0xFD,0xFC,0xFB,0xFA,0xF9,0xF8,0xF7,0xF6,
	0xF5,0xF4,0xF2,0xF1,0xEF,0xEE,0xEC,0xEA,
	0xE9,0xE7,0xE5,0xE3,0xE1,0xDF,0xDD,0xDA,
	0xD8,0xD6,0xD4,0xD1,0xCF,0xCC,0xCA,0xC7,
	0xC5,0xC2,0xBF,0xBC,0xBA,0xB7,0xB4,0xB1,
	0xAE,0xAB,0xA8,0xA5,0xA2,0x9F,0x9C,0x99,
	0x96,0x93,0x90,0x8D,0x89,0x86,0x83,0x80,
	0x80,0x7C,0x79,0x76,0x72,0x6F,0x6C,0x69,
	0x66,0x63,0x60,0x5D,0x5A,0x57,0x55,0x51,
	0x4E,0x4C,0x48,0x45,0x43,0x40,0x3D,0x3A,
	0x38,0x35,0x33,0x30,0x2E,0x2B,0x29,0x27,
	0x25,0x22,0x20,0x1E,0x1C,0x1A,0x18,0x16,
	0x15,0x13,0x11,0x10,0x0E,0x0D,0x0B,0x0A,
	0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,
	0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,
	0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
	0x0A,0x0B,0x0D,0x0E,0x10,0x11,0x13,0x15,
	0x16,0x18,0x1A,0x1C,0x1E,0x20,0x22,0x25,
	0x27,0x29,0x2B,0x2E,0x30,0x33,0x35,0x38,
	0x3A,0x3D,0x40,0x43,0x45,0x48,0x4C,0x4E,
	0x51,0x55,0x57,0x5A,0x5D,0x60,0x63,0x66,
	0x69,0x6C,0x6F,0x72,0x76,0x79,0x7C,0x80

};
//位操作增减数值
const u16 POW_NUM[4]=
{
	1000,
	100,
	10,
	1,
};
const u32 RANGE_RATE[5]=
{
	1,
	10,
	100,
	1000,
	1000,
	


};
//==========================================================
const u8 I_TEST_DISP[][6+1]=
{
	"I_Set ",
	"I_Test"

};
const u8 W_TEST_DISP[][6+1]=
{
	"W_Set ",
	"W_Ramp",
	"W_Test"

};
const u8 I_SET[][15+1]=
{
	"I-Voltage=      ",
	"I-High=    M    ",
	"I-Low =    M    ",
	"I-Delay=      s ",
};
const u8 AC_DC_SET[][3+1]=
{
	"AC ",
	"DC ",

};
const u8 FREQ_SET[][2+1]=
{
	"50",
	"60",

};
const u8 GROUP_DISP_ITEM[][5+1]=
{
	"W    ",
	"I    ",
	"W-I  ",
	"I-W  "
};
const u8 GROUP_ITEM[][5+1]=
{
	"W_Set",
	"I_Set",
	"W_Set",
	"I_Set"
	
//	"I    ",
//	"W    ",
//	"I_Set",
//	"W_Set"
};
const u8 I_Sel_Tab[][16+1]=
{
	"Select by^or v ",
	"Range:0.10-1.00",
	"0-9999  0=OFF  ",
	"Range:1-9999   ",
	"0.6-999.90=CONT",
};
const u8 W_SET[][15+1]=
{
	"W-Mode =        ",
	"W-Voltage=    kV",
	"W-High=     mA  ",
	"W-Low =     mA  ",
	"W-Ramp=     s   ",
	"W-Dwell=     s  ",
	"Freq =    HZ    ",
	"W-Arc =         ",
};
const u8 W_Sel_Tab[][16+1]=
{
	"Select by ^ or v",
	"Select by ^ or v",
	"Range:0-5.00kVAC",
	"Range:0.01-12mA ",
	"Range:0.00-12mA ",
	"Range:0.1-999.9 ",
	"R:0.5-999.9 0=C ",
	"Select by ^ or v",
	"Range: 0-9 0=OFF",
	
};

const u8 I_W_SET[][16+1]=
{
	"W-Mode =        ",
	"W-Voltage=    kV",
	"W-High=     mA  ",
	"W-Low =     mA  ",
	"W-Ramp=     s   ",
	"W-Dwell=     s  ",
	"Freq =    HZ    ",
	"W-Arc =         ",
	"I-Voltage=    kV",
	"I-High=      M  ",
	"I-Low =      M  ",
	"I-Delay=      s ",
};
const u8 I_W_Sel_Tab[][16+1]=
{
	"Select by ^ or v",
	"Select by ^ or v",
	"Range:0-5.00kVAC",
	"Range:0.01-12mA ",
	"Range:0.00-12mA ",
	"Range:0.1-999.9 ",
	"R:0.5-999.9 0=C ",
	"Select by ^ or v",
	"Range:0-9 0=OFF ",
	"Range:00.10-1.00",
	"0-9999  0=OFF   ",
	"Range:1-9999    ",
	"0.6-999.9 0=CONT",
};

const u8 I_WDC_Sel_Tab[][16+1]=
{
	"Select by ^ or v",
	"Select by ^ or v",
	"Range:0-6.00kVDC",
	"Range:0.01-5mA  ",
	"Range:0.00-5mA  ",
	"Range:0.1-999.9 ",
	"R:0.5-999.9 0=C ",
	"Select by ^ or v",
	"Range:0-9 0=OFF ",
	"Range:00.10-1.00",
	"0-9999  0=OFF   ",
	"Range:1-9999    ",
	"0.6-999.9 0=CONT",
};

//量程
const u8 RangeTab[][4+1]=
{
	{"AUTO"},
	{"01  "},
	{"02  "},
	{"03  "},
	{"04  "},
	{"05  "},
	{"06  "},
	{"07  "},
};
//==========================================================
//讯响
const u8 BeepTab[][4+1]=
{
	"OFF ",
	"Pass",
	"Fail",
};

//==========================================================
//开关
const u8 SwitchTab[][4+1]=
{
	"OFF ",
	"ON  ",
};
#define FACTORY_MENU_MAX (sizeof(FactoryTab)/sizeof(FactoryTab[0])-1)
//==========================================================
//设置菜单
const u8 SetupMenu[][20+1]=
{
	"1.PARAMETER SETUP   ",
	"2.COMPARE SETUP     ",
	"3.PASSWORD SETUP    ",
	"4.FACTORY INFO      ",
};
//==========================================================
//确认提示
const u8 EnterTab[20+1]=
{
	"  Enter by <SET>    ",
};
//==========================================================
//数值提示
const u8 NumberTab[][20+1]=
{
	"Range:  5 - 500 ",
	"Range:  0 - 999.9 ",
	"Range:  0 - 9999 ",
	"Range:  0 - 9999 ",
};
//==========================================================
//选择提示
const u8 SelectTab[20+1]=
{
	" Select by arrow    ",
};
//==========================================================
//参数菜单
const u8 ParameterTab[][12+1]=
{
	"(1)RANGE  = ",
	"(2)BEEP   = ",
	"(3)CLEAR  = ",
	"(4)EXTRIG = ",
	"(5)RS232C = ",
//	"(6)SAMPLE = ",
};
//==========================================================
//编号
const u8 NumTab[][3]=
{
	"1.",
	"2.",
	"3.",
	"4.",
	"5.",
	"6.",
	"7.",
	"8.",
};
//==========================================================
//系统菜单
const u8 SystemTab[][12+1]=
{
	"(1)Vol_Out= ",
	"(2)T_Time = ",
	"(3)Res_Hi = ",
	"(4)Res_Lo = ",

};
//==========================================================
//系统项上、下限
const u16 SystemLimit[][2]=
{
	{500, 5},
	{9999, 0},
	{9999, 0},
	{9999, 0},
};
//==========================================================
//系统项上、下限
const u16 SystemLimitDot[5]=
{
	0,1,0,0
	
};
//==========================================================
//参数项上、下限
//const u16 ParameterLimit[][2]=
//{
//	{ 3, 0},//选择测试项
//	{ 1, 0},//项目 选择AD/DC
//	{ 600, 10},
//	{ 500, 1},
//	{ 500, 0},
//	{ 9999, 1},
//	{ 9999, 0},
//	{ 1, 0},
//	{ 9, 0},
//	{ 100, 10},
//	{ 9999, 0},
//	{ 9999, 0},
//	{ 9999, 0},
//	
//};
const u16 ParameterLimit[][2]=
{
	{ 3, 0},//选择测试项
	{ 1, 0},//项目 选择AD/DC
	{ 600, 0},
	{ 500, 1},
	{ 500, 0},
	{ 9999, 1},
	{ 9999, 5},
	{ 1, 0},
	{ 9, 0},
	{ 100, 10},
	{ 9999, 0},
	{ 9999, 0},
	{ 9999, 6},
	
};
//const u16 ParameterLimit_AC[][2]=
//{
//	{ 3, 0},//选择测试项
//	{ 1, 0},//项目 选择AD/DC
//	{ 500, 10},
//	{ 1200, 1},
//	{ 1200, 0},
//	{ 9999, 1},
//	{ 9999, 0},
//	{ 1, 0},
//	{ 9, 0},
//	{ 100, 10},
//	{ 9999, 0},
//	{ 9999, 1},
//	{ 9999, 0},
//	
//};
const u16 ParameterLimit_AC[][2]=
{
	{ 3, 0},//选择测试项
	{ 1, 0},//项目 选择AD/DC
	{ 500, 0},
	{ 1200, 1},
	{ 1200, 0},
	{ 9999, 1},
	{ 9999, 5},
	{ 1, 0},
	{ 9, 0},
	{ 100, 10},
	{ 9999, 0},
	{ 9999, 1},
	{ 9999, 6},
	
};

const u16 ParameterComp[][2]=
{
	{ 3, 0},//选择测试项
	{ 1, 0},//项目 选择AD/DC
	{ 600, 0},
	{ 1200, 1},
	{ 1200, 0},
	{ 9999, 1},
	{ 9999, 5},
	{ 1, 0},
	{ 9, 0},
	{ 100, 10},
	{ 9999, 0},
	{ 9999, 1},
	{ 9999, 6},
	
};
const u16 ParameterLimit_dot[]={2,2,2,1,1,0,0,2,0,0,1};
const u16 ParameterLimit_len[]={2,2,2,3,4,4,4,4,1,3,3,4,4,4,4,4};

//==========================================================
//系统状态
const u8 MsgTab[][6+1]=
{
	{"W_TEST"},
	{"IDLE  "},
	{"TEST  "},
	{"ABORT "},
	{"Pass  "},
	{"ARC_F "},
	{"Hi-F  "},
	{"Lo-F  "},
	{"OVER  "},
	
};

//	MSG_IDLE=0 , 
//	MSG_RAMP , 
//	MSG_TEST , 
//	MSG_PAUSE , 
//	MSG_PASS ,
//	MSG_ARC , 
//	MSG_HIGH , 
//	MSG_LOW , 
//	MSG_OVER , 
//	MSG_ERROR ,

//==========================================================
//出厂信息
const u8 FactoryTabS[][20+1]=
{	
//	{"                "},//型号
	{"     JINKO      "},//型号
	{" 7122  VER:2.12 "},//名称
	{" Tel:0519-88226706  "},//电话
	{" Fax:0519-88226808  "},//传真
	{" "},//主页
};

const u8 FactoryTab[][20+1]=
{	
//	{"                "},//型号
	{"     JINKO      "},//型号
	{" 7122  VER:2.12S"},//名称
	{" Tel:0519-88226706  "},//电话
	{" Fax:0519-88226808  "},//传真
	{" "},//主页
};
//2.11增加绝缘1G校准点
//2.12修复通讯协议选择bug
//==========================================================
////参数值小数点固定(0-3: xxxx xxx.x xx.xx x.xxx)
const u8 ParameterDotTab[][PARAMETER_MENU_MAX]=
{
	{0,0,2,2,1,1,2,0},//ACW
	{0,0,2,2,1,1,2,0},//DCW
	{0,0,0,0,1,1,0,0},//IR
	{0,2,0,0,1,1,0,0},//GND
};
//==========================================================
//参数菜单项
enum ParameterMenuEnum
{	
	PARAMETER_MENU_RANGE ,
	PARAMETER_MENU_BEEP ,
	PARAMETER_MENU_CLEAR ,
	PARAMETER_MENU_TRIG ,
	PARAMETER_MENU_UART ,
};

//==========================================================
//系统菜单项
enum SYSTEMMenuEnum
{	
	SYSTEM_MENU_VOUT ,
	SYSTEM_MENU_Ttime,
	SYSTEM_MENU_RH	 ,
	SYSTEM_MENU_RL	 ,
	
};

void Disp_TestMessage(void)
{
	LcdAddr.x=0;LcdAddr.y=0;
	Lcd_SetAddr();//设置坐标
	switch(SaveData.Setup.Group_Item)
	{
		case I_SETUP:
			Disp_Str((u8 *)I_TEST_DISP[1]);
			LcdAddr.x=6;LcdAddr.y=1;
			Disp_StrAt((u8 *)"DC");
			LcdAddr.x=14;LcdAddr.y=1;
			Disp_StrAt((u8*)"M");
			Lcd_WriteData(OHM);
			
		
			break;
		case W_SETUP:
			if(GetSystemMessage()==MSG_RAMP)//缓升
			{
				Disp_Str((u8 *)W_TEST_DISP[1]);
			}else//测试
			{
				Disp_Str((u8 *)W_TEST_DISP[2]);
			}
			LcdAddr.x=6;LcdAddr.y=1;
			if(SaveData.Setup.Item)
				
				Disp_StrAt((u8 *)"DC");
			else
				Disp_StrAt((u8 *)"AC");
			LcdAddr.x=14;LcdAddr.y=1;
			Disp_StrAt((u8*)"mA");
			break;
		case I_WSETUP:
			if(run_stemp==0)//第一步
			{
				Disp_Str((u8 *)I_TEST_DISP[1]);
				LcdAddr.x=6;LcdAddr.y=1;
				Disp_StrAt((u8 *)"DC");
				LcdAddr.x=14;LcdAddr.y=1;
				Disp_StrAt((u8*)"M");
				Lcd_WriteData(OHM);
			}else//第二步
			{
				if(GetSystemMessage()==MSG_RAMP)//缓升
				{
					Disp_Str((u8 *)W_TEST_DISP[1]);
				}else//测试
				{
					Disp_Str((u8 *)W_TEST_DISP[2]);
				}
				LcdAddr.x=6;LcdAddr.y=1;
				if(SaveData.Setup.Item)
				
					Disp_StrAt((u8 *)"DC");
				else
					Disp_StrAt((u8 *)"AC");
				LcdAddr.x=14;LcdAddr.y=1;
				Disp_StrAt((u8*)"mA");
			}
			break;
		case W_ISETUP:
			if(run_stemp==0)//第一步
			{
				if(GetSystemMessage()==MSG_RAMP)//缓升
				{
					Disp_Str((u8 *)W_TEST_DISP[1]);
				}else//测试
				{
					Disp_Str((u8 *)W_TEST_DISP[2]);
				}
				LcdAddr.x=6;LcdAddr.y=1;
				if(SaveData.Setup.Item)
				
					Disp_StrAt((u8 *)"DC");
				else
					Disp_StrAt((u8 *)"AC");
				LcdAddr.x=14;LcdAddr.y=1;
				Disp_StrAt((u8*)"mA");
			
			}else//第二步
			{
				Disp_Str((u8 *)I_TEST_DISP[1]);
				LcdAddr.x=6;LcdAddr.y=1;
				Disp_StrAt((u8 *)"DC");
				LcdAddr.x=14;LcdAddr.y=1;
				Disp_StrAt((u8*)"M");
				Lcd_WriteData(OHM);
			
			}
			break;
		default:
			break;
	
	
	//Lcd_SetAddr();//设置坐标
	//Disp_Product_Model();//显示产品型号
	
	}
	LcdAddr.x=7;LcdAddr.y=0;
	Disp_StrAt((u8 *)"M");
	Disp_Char(SaveData.Group+1+'0');
	
	LcdAddr.x=15;LcdAddr.y=0;
	//Disp_StrAt((u8 *)"M");
	Disp_CharAt('s');
	
	LcdAddr.x=4;LcdAddr.y=1;
	//Disp_StrAt((u8 *)"M");
	Disp_StrAt((u8 *)"kV");
	
}
//==========================================================
//函数名称：InitGlobalValue
//函数功能：初始化全局变量
//入口参数：无
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 15:33
//备注说明：无
//==========================================================
void InitGlobalValue(void)
{
	u16 len;
	u8 * buf;
						 
	buf=(u8 *)&SaveData;//数据首地址
	len=sizeof(Save_TypeDef);
	while(len--)
	{
		*buf=0;//清空
		buf++;
	}
	F_Password=FALSE;//密码有效标志	
}
//==========================================================
//函数名称：Parameter_valuecomp
//函数功能：初始化值得比较
//入口参数：无
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 15:33
//备注说明：无
//==========================================================
void Parameter_valuecomp(void)
{
	u8 i,j;
	u16 *pt;
//	for(j=0;j<GROUP_MAX+1;j++)
//	{
		for(i=0;i<PARAMETER_MENU_MAX;i++)
		{	pt=(u16* )&SaveData.Setup + i;
			if(*pt>ParameterComp[i][0])
			*pt=ParameterComp[i][1];
		}
//	}


}
//==========================================================
//函数名称：Hex_Format
//函数功能：格式化整数值到DispBuf
//入口参数：整数，小数位数，数值位数，显示零
//出口参数：无
//创建日期：2014.12.15
//修改日期：2015.01.14 13:12
//备注说明：dot=0-XXXXX XXXX.X XXX.XX XX.XXX X.XXXX-Dot=4
//注意事项：最多5位数
//==========================================================
void Hex_Format(u16 dat , u8 Dot , u8 len , bool dispzero)
{
	u8 i,j;

	if(len>5)len=5;//最大长度5
	if(len==0)len=1;
	if(Dot>4)Dot=4;//最大小数点4
	if(Dot>len)Dot=len;

	for(i=0;i<sizeof(DispBuf);i++)	//清空缓冲区
		DispBuf[i]=' ';

	for(i=len;i>0;i--)	//数制转换
	{
		DispBuf[i-1] = dat%10 + '0';//转为ASCII
		dat/=10;
	}
	
	if(Dot)//有小数点
	{
		j=len;
		i=Dot;//取小数点位置
		while(i--)
		{
			DispBuf[j]=DispBuf[j-1];
			j--;
		}
		DispBuf[j]='.';//加入小数点
	}

	if(dispzero==FALSE)//不显示无效零
	{
		for(i=0;i<(len-1);i++)
		{
			if((DispBuf[i]=='0')&&(DispBuf[i+1]!='.'))
				DispBuf[i]=' ';
			else
				break;
		}
	}
	if(Dot)len++;
	for(i=len;i<sizeof(DispBuf);i++)//末尾补结束符'\0'
	{
		DispBuf[i]=0;
	}			
}
//==========================================================
//函数名称：Disp_Product_Model
//函数功能：显示产品型号
//入口参数：无
//出口参数：无
//创建日期：2015.10.27
//修改日期：2015.10.27 16:00
//备注说明：无
//==========================================================
void Disp_Product_Model(void)
{
	if(SaveData.pselect == 0)
	{
		Disp_Str((u8*)FactoryTab[0]);
	}else if(SaveData.pselect == 1){
		Disp_Str((u8*)FactoryTabS[0]);
	}
}

//==========================================================
//函数名称：Disp_Software_Version
//函数功能：显示软件版本
//入口参数：无
//出口参数：无
//创建日期：2015.10.27
//修改日期：2015.10.27 16:00
//备注说明：无
//==========================================================
void Disp_Software_Version(void)
{
//	Disp_Str("Ver:");
//	memset(DispBuf,'\0',sizeof(DispBuf));//清空
//	DispBuf[0]='0'+((SOFTWARE_VERSION&0xf0)>>4);
//	DispBuf[1]='.';
//	DispBuf[2]='0'+((SOFTWARE_VERSION&0x0f));
//	Disp_Str(DispBuf);
	if(SaveData.pselect == 0)
	{
		Disp_Str((u8*)FactoryTab[1]);
	}else if(SaveData.pselect == 1){
		Disp_Str((u8*)FactoryTabS[1]);
	}
	
}

//==========================================================
//函数名称：Disp_Compile_Date
//函数功能：显示编译日期
//入口参数：无
//出口参数：无
//创建日期：2015.10.27
//修改日期：2015.10.27 16:00
//备注说明：无
//==========================================================
void Disp_Compile_Date(void)
{
//	Disp_Str("Comp:");
//	Disp_Str(__DATE__ );//显示编译日期-Mmm dd yyyy
	Disp_Str(__DATE__);//显示编译日期-mm/dd/yy
}

//==========================================================
//函数名称：Disp_PowerOn_Menu
//函数功能：显示开机界面
//入口参数：无
//出口参数：无
//创建日期：2015.10.26
//修改日期：2015.10.26 15:00
//备注说明：无
//==========================================================
void Disp_PowerOn_Menu(void)
{
	//第一行
	LcdAddr.x=0;LcdAddr.y=0;
	Lcd_SetAddr();//设置坐标
	Disp_Product_Model();//显示产品型号
	
	//第二行
	LcdAddr.x=0;LcdAddr.y=1;
	Lcd_SetAddr();//设置坐标
	Disp_Software_Version();//显示软件版本
	
//	LcdAddr.x=11;LcdAddr.y=1;
//	Lcd_SetAddr();//设置坐标
//	Disp_Compile_Date();//显示编译日期
}
//==========================================================
//函数名称：Number_Setup
//函数功能：数值框设置处理
//入口参数：NumBox_TypeDef
//出口参数：键值
//创建日期：2015.01.07
//修改日期：2015.08.19 13:53
//备注说明：无
//==========================================================
//u8 Number_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;
//	u8 count;//步进计数器
//	u8 current;//当前设置位
//	bool blink;//显示闪烁标志
//	LcdAddr_TypeDef addr;//显示地址备份

////	//上限、下限、小数点检查
////	if(pt->Num > NumBox.Max)
////		pt->Num=NumBox.Max;
////	if(pt->Num < NumBox.Min)
////		pt->Num=NumBox.Min;
////	if(pt->Dot != NumBox.Dot)
////		pt->Dot=NumBox.Dot;

//	addr.x=LcdAddr.x;//显示地址备份
//	addr.y=LcdAddr.y;
////	SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期
//	
//	count=0;//步进计数器
//	blink=TRUE;//显示闪烁标志
//	if(pt->Dot==0)
//		current=3;//当前设置位
//	else
//		current=4;//当前设置位

//	while(1)
//	{
//		LcdAddr.x=addr.x;//显示地址
//		LcdAddr.y=addr.y;
//		Hex_Format(pt->Num,pt->Dot,4,TRUE);//数值格式化，4位数值

////		if( GetSoftTimerOut(DISP_SOFTTIMER) )//等待延时结束
////		{
////			SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期
////			blink=!blink;
////		}
//		if(blink)//等待延时结束
////		{
////			len=DispBuf[current];//备份
////			DispBuf[current]=CURSORCHAR;
////			Disp_Str(DispBuf,1);//显示菜单值
////			DispBuf[current]=len;//恢复
//////			if(pt->Dot==0)
//////				len=4;//总位数
//////			else
//////				len=5;//总位数
//////			while(len--)
//////				Disp_Str(" ",0);
////		}
////		else
//		{
//			Disp_Str(DispBuf,1);//显示菜单值
//		}

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
////				count=0;//步进计数器
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//小数点固定
////					current++;
////				if(NumBox.Dot!=0)//有小数点
////					current%=5;//最长5位
////				else
////					current%=4;//最长4位
////				return(KEY_SET);
//				break;

//			case KEY_DOWN:		//下键
//				blink=TRUE;//显示闪烁标志
//				count=0;//步进计数器
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//响两声
//				}
//				break;

//			case L_KEY_DOWN:	//长按下键
//				blink=TRUE;//显示闪烁标志
//				count++;//步进计数器
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				if(count>28)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>19)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//步进计数器
//				{
//					if(len>0)len--;
//				}
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//响两声
//				}
//				break;

//			case KEY_UP:	//上键
//				blink=TRUE;//显示闪烁标志
//				count=0;//步进计数器
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
//					pt->Num=pt->Min;
////					Beep_Two();//响两声
//				}
//				break;

//			case L_KEY_UP:	//长按上键
//				blink=TRUE;//显示闪烁标志
//				count++;//步进计数器
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				if(count>28)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>19)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//步进计数器
//				{
//					if(len>0)len--;
//				}
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
//					pt->Num=pt->Min;
////					Beep_Two();//响两声
//				}
//				break;

//			case KEY_LEFT:		//左键
////			case L_KEY_LEFT:	//长按左键
////				count=0;//步进计数器
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//小数点固定
////					current++;
////				if(NumBox.Dot!=0)//有小数点
////					current%=5;//最长5位
////				else
////					current%=4;//最长4位
//				return(KEY_LEFT);
//				break;

//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
////				count=0;//步进计数器
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//小数点固定
////					current++;
////				if(NumBox.Dot!=0)//有小数点
////					current%=5;//最长5位
////				else
////					current%=4;//最长4位
//				return(KEY_RIGHT);
//				break;

//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				return(KEY_ENTER);
//				break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				return(KEY_START);
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				return(KEY_RESET);
//				break;

//			default:
//				if(Keyboard.continuance!=TRUE) //持续按键
//					count=0;//步进计数器
//				break;
//		}
//	}
//}

//==========================================================
//函数名称：ListBox_Setup
//函数功能：列表框设置
//入口参数：无
//出口参数：键值
//创建日期：2015.01.08
//修改日期：2015.08.19 13:48
//备注说明：列表项标题长度固定为8个字符
//==========================================================
//u8 ListBox_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;//标题栏字符长度
//	bool blink=TRUE;//闪烁标志
//	LcdAddr_TypeDef addr;

//	len=strlen(pt->Title);//标题栏字符长度
//	addr.x=LcdAddr.x;//显示地址备份
//	addr.y=LcdAddr.y;
////	SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期
//	
//	while(1)
//	{
//		LcdAddr.x=addr.x;//显示地址
//		LcdAddr.y=addr.y;
////		if( GetSoftTimerOut(DISP_SOFTTIMER) )//等待延时结束
////		{
////			SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期
////			blink=!blink;
////		}
//		if(blink)
////		{
////			key=len;//列表项标题长度
////			while(key--)
////				Disp_Str(" ",0);//显示空格;
////		}
////		else
//			Disp_Str(pt->Title+(len+1)*pt->Num,1);//显示菜单值

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
//				return(KEY_SET);
//				break;

//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				blink=TRUE;
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				if(pt->Num>pt->Min)
//					pt->Num--;
//				else
//				{
//					pt->Num=pt->Max;
////					Beep_Two();//响两声
//				}
//				break;

//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				blink=TRUE;
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//设置闪烁延时周期(1000/3=333mS)
//				pt->Num++;
//				if(pt->Num>pt->Max)
//				{
//					pt->Num=pt->Min;
////					Beep_Two();//响两声
//				}
//				break;

//			case KEY_LEFT:		//左键
////			case L_KEY_LEFT:	//长按左键
//				return(KEY_LEFT);
////				break;

//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				return(KEY_RIGHT);
//				break;

//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				return(KEY_ENTER);
//				break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				return(KEY_START);
//				break;

//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				return(KEY_RESET);
//				break;

//			default:
//				break;
//		}
//	}
//}

//==========================================================
//函数名称：Disp_Frame
//函数功能：显示界面框架
//入口参数：无
//出口参数：无
//创建日期：2014.12.26
//修改日期：2015.08.18 16:30
//备注说明：整屏更新
//==========================================================
//void Disp_Frame( void )
//{
//	Lcd_Draw_Line(9,0,LCD_ADDR_Y_MAX);//竖线,高度为LCD_ADDR_Y_MAX
//	Lcd_Draw_Line(0,0,LCD_ADDR_X_MAX);//横线,长度为LCD_ADDR_X_MAX
//	Lcd_Draw_Line(0,32*1,9);//横线
//	Lcd_Draw_Line(0,32*2,9);//横线
//	Lcd_Draw_Line(0,32*3,9);//横线
//	Lcd_Draw_Line(0,127,LCD_ADDR_X_MAX);//横线
//}

//==========================================================
//函数名称：Disp_Boot_Number
//函数功能：显示开机次数
//入口参数：无
//出口参数：无
//创建日期：2014.11.13
//修改日期：2014.11.13 12:42
//备注说明：无
//==========================================================
//void Disp_Boot_Number(void)
//{
//	Disp_Str("开机次数: ",0);
//	Hex_Format(SaveData.Factory.BootNum,0,4,TRUE);//数值格式化
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//函数名称：Disp_Software_Version
//函数功能：显示软件版本
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.01.09 15:13
//备注说明：无
//==========================================================
//void Disp_Software_Version(void)
//{
//	Disp_Str("软件版本: ",0);
//	memset(DispBuf,'\0',sizeof(DispBuf));//清空
//	DispBuf[0]='0'+((SOFTWARE_VERSION&0xf0)>>4);
//	DispBuf[1]='0'+((SOFTWARE_VERSION&0x0f));
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//函数名称：Disp_Hardware_Version
//函数功能：显示硬件版本
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.01.09 15:13
//备注说明：无
//==========================================================
//void Disp_Hardware_Version(void)
//{
//	Disp_Str("硬件版本: ",0);
//	memset(DispBuf,'\0',sizeof(DispBuf));//清空
//	DispBuf[0]='0'+((HARDWARE_VERSION&0xf0)>>4);
//	DispBuf[1]='0'+((HARDWARE_VERSION&0x0f));
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//函数名称：Disp_Compile_Date
//函数功能：显示编译日期
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.01.09 15:13
//备注说明：无
//==========================================================
//void Disp_Compile_Date(void)
//{
//	Disp_Str("编译日期: ",0);
////	Disp_Str(__DATE__ ,0);//显示编译日期-Mmm dd yyyy
//	Disp_Str(__DATE2__,0);//显示编译日期-mm/dd/yy
//}

//==========================================================
//函数名称：Disp_Product_Model
//函数功能：显示产品型号
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.01.09 15:13
//备注说明：无
//==========================================================
//void Disp_Product_Model(void)
//{
//	Disp_Str("YD9860B 综合安规",0);
//}

//==========================================================
//函数名称：Disp_Company_Name
//函数功能：显示公司名称
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.01.09 15:13
//备注说明：无
//==========================================================
//void Disp_Company_Name(void)
//{
//	Disp_Str("常州市扬子电子有限公司",0);//厂商名称
//}
//==========================================================
//函数名称：Disp_Company_Telephone
//函数功能：显示厂商电话
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.09.06 10:07
//备注说明：无
//==========================================================
//void Disp_Company_Telephone(void)
//{
//	Disp_Str("电话: ",0);
//	Disp_Str("0519-88226706 88226707",0);//电话
//}

//==========================================================
//函数名称：Disp_Company_Http
//函数功能：显示厂商主页
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.09.06 10:07
//备注说明：无
//==========================================================
//void Disp_Company_Http(void)
//{
//	Disp_Str("主页: ",0);
//	Disp_Str("www.cz-yangzi.com",0);//主页
//}

//==========================================================
//函数名称：Disp_Chip_ID
//函数功能：显示芯片ID号
//入口参数：无
//出口参数：无
//创建日期：2014.11.13
//修改日期：2014.11.13 13:31
//备注说明：无
//==========================================================
//STC12系列CPU内部ID号首地址定义(F1-F7为ID号)
#define MCU_ID_ADDR (0xF1)
//==========================================================
//void Disp_Chip_ID(void)
//{
//	u8 i;
//	u8 dat;
//	u8 idata *addr;

//	Disp_Str("软件编号: ",0);
////	memset(DispBuf,'\0',sizeof(DispBuf));//清空
//	addr=MCU_ID_ADDR;//ID号首地址
//	i=7;
//	while(i--)
//	{
//		dat=(*addr&0xf0)>>4;//ID号高4位
//		DispBuf[0]=(dat>9)?(dat-0x0a+'A'):(dat+'0');
//		dat=(*addr&0x0f);//ID号低4位
//		DispBuf[1]=(dat>9)?(dat-0x0a+'A'):(dat+'0');
//		if(i!=0)
//			DispBuf[2]='-';
//		else
//			DispBuf[2]=0;
//		DispBuf[3]=0;
//		Disp_Str(DispBuf,0);//显示
//		addr++;
//	}
//}
//==========================================================
////无序列号的显示固定值
//void Disp_Chip_ID(void)
//{
//	u8 i=7;
//	u8 dat=0;
//
//	Disp_Str("软件编号: ",0);
//	while(i--)
//	{
//		DispBuf[0]=(dat>9)?(dat-0x0a+'A'):(dat+'0');
//		DispBuf[1]=DispBuf[0];
//		if(i!=0)
//			DispBuf[2]='-';
//		else
//			DispBuf[2]=0;
//		DispBuf[3]=0;
//		Disp_Str(DispBuf,0);
//	}
//}

//==========================================================
//函数名称：Disp_Product_ID
//函数功能：显示出厂编号
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.08.19 10:03
//备注说明：无
//==========================================================
//void Disp_Product_ID(void)
//{
//	Hex_Format(SaveData.Factory.ProductId,0,4,1);//数据格式化到DispBuf
//	Disp_Str("出厂编号: ",0);
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//函数名称：Disp_PowerOn_Menu
//函数功能：显示开机界面
//入口参数：无
//出口参数：无
//创建日期：2014.12.26
//修改日期：2015.08.18 09:38
//备注说明：无
//==========================================================
//void Disp_PowerOn_Menu(void)
//{
////	Disp_Kjjm();//显示开机界面(整屏图片显示)

//	LcdAddr.x=7;LcdAddr.y=15;
//	Disp_Product_Model();//显示产品型号

//	LcdAddr.x=9;LcdAddr.y=55;
//	Disp_Software_Version();//显示软件版本
//	
//	LcdAddr.x=4;LcdAddr.y=95;
//	Disp_Company_Name();//显示厂商名称
//}

//==========================================================
//函数名称：Disp_Group
//函数功能：显示组别
//入口参数：无
//出口参数：无
//创建日期：2015.01.05
//修改日期：2015.01.05 13:18
//备注说明：无
//==========================================================
//void Disp_Group(u8 highlight)
//{
////	Hex_Format(SaveData.Group+1,0,1,0);//数据格式化到DispBuf
//	Hex_Format(SaveData.Group+1,0,2,1);//数据格式化到DispBuf
//	Disp_Str(DispBuf,highlight);//显示
//	Disp_Str("组",highlight);//显示
//}

//==========================================================
//函数名称：Disp_Parameter_Value
//函数功能：显示设置值
//入口参数：step:第几步骤；index:第几项参数；highlight:非零高亮显示
//出口参数：无
//创建日期：2015.01.05
//修改日期：2015.09.06 09:14
//备注说明：数值位数+小数点+单位的长度固定为7个字符
//==========================================================
//void Disp_Parameter_Value(u8 step ,u8 index, u8 highlight)
//{
//	u8 item;
//	
//	step%=STEP_MAX;//最大步骤
//	index%=PARAMETER_MENU_MAX;//最大参数项
//	item=SaveData.Setup[step].Item;//项目
//		
//	switch(index)
//	{
//		case PARAMETER_MENU_ITEM://项目
//			Disp_Str(&ItemTab[item],highlight);//显示项目
//			break;

//		case PARAMETER_MENU_OUTPUT://输出
//			Hex_Format(SaveData.Setup[step].Output,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//					Disp_Str("V ",0);//显示V
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("A ",0);//显示A
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[step][item]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;
//		
//		case PARAMETER_MENU_LIMITH://上限
//			Hex_Format(SaveData.Setup[step].High,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//显示
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;

//		case PARAMETER_MENU_LIMITL://下限
//			Hex_Format(SaveData.Setup[step].Low,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//显示
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;

//		case PARAMETER_MENU_TESTTIME:
//			Hex_Format(SaveData.Setup[step].TestTime,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//				case ITEM_GND:
//					Disp_Str("s ",0);//显示
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;
//		
//		case PARAMETER_MENU_RAMPDELAY:
//			Hex_Format(SaveData.Setup[step].RampDelay,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//				case ITEM_GND:
//					Disp_Str("s ",0);//显示
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;

//		case PARAMETER_MENU_ZERO:
//			Hex_Format(SaveData.Setup[step].Zero,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			switch(item)//按项目显示单位
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//显示
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//显示
//					Disp_Char(OHM,0);//显示Ω
//					break;
//				
//				default:
//					Disp_Str("  ",0);//显示
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//无小数点补1位空格
//				Disp_Str(" ",0);//显示
//			break;

//		case PARAMETER_MENU_ARC:
//			Hex_Format(SaveData.Setup[step].Arc,ParameterDotTab[item][index],4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,highlight);//显示
//			Disp_Str("   ",0);//显示3个空格，无小数点1，无单位2
//			break;

//		default:
//			break;
//	}
//}

//==========================================================
//函数名称：Disp_SysMessage
//函数功能：显示系统信息
//入口参数：无
//出口参数：无
//创建日期：2014.10.15
//修改日期：2014.10.15 15:17
//备注说明：无
//==========================================================
void Disp_SysMessage(void)
{
//	if(SaveData.Setup[SaveData.Group].Group_Item>3)
//		SaveData.Setup[SaveData.Group].Group_Item=0;
//	Disp_StrAt((u8 *)GROUP_DISP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//显示系统信息
	//switch()
	Disp_StrAt((u8 *)MsgTab[GetSystemMessage()]);//显示系统信息
}

//==========================================================
//函数名称：Disp_Idle_Menu
//函数功能：显示待测菜单
//入口参数：无
//出口参数：无
//创建日期：2015.10.26
//修改日期：2015.10.29 10:27
//备注说明：无
//==========================================================
void Disp_Idle_Menu(void)
{
	//第一行
	if(SaveData.Setup.Group_Item>3)
		SaveData.Setup.Group_Item=0;
	LcdAddr.x=MSG_ADDR_X;LcdAddr.y=0;
	Lcd_SetAddr();//设置坐标
	Disp_StrAt((u8 *)GROUP_ITEM[SaveData.Setup.Group_Item]);//显示系统信息
	//Disp_SysMessage();//显示系统信息
	LcdAddr.x=GROUP_ADDR_X;LcdAddr.y=0;
	Hex_Format(SaveData.Group+1,0,1,TRUE);//显示当前组别
	Disp_StrAt((u8*)"M");
	Disp_Str(DispBuf);
//	if(SaveData.Group==0)
//		SaveData.Group=1;
	if(SaveData.Setup.Group_Item>1)
		Disp_Str((u8*)"_");
	else
		Disp_Str((u8*)" ");
	LcdAddr.x=TIME_ADDR_X;
	if(SaveData.Setup.Group_Item==3||SaveData.Setup.Group_Item==1)//绝缘电阻
		Hex_Format((u16)SaveData.Setup.I_Delay,1,4,FALSE);//显示测试时间
	else
		Hex_Format((u16)SaveData.Setup.TestTime,1,4,FALSE);//显示测试时间
	Disp_StrAt(DispBuf);
	Disp_Str((u8*)"s");

	//第二行
	LcdAddr.x=V_ADDR_X;LcdAddr.y=1;
	if(SaveData.Setup.Item==0)
	{
		if(SaveData.Setup.Output>600)
			SaveData.Setup.Output=600;
		
	
	}
	if(/*SaveData.Setup.Group_Item==3||*/SaveData.Setup.Group_Item==1)//绝缘电阻
	{
		Hex_Format((u16)SaveData.Setup.I_Volt,2,3,FALSE);//显示测试时间
		SaveData.Setup.Item=1;
		
	}else if(SaveData.Setup.Group_Item==3){
		Hex_Format((u16)SaveData.Setup.I_Volt,2,3,FALSE);//显示测试时间
	}
	else{
		Hex_Format((u16)SaveData.Setup.Output,2,3,FALSE);//显示测试时间
	}
	Disp_StrAt(DispBuf);
	Disp_Str((u8*)"kV");
	
	memset(sendbuff,0,20);
	memcpy(sendbuff,DispBuf,4);
	strcat(sendbuff,"kV;");
	if(SaveData.Setup.Item==0 && SaveData.Setup.Group_Item != I_WSETUP)//AC 注意  设置的时候 绝缘电阻要固定为DC
		Disp_Str((u8*)"AC");
	else
		Disp_Str((u8*)"DC");
	
	
	if(SaveData.Setup.Group_Item==3||SaveData.Setup.Group_Item==1)//绝缘电阻
	{
		LcdAddr.x=RES_ADDR_X+1;
		Hex_Format((u16)SaveData.Setup.I_High,0,4,FALSE);//显示上限电阻
		Disp_StrAt(DispBuf);
		Disp_Str((u8*)"M");
		Lcd_WriteData(OHM);
		strcat(sendbuff,(char*)DispBuf);
		strcat(sendbuff,"MΩ;");
		
	}
	else
	{
		LcdAddr.x=RES_ADDR_X;
		Hex_Format((u16)SaveData.Setup.High,2,4,FALSE);//显示测试时间
		Disp_StrAt(DispBuf);
		Disp_Str((u8*)"mA");
		strcat(sendbuff,(char*)DispBuf);
		strcat(sendbuff,"mA;");
	}
		

}
//==========================================================
//函数名称：Check_Parameter_Limit
//函数功能：参数值检查
//入口参数：无
//出口参数：无
//创建日期：2015.10.28 
//修改日期：2015.10.28 13:50
//备注说明：上限、下限检查,	L<=x<=H
//==========================================================
//void Check_Parameter_Limit(void)
//{
//	u8 i;
//	u8 *pt;

//	pt=(u8* )&SaveData.Parameter;
//	for(i=0;i<PARAMETER_MENU_MAX;i++)//共5项
//	{
//		if(*pt>ParameterLimit[i][0])//Max
//			*pt= ParameterLimit[i][0];//Max
//		if(*pt<ParameterLimit[i][1])//Min
//			*pt=ParameterLimit[i][1];//Min
//		pt++;
//	}
//}
//==========================================================
//函数名称：Range_Control
//函数功能：量程控制
//入口参数：u8 dat
//出口参数：无
//创建日期：2014.09.25
//修改日期：2015.09.04 15:35
//备注说明：量程(0-4) 100 1k 10k 100k 1M
//==========================================================
void Range_Control(u8 dat)
{

	u8 temp;
	temp=IC42_574buff;
	temp&=HW_HW_PGA_MASK;
	switch(dat)
	{
		case 3:
			temp|=HW_PGA_1K;
		break;
		case 2:
			temp|=HW_PGA_10K;
		break;
		case 1:
			temp|=HW_PGA_100K;
		break;
		case 0:
			//temp|=HW_PGA_103K;
		break;
//		case 4:
//			temp|=HW_PGA_104K;
//		break;
//		case 5:
//			//temp|=HW_PGA_105K;
//			//控制内部放大8倍
//		break;
//		case 6:
//			//控制内部放大64倍
//		break;
//		case 7:
//			//控制内部放大128倍
//		break;
		default:
			temp|=HW_PGA_1K;
		break;
			
	
	}
	IC42_574buff=temp;
	PDout(4)=0;
	GPIO_WriteHigh(GPIOD,IC42_574buff);
	PDout(4)=1;
	delay_ms(100);

}


//==========================================================
//函数名称：Disp_Setup_Menu
//函数功能：显示设置菜单
//入口参数：index:第几项
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 13:25
//备注说明：无
//==========================================================
void Disp_Setup_Menu(u8 index)
{
	//第一行
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8*)&SetupMenu[index%SETUP_MENU_MAX][0]);
	
	//第二行
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8*)EnterTab);//显示确认提示
}
//==========================================================
//函数名称：Disp_Parameter_Value
//函数功能：显示参数
//入口参数：index:第几项参数
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 11:25
//备注说明：无
//==========================================================
//void Disp_Parameter_Value(u8 index)
//{
//	index%=PARAMETER_MENU_MAX;//最大系统项
//	
//	switch(index)
//	{
//		case PARAMETER_MENU_RANGE://量程模式
////			if(SaveData.Parameter.Range>7)
////				SaveData.Parameter.Range=0;
//			Disp_Str((u8*)&RangeTab[SaveData.Parameter.Range]);
//			break;

//		case PARAMETER_MENU_BEEP://讯响模式
////			if(SaveData.Parameter.Beep>3)
////				SaveData.Parameter.Beep=0;
//			Disp_Str((u8*)&BeepTab[SaveData.Parameter.Beep]);
//			break;

//		case PARAMETER_MENU_CLEAR://清零开关
////			if(SaveData.Parameter.ClrOn>2)
////				SaveData.Parameter.ClrOn=0;
//			Disp_Str((u8 *)&SwitchTab[SaveData.Parameter.ClrOn]);
//			break;

//		case PARAMETER_MENU_TRIG://外部触发开关
////			if(SaveData.Parameter.ExTrig>2)
////				SaveData.Parameter.ExTrig=0;
//			Disp_Str((u8*)&SwitchTab[SaveData.Parameter.ExTrig]);
//			break;

//		case PARAMETER_MENU_UART://串口开关
////			if(SaveData.Parameter.UartOn>2)
////				SaveData.Parameter.UartOn=0;
//			Disp_Str((u8*)&SwitchTab[SaveData.Parameter.UartOn]);
//			break;

//		default:
//			break;
//	}
//}
//==========================================================
//函数名称：ListBox_Setup
//函数功能：列表框设置
//入口参数：无
//出口参数：键值
//创建日期：2015.10.28
//修改日期：2015.10.28 09:50
//备注说明：标题栏字符长度,TITLE_LEN_MAX=8
//==========================================================
u8 ListBox_Setup(NumBox_TypeDef * pt)
{
	u8 key;
	u8 len;
	bool blink;//闪烁标志
	LcdAddr_TypeDef addr;

	blink=TRUE;//闪烁标志

	addr.x=LcdAddr.x;//显示地址备份
	addr.y=LcdAddr.y;

	len=strlen((const char *)(pt->Title));//标题栏字符长度
	len++;//结束符
	if(len>TITLE_LEN_MAX)len=TITLE_LEN_MAX;//最大长度限定
	
	while(1)
	{
		if(blink)
		{
			LcdAddr.x=addr.x;//显示地址
			LcdAddr.y=addr.y;
			Disp_StrAt((u8*)(pt->Title+len*pt->Num));//显示菜单值
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//设置键
			case L_KEY_SET:	//长按设置键
				return(KEY_SET);
				//break;

			case KEY_DOWN:		//下键
			case L_KEY_DOWN:	//长按下键
				blink=TRUE;
				if(pt->Num>pt->Min)
					pt->Num--;
				else
				{
					pt->Num=pt->Min;
					Beep_Two();//响两声
				}
				break;

			case KEY_UP:	//上键
			case L_KEY_UP:	//长按上键
				blink=TRUE;
				pt->Num++;
				if(pt->Num>pt->Max)
				{
					pt->Num=pt->Max;
					Beep_Two();//响两声
				}
				break;

			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				return(KEY_ENTER);
				//break;

			case KEY_START:		//启动键
			case L_KEY_START:	//长按启动键
				//return(KEY_START);
				//break;

			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				return(KEY_RESET);
				//break;

			default:
				break;
		}
	}
}
//==========================================================
//函数名称：Disp_Parameter_Menu
//函数功能：显示参数界面
//入口参数：无
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 13:20
//备注说明：无
//==========================================================
void Disp_Parameter_Menu(u8 index)
{
	//第一行
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8*)ParameterTab[index]);//显示参数菜单
//	Disp_Parameter_Value(index);//显示参数值
	
	//第二行
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8*)SelectTab);//显示选择提示
}

//==========================================================
//函数名称：Parameter_Setup
//函数功能：参数菜单设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 11:49
//备注说明：无
//==========================================================
//void Parameter_Setup(void)
//{
//	u8 *pt;
//	u8 key;
//	u8 index;
//	bool f_disp;

//	index=0;//第一项
//	f_disp=TRUE;//显示

//	while(GetSystemStatus()==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//显示更新
//		{
//			f_disp=FALSE;
//			Disp_Parameter_Menu(index);//显示界面

//			//取设置值、上下限
//			pt=(u8* )&SaveData.Parameter + index;
//			NumBox.Num=*pt;
//			NumBox.Max=ParameterLimit[index][0];//Max
//			NumBox.Min=ParameterLimit[index][1];//Min
//			NumBox.Dot=0;//Dot
//		
//			//显示地址	  SaveData.Parameter.Range
//			LcdAddr.x=12;LcdAddr.y=0;
//	
//			switch(index)//数值设置处理
//			{
//				case PARAMETER_MENU_RANGE://量程模式
//					NumBox.Title=(u8*)RangeTab[0];
//					key=ListBox_Setup(&NumBox);//列表框设置
//					break;
//		
//				case PARAMETER_MENU_BEEP://讯响模式
//					NumBox.Title=(u8*)BeepTab[0];
//					key=ListBox_Setup(&NumBox);//列表框设置
//					break;
//		
//				case PARAMETER_MENU_CLEAR://清零开关
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//列表框设置
//					break;
//		
//				case PARAMETER_MENU_TRIG://外部触发开关
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//列表框设置
//					break;
//	
//				case PARAMETER_MENU_UART://串口开关
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//列表框设置
//					if(SaveData.Parameter.UartOn==1)
//						;//Start_Uart();//串口开启
//					else
//						;//Stop_Uart();//串口关闭
//					break;
//	
//				default:
//					break;
//			}
//	
//			*pt=NumBox.Num;//更新设置值
////			Check_Parameter_Limit();//值检查
//	
//			//按键处理
//			switch(key)
//			{
//				case KEY_SET:	//设置键
//				case L_KEY_SET:	//长按设置键
//					f_disp=TRUE;//显示
//					index++;
//					if(index>=PARAMETER_MENU_MAX)
//						index=0;
//					break;

//				case KEY_UP:	//上键
//				case L_KEY_UP:	//长按上键
//					break;
//	
//				case KEY_DOWN:		//下键
//				case L_KEY_DOWN:	//长按下键
//					break;
//	
//				case KEY_ENTER:		//确认键
////				case L_KEY_ENTER:	//长按确认键
//					//SaveParameter();//保存参数
//					SetSystemStatus(SYS_STATUS_SETUP);//待机状态
//					if(SaveData.Parameter.Range)
//					Range_Control(SaveData.Parameter.Range);
//					Store_set_flash();
//					break;
//		
//				case KEY_START:		//启动键
//				case L_KEY_START:	//长按启动键
//					SetSystemStatus(SYS_STATUS_TEST);//启动测试状态
//					break;
//		
//				case KEY_RESET:		//复位键
//				case L_KEY_RESET:	//长按复位键
//					SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//					break;
//				
//				default:
//					break;
//			}
//		}
//	}
//}
//==========================================================
//函数名称：Disp_System_Value
//函数功能：显示系统值
//入口参数：index:第几项参数
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 14:20
//备注说明：无
//==========================================================
void Disp_System_Value(u8 index)
{
	index%=SYSTEM_MENU_MAX;//最大项
	switch(index)
	{
		
		case SYSTEM_MENU_VOUT ://输出电压设置
//			Hex_Format(SaveData.System.Vol_Out,0,4,TRUE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);//显示
			Disp_Char(' ');
			Disp_Char('V');
			Disp_Char(' ');
			break;
		case SYSTEM_MENU_Ttime://测试时间设置
//			Hex_Format(SaveData.System.Set_Time,1,4,TRUE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);//显示
			Disp_Char(' ');
			Disp_Char('s');
			break;
		case SYSTEM_MENU_RH://上限
//			Hex_Format(SaveData.System.Res_Hi,0,4,TRUE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);//显示
			Disp_Char(' ');
			Disp_Char('M');
			Disp_Char(OHM);
			break;

		case SYSTEM_MENU_RL://下限
//			Hex_Format(SaveData.System.Res_Lo,0,4,TRUE);//数据格式化到DispBuf
			Disp_StrAt(DispBuf);//显示
			Disp_Char(' ');
			Disp_Char('M');
			Disp_Char(OHM);
			break;
	
	

		default:
			break;
	}
}

//==========================================================
//函数名称：Disp_System_Menu
//函数功能：显示系统界面
//入口参数：index:第几项参数
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 14:23
//备注说明：无
//==========================================================
void Disp_System_Menu(u8 index)
{
	//第一行
	LcdAddr.x=0;LcdAddr.y=0;
	switch(index)
	{
		case 0:
	
		Disp_StrAt((u8*)"Memory=         ");//显示菜单
		//Hex_Format(SaveData.Group,0,1,FALSE);
		//LcdAddr.x=10;LcdAddr.y=0;
		//Disp_StrAt(DispBuf);
		
		LcdAddr.x=0;LcdAddr.y=1;
		Disp_StrAt((u8*)"Range:1-9      ");//显示数值范围
		break;
		case 1:
	 
		Disp_StrAt((u8*)"Test  =        ");//显示菜单
		//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
		//LcdAddr.x=10;LcdAddr.y=0;
		//Disp_StrAt((u8*)GROUP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//显示项目
		
		LcdAddr.x=0;LcdAddr.y=1;
		Disp_StrAt((u8*)I_Sel_Tab[0]);//显示数值范围
		break;
		case 2:
	
		switch(SaveData.Setup.Group_Item)//选择测试项目
		{
			case I_SETUP:
				Disp_StrAt((u8*)I_SET[index-2]);//显示菜单
				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
				//LcdAddr.x=10;LcdAddr.y=0;
				//Disp_StrAt((u8*)GROUP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//显示项目
				
				LcdAddr.x=0;LcdAddr.y=1;
				Disp_StrAt((u8*)I_Sel_Tab[index-1]);//显示数值范围
				
				break;
			case W_SETUP://分ACDC
//				Disp_StrAt((u8*)W_SET[index-2]);//显示菜单
//				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
//				//LcdAddr.x=10;LcdAddr.y=0;
//				//Disp_StrAt((u8*)AC_DC_SET[SaveData.Setup[SaveData.Group].Item]);//显示项目
//				
//				LcdAddr.x=0;LcdAddr.y=1;
//				Disp_StrAt((u8*)W_Sel_Tab[index-2]);//显示数值范围
//				break;
			case I_WSETUP://分ACDC
				
				//break;
			case W_ISETUP://分ACDC
				LcdAddr.x=0;LcdAddr.y=0;
				Disp_StrAt((u8*)W_SET[index-2]);//显示菜单
				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
				//LcdAddr.x=10;LcdAddr.y=0;
				//Disp_StrAt((u8*)AC_DC_SET[SaveData.Setup[SaveData.Group].Item]);//显示项目
				
				LcdAddr.x=0;LcdAddr.y=1;
				if(SaveData.Setup.Item==0)
					Disp_StrAt((u8*)W_Sel_Tab[index-2]);//显示数值范围
				else
					Disp_StrAt((u8*)I_WDC_Sel_Tab[index-2]);//显示数值范围
				break;
			default:
				
				break;

		}
		break;
	case 3://W_SET
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		switch(SaveData.Setup.Group_Item)//选择测试项目
		{
			case I_SETUP:
				Disp_StrAt((u8*)I_SET[index-2]);//显示菜单
				
				
				LcdAddr.x=0;LcdAddr.y=1;
				Disp_StrAt((u8*)I_Sel_Tab[index-1]);//显示数值范围
				
				break;
			case W_SETUP://分ACDC
				
				
			case I_WSETUP://分ACDC
				
				
			case W_ISETUP://分ACDC
				Disp_StrAt((u8*)I_W_SET[index-2]);//显示菜单
				LcdAddr.x=0;LcdAddr.y=1;
				if(SaveData.Setup.Item==0)
					Disp_StrAt((u8*)W_Sel_Tab[index-1]);//显示数值范围
				else
					Disp_StrAt((u8*)I_WDC_Sel_Tab[index-1]);//显示数值范围
				break;
				
			default:
				
				break;

		}//
		break;
		case 10:
		case 11:
		case 12:
		case 13:
			Disp_StrAt((u8*)I_W_SET[index-2]);//显示菜单
			if(index==12||index==11)
			{
				LcdAddr.x=14;LcdAddr.y=0;
				Disp_CharAt(OHM);
				//Disp_StrAt((u8*));//显示数值范围
			}
			LcdAddr.x=0;LcdAddr.y=1;
			Disp_StrAt((u8*)I_W_Sel_Tab[index-1]);//显示数值范围
			break;
				
	

	
	}
	
	
	
	
}
//==========================================================
//函数名称：Number_Setup
//函数功能：数值框设置处理
//入口参数：NumBox_TypeDef
//出口参数：键值
//创建日期：2015.10.28
//修改日期：2015.10.28 09:44
//备注说明：无
//==========================================================
u8 Number_Setup(NumBox_TypeDef * pt)
{
	u8 key;
	u8 len;
	u8 count;//步进计数器
	u8 current;//当前设置位
	bool blink;//显示闪烁标志
	LcdAddr_TypeDef addr;//显示地址备份

	blink=TRUE;//显示闪烁标志

	addr.x=LcdAddr.x;//显示地址备份
	addr.y=LcdAddr.y;

	count=0;//步进计数器
	if(pt->Dot==0)
		current=3;//当前设置位
	else
		current=4;//当前设置位

	while(1)
	{
		if(blink)//显示
		{
			LcdAddr.x=addr.x;//显示地址
			LcdAddr.y=addr.y;
			//if(in)
			Hex_Format(pt->Num,pt->Dot,pt->Len,FALSE);//数值格式化，4位数值
			Disp_StrAt(DispBuf);//显示菜单值
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//设置键
			case L_KEY_SET:	//长按设置键
				return(KEY_SET);
				//break;

			case KEY_DOWN:		//下键
				blink=TRUE;//显示闪烁标志
				count=0;//步进计数器
				if(current>(3-NumBox.Dot))//小数点位
					len=current-1;
				else
					len=current;
				if(pt->Num>=(POW_NUM[len]+pt->Min))
					pt->Num-=POW_NUM[len];
				else
				{
					if(pt->Min == 5 || pt->Min == 6)
					{
						if(pt->Min == 6)
						{
							if(pt->Num != 0)
							{
								pt->Num = 0;
							}else{
								Beep_Two();//响两声
							}
						}
						
						if(pt->Min == 5)
						{
							if(pt->Num != 0)
							{
								pt->Num = 0;
							}else{
								Beep_Two();//响两声
							}
						}
					}else{
						
					}
				}
				break;

			case L_KEY_DOWN:	//长按下键
				blink=TRUE;//显示闪烁标志
				count++;//步进计数器
				if(current>(3-NumBox.Dot))//小数点位
					len=current-1;
				else
					len=current;
				if(count>28)//步进计数器
				{
					if(len>0)len--;
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>19)//步进计数器
				{
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>10)//步进计数器
				{
					if(len>0)len--;
				}
				if(pt->Num>=(POW_NUM[len]+pt->Min))
					pt->Num-=POW_NUM[len];
				else
				{
					if(pt->Min == 6)
					{
						if(pt->Num != 0)
						{
							pt->Num = 0;
						}else{
							Beep_Two();//响两声
						}
					}
					
					if(pt->Min == 5)
					{
						if(pt->Num != 0)
						{
							pt->Num = 0;
						}else{
							Beep_Two();//响两声
						}
					}
				}
				break;

			case KEY_UP:	//上键
				blink=TRUE;//显示闪烁标志
				count=0;//步进计数器
				if(current>(3-NumBox.Dot))//小数点位
					len=current-1;
				else
					len=current;
				if(pt->Min == 6 || pt->Min == 5)
				{
					if(pt->Min == 6)
					{
						if(pt->Num == 0)
						{
							pt->Num = 6;
						}else{
							pt->Num+=POW_NUM[len];
						}
					}
					
					if(pt->Min == 5)
					{
						if(pt->Num == 0)
						{
							pt->Num = 5;
						}else{
							pt->Num+=POW_NUM[len];
						}
					}
				}else{
					pt->Num+=POW_NUM[len];
					if(pt->Num>pt->Max)
					{

						pt->Num=pt->Max;
						Beep_Two();//响两声
					}
				}
				break;

			case L_KEY_UP:	//长按上键
				blink=TRUE;//显示闪烁标志
				count++;//步进计数器
				if(current>(3-NumBox.Dot))//小数点位
					len=current-1;
				else
					len=current;
				if(count>28)//步进计数器
				{
					if(len>0)len--;
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>19)//步进计数器
				{
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>10)//步进计数器
				{
					if(len>0)len--;
				}
				if(pt->Min == 6 || pt->Min == 5)
				{
					if(pt->Min == 6)
					{
						if(pt->Num == 0)
						{
							pt->Num = 6;
						}else{
							pt->Num+=POW_NUM[len];
						}
					}
					
					if(pt->Min == 5)
					{
						if(pt->Num == 0)
						{
							pt->Num = 5;
						}else{
							pt->Num+=POW_NUM[len];
						}
					}
				}else{
					pt->Num+=POW_NUM[len];
					if(pt->Num>pt->Max)
					{

						pt->Num=pt->Max;
						Beep_Two();//响两声
					}
				}
				break;

			case KEY_ENTER:		//确认键
			case L_KEY_ENTER:	//长按确认键
				return(KEY_ENTER);
				//break;

			case KEY_START:		//启动键
			case L_KEY_START:	//长按启动键
//				return(KEY_START);
				break;
	
			case KEY_RESET:		//复位键
			case L_KEY_RESET:	//长按复位键
				return(KEY_RESET);
//				break;

			default:
				if(Keyboard.continuance!=TRUE) //持续按键
					count=0;//步进计数器
				break;
		}
	}
}

//==========================================================
//函数名称：Range_Changecomp
//函数功能：电阻测试换挡
//入口参数：无
//出口参数：无
//创建日期：2015.10.26 
//修改日期：2015.10.29 13:35
//备注说明：无
//==========================================================
void Range_Changecomp(void)
{
	
//	bool f_disp=FALSE;//显示标志
	bool f_upper=FALSE;//量程过压标志
	bool f_below=FALSE;//量程欠压标志
	bool f_switch=FALSE;//量程切换标志
	u8 i;
	//量程自动换挡处?
	if(Test_value.Test_I>RANGR_LIMIT_HIGH)//高于量程上限
	{
		f_upper=TRUE;//量程过压标志
		f_below=FALSE;//量程欠压标志
		for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
	}
	else if(Test_value.Test_I<RANGR_LIMIT_LOW)//低于量程下限
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
	//f_switch=TRUE;
	
		if((Range>0)&&(f_upper==TRUE))//量程非最高且低压
		{
			Range--;
			f_switch=TRUE;//量程切换标志
			for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
		}
		if((Range<RANGE_MAX)&&(f_below==TRUE))//量程非最低且过压
		{
			Range++;
			f_switch=TRUE;//量程切换标志
			for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
		}
	
	if(f_switch==TRUE)//量程切换标志
	{
		Range_Control(Range);//量程控制
		//Range_Control(2);
		
		delay_ms(50);//硬件延时
	}
}
//==========================================================
//函数名称：Get_FFT
//函数功能：计算测试值结果
//入口参数：无
//出口参数：无
//创建日期：2014.11.08 
//修改日期：2015.08.27 14:43
//备注说明：更新Voltage
//==========================================================
void Get_FFT(void)
{
	float dat=0;
	u8 i;
	ffit_data1++;	
	//fft_flag=Range;
	//增加判断  没有换挡的时候 ffit_data1不清零 Range
	if(((Test_value.Test_I>40000)||(Test_value.Test_I<2000))&&(Range!=RANGE_MAX))
		ffit_data1=0;
	//Float.Digit=Float.Digit/1000;
//	if(fft_flag>Float.Exponent)
//	{
//		Float.Digit*=10;
//	}
//	else if(fft_flag<Float.Exponent)
//	{
//		Float.Digit/=10;
//	}
	i_buff[count_ffit++]=Res_count.r;//Test_value.Test_I;
	
	if(count_ffit>=FIT_INUM)
	{
		count_ffit=0;
	}
	for(i=0;i<FIT_INUM;i++)
	{
	 	dat+=i_buff[i];
	
	}
	if(ffit_data1<FIT_INUM)
		;//Res.Real=Test_value.Test_I;
	//Test_value.Test_I=
	else
	{
		Res_count.r=dat/(FIT_INUM);
		ffit_data1=	FIT_INUM;

	}

	DispF(Res_count.r);
	Float.Digit=Float.Digit/1000;
//		ffit_data=0;
//		ffit_data1=0;
	//Res.Real=Current;
//	if(Voltage>AD_MAX)//最大AD值判别
//		Voltage=AD_MAX;
//
//	//校准处理
//	dat=Voltage*10;//放大10倍
//	dat*=Cal[0].Num;
//	dat/=Cal[0].NumAd;
//
//	//四舍五入
//	if(dat%10>4)dat+=10;
//	dat/=10;
//	//Voltage=(u16)dat;Res.Real
//	Voltage=Res.Real;
//	//最大AD值判别
//	if(Current>AD_MAX)//最大AD值判别
//		Current=AD_MAX;
//
//	//校准处理
//	dat=Current*10;//放大10倍	
//	dat*=Cal[Range+1].Num;
//	dat/=Cal[Range+1].NumAd;
//
//	//四舍五入
//	if(dat%10>4)dat+=10;
//	dat/=10;
//	Current=(u16)dat;
//	Current=Res.Imaginary;
}

void Test_Debug(void)
{
	vu32 temp;
//	temp=Current;
	//Current=temp*SaveData.Calibrate.IrCur[Range].Num/SaveData.Calibrate.IrCur[Range].NumAd;
	//Current=temp*Cal[Range].Num/Cal[Range].NumAd;
	//temp*=1000;
	
//	switch(Range)
//	{
//		case 0:
//			
//			temp=(temp*1000/1033);///1108;//10mR
//		break;
//		case 1:
//			  temp=(temp*1000/1101);///1146;//100mR
//		break;
//		case 2:
//			temp=(temp*1000/1231);///1115;//1R
//		break;
//		case 3:
//			temp=(temp*1000/889);///1118;//10R
//		break;
//		case 4:
//		break;
//		default:
//		break;	
//	}
//	if(SaveData.System.Vol_Out>100)
//		Res_count.v=Test_value.Test_v.Test_v*10;
//	else
//		Res_count.v=Test_value.Test_v.Test_v;
	if(Test_value.Test_I<10)
		Test_value.Test_I=10;
	Res_count.i=(u32)Test_value.Test_I;
	Res_count.rate=RANGE_RATE[Range];
//	Res_count.rate*=1000;
	Get_Res();
	

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
//void Read_Ad(void)
//{
//	
//	//AD7705_write_Reg(0x11);//写入通信寄存器，设置为写设置寄存器

////	AD7705_init(1);
//	Hex_Format(Test_value.Test_Time,1,4,TRUE);//显示时间
//	LcdAddr.x=TIM_ADDR_X;LcdAddr.y=0;
//	Disp_StrAt(DispBuf);//显示测试值
//	Disp_StrAt((u8 *)" S");
//	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
//	{
//	}
//	//delay_ms(120);
////	//AD7705_write_Reg(0x44);//自校准、增益为1、单极性模拟输入、片内缓冲器，FSYNC清0
////	Test_value.Test_I=Read_Channel(1);//电压AD值  channel1  电流
////	AD7705_init(0);
//	Hex_Format(Test_value.Test_Time,1,4,TRUE);//显示时间
//	LcdAddr.x=TIM_ADDR_X;LcdAddr.y=0;
//	Disp_StrAt(DispBuf);//显示测试值
//	Disp_StrAt((u8 *)" S");
////	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
////	{
////	}
//	delay_ms(30);
////	Test_value.Test_v.Test_v=Read_Channel(0);//电流AD值
//		
//	
//	
//}
//==========================================================
//函数名称：System_Setup
//函数功能：系统设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.10.28
//修改日期：2015.10.28 14:27
//备注说明：无
//==========================================================
void Step_Setup(void)
{
	u16 *pt;
	u8 key;
	u8 keymax;
	u8 index;
	bool f_disp;

	index=0;//从第一项开始
	f_disp=TRUE;//显示

	while(SystemStatus==SYS_STATUS_SETUP)
	{
		if(f_disp==TRUE)
		{
			f_disp=FALSE;
			switch(index)
			{
				case 0://设置组别
						pt=(u16*)(&SaveData.Group);
						NumBox.Num=*pt+1;
						NumBox.Max=9;//Max
						NumBox.Min=1;//Min
						NumBox.Dot=0;//Dot
						NumBox.Len=1;
					break;
				case 1://设置项目
						pt=(u16*)(&SaveData.Setup.Group_Item);
						NumBox.Title=(u8*)GROUP_DISP_ITEM[0];
						NumBox.Num=*pt;
						NumBox.Max=3;//Max
						NumBox.Min=0;//Min
						NumBox.Dot=0;//Dot
						NumBox.Len=1;

						
					break;
				case 2:// AC/DC选择  绝缘电阻就直接跳过去
					switch(SaveData.Setup.Group_Item)
					{
						case I_SETUP:

							
							break;
						case W_SETUP:
							
							//break;
						case I_WSETUP:
							//break;
						case W_ISETUP:
							if(SaveData.Setup.Item>1)
								SaveData.Setup.Item=0;
							pt=(u16*)(&SaveData.Setup.Item);
							NumBox.Title=(u8*)AC_DC_SET[0];
							NumBox.Num=*pt;
							NumBox.Max=1;//Max
							NumBox.Min=0;//Min
							NumBox.Dot=0;//Dot
							NumBox.Len=1;
							break;
						
					
					}
					
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			
			case 9:
				
				switch(SaveData.Setup.Group_Item)
				{
					case I_SETUP:

						
						break;
					case W_SETUP:
						
						//break;
					case I_WSETUP:
						//break;
					case W_ISETUP:
						pt=(u16* )(&SaveData.Setup.Output + index-3);
						if(SaveData.Setup.Item==0)//交流设置
						{
							
							
							NumBox.Title=(u8*)W_SET[0];
							NumBox.Num=*pt;
							NumBox.Max=(u16)ParameterLimit_AC[index-1][0];//Max
							NumBox.Min=(u16)ParameterLimit_AC[index-1][1];//Max;//Min
							NumBox.Dot=ParameterLimit_dot[index-3];//Dot
							NumBox.Len=ParameterLimit_len[index];
						}
						else//直流设置
						{
							
							NumBox.Title=(u8*)W_SET[0];
							NumBox.Num=*pt;
							NumBox.Max=(u16)ParameterLimit[index-1][0];//Max
							NumBox.Min=(u16)ParameterLimit[index-1][1];//Max;//Min
							NumBox.Dot=ParameterLimit_dot[index-3];//Dot
							NumBox.Len=ParameterLimit_len[index];
						
						
						}//

						break;
					
				
				}
				break;
				case 8:
					if(SaveData.Setup.Freq>1)
						SaveData.Setup.Freq=0;
					pt=(u16*)(&SaveData.Setup.Freq);
					NumBox.Title=(u8*)FREQ_SET[0];
					NumBox.Num=*pt;
					NumBox.Max=(u16)ParameterLimit_AC[index-1][0];//Max
					NumBox.Min=(u16)ParameterLimit_AC[index-1][1];//Max;//Min
					NumBox.Dot=0;//Dot
					NumBox.Len=1;
				break;
				case 10:
				case 11:
				case 12:
				case 13:
					
					pt=(u16* )(&SaveData.Setup.Output + index-3);
					//pt=(u16*)(&SaveData.Setup[SaveData.Group].Item);
					NumBox.Title=(u8*)I_W_SET[0];
					NumBox.Num=*pt;
					NumBox.Max=(u16)ParameterLimit_AC[index-1][0];//Max
					NumBox.Min=(u16)ParameterLimit_AC[index-1][1];//Max;//Min
					NumBox.Dot=ParameterLimit_dot[index-3];//Dot
					NumBox.Len=ParameterLimit_len[index];
					break;
						
				
				
				
			
	
			
			
			}
			Disp_System_Menu(index);//显示系统界面

			//取设置值、上下限
//			u8 ListBox_Setup(NumBox_TypeDef * pt)
			
			switch(index)
			{
				case 0:
					LcdAddr.x=10;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					
					break;
				case 1:
					LcdAddr.x=8;LcdAddr.y=0;//显示地址
					key=ListBox_Setup(&NumBox);
					break;
				case 2:
					LcdAddr.x=10;LcdAddr.y=0;//显示地址
					key=ListBox_Setup(&NumBox);
					break;
				case 3:
					LcdAddr.x=10;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 4:
					LcdAddr.x=7;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 5:
					LcdAddr.x=7;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 6:
					LcdAddr.x=7;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 7:
					LcdAddr.x=8;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 8:
					LcdAddr.x=7;LcdAddr.y=0;//显示地址
					key=ListBox_Setup(&NumBox);
					break;
				case 9:
					LcdAddr.x=7;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				case 10:
					LcdAddr.x=10;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
				break;
					
				case 11:
//					LcdAddr.x=8;LcdAddr.y=0;//显示地址
//					key=Number_Setup(&NumBox);//数值框设置
//				break;
				case 12:
				case 13:
					LcdAddr.x=8;LcdAddr.y=0;//显示地址
					key=Number_Setup(&NumBox);//数值框设置
					break;
				default:
					break;
				
			
			}
			
			//if(index<2)
			
			//else
				//Resistance_Setup(&NumBox);;
			if(index==0)
			{
				*pt=NumBox.Num-1;
				ReadSetByGroup();
				Parameter_valuecomp();//比较设置参数
				
			}
			else
				*pt=NumBox.Num;//更新设置值
//		 	Check_Parameter_Limit();//参数设置值检查
	
			//按键处理
			switch(key)
			{
				case KEY_SET:	//设置键
				case L_KEY_SET:	//长按设置键
					if(SaveData.Setup.Group_Item==1&&index==1)
					{
						index=9;
					}
					if(SaveData.Setup.Item==1&&index==7)//直流
					{
						index++;
						index++;
						
					}
					else
						index++;
					if(index>1)
					{
						switch(SaveData.Setup.Group_Item)
						{
							case I_SETUP:
								keymax=14;
								break;
							case W_SETUP:
								keymax=10;
								break;
							case I_WSETUP:
								//break;
							case W_ISETUP:
								keymax=14;
								break;
							default:
								keymax=14;
								break;
						
						}
						if(index>=keymax)
						{
							
							index=0;
							SetSystemStatus(SYS_STATUS_IDLE);//待机状态
							Store_set_flash();
							
						}
					}
					f_disp=TRUE;
					break;

				case KEY_UP:	//上键
				case L_KEY_UP:	//长按上键
					break;
	
				case KEY_DOWN:		//下键
				case L_KEY_DOWN:	//长按下键
					break;
	
				case KEY_ENTER:		//确认键
//				case L_KEY_ENTER:	//长按确认键
					//SaveSystem();//保存数据
					if(SaveData.Setup.Output==1)
						SaveData.Setup.Output=2;
					SetSystemStatus(SYS_STATUS_IDLE);//待机状态
					Store_set_flash();
					SaveGroup();
				
					//ReadSaveData();
					break;
		
				case KEY_START:		//启动键
				case L_KEY_START:	//长按启动键
					//SetSystemStatus(SYS_STATUS_TEST);//启动测试状态
					break;
		
				case KEY_RESET:		//复位键
				case L_KEY_RESET:	//长按复位键
					SetSystemStatus(SYS_STATUS_IDLE);//待机状态
					break;
				
				default:
					break;
			}
		}
	}
	//Parameter_valuecomp();
}

//==========================================================
//函数名称：Resistance_Setup
//函数功能：电阻数设置处理
//入口参数：NumBox_TypeDef
//出口参数：键值
//创建日期：2016.03.10
//修改日期：2016.03.10 13:44
//备注说明：无
//==========================================================
//u8 Resistance_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;
//	u8 count;//步进计数器
//	u8 current;//当前设置位
//	bool blink;//显示闪烁标志
//	LcdAddr_TypeDef addr;//显示地址备份
//	u8 tp;//单位和小数点系数(1-4)
//	if(pt->Unit>1)
//		pt->Unit=0;
//	if(pt->Dot>6)
//		pt->Dot=0;
//	tp=3*NumBox.Unit;
//	tp+=3;
//	tp-=NumBox.Dot;

//	blink=TRUE;//显示闪烁标志

//	addr.x=LcdAddr.x;//显示地址备份
//	addr.y=LcdAddr.y;

//	count=0;//步进计数器
//	if(pt->Dot==0)
//		current=3;//当前设置位
//	else
//		current=4;//当前设置位

//	while(1)
//	{
//		if(blink)//显示
//		{
//			LcdAddr.x=addr.x;//显示地址
//			LcdAddr.y=addr.y;
//			Hex_Format(NumBox.Num,NumBox.Dot,4,TRUE);//数值格式化，4位数值
//			Disp_StrAt(DispBuf);//显示菜单值
//			if(pt->Unit==0)Disp_Char('m');
//			if(pt->Unit==1)Disp_Char(' ');
//			Disp_Char(OHM);
//		}

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				return(KEY_SET);
////				break;

//			case KEY_DOWN:		//下键
//				blink=TRUE;//显示闪烁标志
//				count=0;//步进计数器
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//响两声
//					if(tp>1)
//					{
//						tp--;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//					}
//					else
//						pt->Num=pt->Min;

//				}
//				break;

//			case L_KEY_DOWN:	//长按下键
//				blink=TRUE;//显示闪烁标志
//				count++;//步进计数器
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
////				if(count>28)//步进计数器
////				{
////					if(len>0)len--;
////					if(len>0)len--;
////					if(len>0)len--;
////				}
////				else if(count>19)//步进计数器
//				if(count>19)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//步进计数器
//				{
//					if(len>0)len--;
//				}
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//响两声
//					if(tp>1)
//					{
//						tp--;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//						count=0;//步进计数器
//					}
//					else
//						pt->Num=pt->Min;
//				}
//				break;

//			case KEY_UP:	//上键
//				blink=TRUE;//显示闪烁标志
//				count=0;//步进计数器
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
////					pt->Num=pt->Min;
////					Beep_Two();//响两声
//					if(tp<4)
//					{
//						pt->Num=pt->Max/10+1;
//						tp++;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//					}
//					else
//						pt->Num=pt->Max;
//				}
//				break;

//			case L_KEY_UP:	//长按上键
//				blink=TRUE;//显示闪烁标志
//				count++;//步进计数器
//				if(current>(3-NumBox.Dot))//小数点位
//					len=current-1;
//				else
//					len=current;
////				if(count>28)//步进计数器
////				{
////					if(len>0)len--;
////					if(len>0)len--;
////					if(len>0)len--;
////				}
////				else if(count>19)//步进计数器
//				if(count>19)//步进计数器
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//步进计数器
//				{
//					if(len>0)len--;
//				}
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
////					pt->Num=pt->Min;
////					Beep_Two();//响两声
//					if(tp<4)
//					{
//						tp++;
//						pt->Num=pt->Max/10+1;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//						count=0;//步进计数器
//					}
//					else
//						pt->Num=pt->Max;
//				}
//				break;

//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				return(KEY_ENTER);
//				//break;

//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				return(KEY_START);
////				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				return(KEY_RESET);
////				break;

//			default:
//				if(Keyboard.continuance!=TRUE) //持续按键
//					count=0;//步进计数器
//				break;
//		}
//	}
//}
//==========================================================
//系统菜单项
//enum SystemMenuEnum
//{	
//	SYSTEM_MENU_UART ,
//	SYSTEM_MENU_FREQ60 ,
//	SYSTEM_MENU_CONNECT ,
//	SYSTEM_MENU_CONNECT_TIME ,
//	SYSTEM_MENU_BEEP ,
//	SYSTEM_MENU_FAIL_PAUSE ,
////	SYSTEM_MENU_BAR_SCAN ,
//};
//==========================================================
//系统项
//const u8 SystemTab[][13]=
//{
//	"1.串口开关: ",
//	"2.交流频率: ",
//	"3.步骤连接: ",
//	"4.连接时间: ",
//	"5.讯响开关: ",
//	"6.失败暂停: ",
////	"7.条码扫描: ",
//};
//==========================================================
//系统项上、下限
//const u8 SystemLimit[][2]=
//{
//	{ 1, 0},//串口开关
//	{ 1, 0},//交流频率
//	{ 1, 0},//步骤连接
//	{ 99, 5},//连接时间
//	{ 1, 0},//讯响开关
//	{ 1, 0},//失败暂停
////	{ 1, 0},//条码扫描
//};
//==========================================================
//频率
//const u8 FrequencyTab[][5]=
//{
//	"50Hz",
//	"60Hz",
//};
//==========================================================
//开关
//const u8 SwitchTab[][5]=
//{
//	"关闭",
//	"打开",
//};

//==========================================================
//函数名称：Check_System_Limit
//函数功能：系统值检查
//入口参数：步骤
//出口参数：无
//创建日期：2015.01.22 
//修改日期：2015.08.18 13:28
//备注说明：含上限、下限检查
//==========================================================
//void Check_System_Limit(void)
//{
//	u8 i;
//	u8 *pt;

//	pt=(u8* )&SaveData.System;
//	for(i=0;i<SYSTEM_MENU_MAX;i++)//共8项
//	{
//		if(*pt>SystemLimit[i][0])//Max
//			*pt= SystemLimit[i][0];//Max
//		if(*pt<SystemLimit[i][1])//Min
//			*pt=SystemLimit[i][1];//Min
//		pt++;
//	}
//}

//==========================================================
//函数名称：Disp_System_Info
//函数功能：显示系统信息
//入口参数：u8 index-第几项
//出口参数：无
//创建日期：2015.01.21
//修改日期：2015.08.19 09:48
//备注说明：按index进行分页显示
//==========================================================
//void Disp_System_Info(u8 index)
//{
//	u8 i;
//	u8 begin;
//	u8 end;
//	u8 page;

//	begin=index/SYSTEM_MENU_PAGE*SYSTEM_MENU_PAGE;//起始项
//	end=begin+SYSTEM_MENU_PAGE;//结束项
//	if(end>SYSTEM_MENU_MAX)
//		end=SYSTEM_MENU_MAX;
//	page=(SYSTEM_MENU_MAX-1)/SYSTEM_MENU_PAGE+'1';//总页数
//	
//	LcdAddr.x=19;LcdAddr.y=2;
//	Disp_Char(index/SYSTEM_MENU_PAGE+'1',0);//显示当前页码
//	Disp_Char('/',0);
//	Disp_Char(page,0);//显示总页数

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=begin;i<end;i++)
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&SystemTab[i][0],0);//显示编号
//		Disp_System_Value(i);//显示系统值
//		LcdAddr.x++;
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//函数名称：Disp_System_Menu
//函数功能：显示系统界面
//入口参数：无
//出口参数：无
//创建日期：2015.01.22
//修改日期：2015.08.19 09:00
//备注说明：无
//==========================================================
//void Disp_System_Menu(void)
//{
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("系统设置",0);//显示
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("按<上,下>键修改,<左,右>键移动",0);//显示
//}

//==========================================================
//函数名称：Disp_System_Value
//函数功能：显示系统值
//入口参数：index:第几项参数
//出口参数：无
//创建日期：2015.01.21
//修改日期：2015.09.06 09:06
//备注说明：数值位数+小数点+单位的长度固定为4个字符
//==========================================================
//void Disp_System_Value(u8 index)
//{
//	index%=SYSTEM_MENU_MAX;//最大系统项
//	
//	switch(index)
//	{
//		case SYSTEM_MENU_UART://串口开关
//			Disp_Str(&SwitchTab[SaveData.System.Uart],0);//显示
//			break;

//		case SYSTEM_MENU_FREQ60://交流输出频率
//			Disp_Str(&FrequencyTab[SaveData.System.Freq60],0);//显示
//			break;

//		case SYSTEM_MENU_CONNECT://步骤连接
//			Disp_Str(&SwitchTab[SaveData.System.Connect],0);//显示
//			break;

//		case SYSTEM_MENU_CONNECT_TIME://连接时间
//			Hex_Format(SaveData.System.ConnectTime,1,2,0);//数据格式化到DispBuf
//			Disp_Str(DispBuf,0);//显示
//			Disp_Str("s",0);//显示空格
//			Disp_Str(" ",0);//显示空格
//			break;

//		case SYSTEM_MENU_BEEP://讯响开关
//			Disp_Str(&SwitchTab[SaveData.System.Beep],0);//显示
//			break;

//		case SYSTEM_MENU_FAIL_PAUSE://失败暂停开关
//			Disp_Str(&SwitchTab[SaveData.System.FailPause],0);//显示
//			break;

////		case SYSTEM_MENU_BAR_SCAN://条码扫描开关
////			Disp_Str(&SwitchTab[SaveData.System.BarScan],0);//显示
////			break;

//		default:
//			break;
//	}
//}

//==========================================================
//函数名称：System_Setup
//函数功能：系统设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.21
//修改日期：2015.09.06 09:10
//备注说明：无
//==========================================================
//void System_Setup(void)
//{
//	u8 *pt;
//	u8 key;
//	u8 index;
//	Bool f_disp;//显示更新

//	f_disp=TRUE;
//	index=0;//从第一项开始
//	Disp_System_Menu();//显示系统界面

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//显示更新
//		{
////			Disp_Clr( );//清屏
//			//覆盖后2项设置项，代替清屏，避免闪烁现象
//			if((index>=SYSTEM_MENU_PAGE))//第二页
//			{
//				LcdAddr.x=SETUP_ADDR_X+1;//显示地址
//				LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*2;//第三项
//				Disp_Str("                ",0);//16个空格
//				LcdAddr.x=SETUP_ADDR_X+1;//显示地址
//				LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*3;//第四项
//				Disp_Str("                ",0);//1个空格
//				Disp_Str(" ",0);//1个空格
//			}
//			f_disp=FALSE;
////			Disp_System_Menu();//显示系统界面
//			Disp_System_Info(index);//显示系统信息
//		}

//		LcdAddr.x=SETUP_ADDR_X+1+12;//数值显示地址
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*(index%SYSTEM_MENU_PAGE);

//		//取设置值
//		pt=(u8* )&SaveData.System + index;
//		NumBox.Num=*pt;

//		//取上下限阀值
//		NumBox.Max=SystemLimit[index][0];//Max
//		NumBox.Min=SystemLimit[index][1];//Min
//		NumBox.Dot=0;//Dot

//		switch(index)//数值设置处理
//		{
//			case SYSTEM_MENU_UART://串口开关
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//列表框设置
//				if(SaveData.System.Uart==1)
//					Start_Uart();//串口开启
//				else
//					Stop_Uart();//串口关闭
//				break;

//			case SYSTEM_MENU_FREQ60://频率
//				NumBox.Title=FrequencyTab[0];
//				key=ListBox_Setup(&NumBox);//列表框设置
//				break;

//			case SYSTEM_MENU_CONNECT://步骤连接
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//列表框设置
//				break;

//			case SYSTEM_MENU_CONNECT_TIME://连接时间
//				NumBox.Dot=1;//Dot
//				key=Number_Setup(&NumBox);//数值框设置
//				break;

//			case SYSTEM_MENU_BEEP://讯响开关
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//列表框设置
//				break;

//			case SYSTEM_MENU_FAIL_PAUSE://失败暂停开关
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//列表框设置
//				break;

////			case SYSTEM_MENU_BAR_SCAN://条码扫描开关
////				NumBox.Title=SwitchTab[0];
////				key=ListBox_Setup(&NumBox);//列表框设置
////				break;

//			default:
//				break;
//		}

//		//更新设置值
//		*pt=NumBox.Num;
//		Check_System_Limit();//系统值检查
//		f_disp=TRUE;//显示更新

//		//按键处理
//		switch(key)
//		{
//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				break;

//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				break;

//			case KEY_LEFT:		//左键
////			case L_KEY_LEFT:	//长按左键
//				if(index)
//					index--;
//				else
//					index=SYSTEM_MENU_MAX-1;
//				break;
//	
//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				index++;
//				if(index>=SYSTEM_MENU_MAX)
//					index=0;
//				break;

//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
//				break;
//	
//			case KEY_ENTER:		//确认键
////			case L_KEY_ENTER:	//长按确认键
//				//参数保存
//				SaveSystem();//保存系统参数
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_START);//启动测试状态
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//函数名称：Password_Check
//函数功能：密码校验
//入口参数：无
//出口参数：TRUE:有效
//创建日期：2015.01.29 
//修改日期：2015.08.24 11:40
//备注说明：无
//==========================================================
//Bool Password_Check(void)
//{
//	u8 key;

//	if(MenuIndex!=2)//出厂信息界面
//	{
//		if(F_Password==TRUE)//密码有效标志	
//			return (TRUE);
//	
//		if(SaveData.Factory.Password==0)//密码为零时无需校验
//			return (TRUE);
//	}
//	else
//	{
//		Disp_Clr( );//清屏
//	}
//	
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("请输入密码",0);//显示
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("按<上,下>键修改,<确认>键输入",0);//显示

//	while(1)
//	{
//		LcdAddr.x=13;//设置显示地址
//		LcdAddr.y=50;
//		Disp_Str("****",0);//显示

//		LcdAddr.x=13;//设置显示地址
//		NumBox.Num=0;//Value
//		NumBox.Max=9999;//Max
//		NumBox.Min=0;//Min
//		NumBox.Dot=0;//Dot

//		key=Number_Setup(&NumBox);//数值框设置
//		switch(key)//按键处理
//		{
//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				break;

//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				break;

//			case KEY_LEFT:	//左键
////			case L_KEY_LEFT:	//长按左键
//				break;
//	
//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
////				break;

//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				break;
//	
//			case KEY_ENTER:		//确认键
////			case L_KEY_ENTER:	//长按确认键
//				Disp_Clr();//清屏
//				if(MenuIndex==2)//出厂信息界面
//				{
//					if(NumBox.Num==918)//出厂配置密码
//						return (TRUE);
//					else
//						return (FALSE);
//				}
//				else
//				{
//					if(NumBox.Num==SaveData.Factory.Password)//当前密码判别
//					{
//						F_Password=TRUE;//密码验证有效
//						return (TRUE);
//					}
//					else
//						return (FALSE);
//				}
//				break;
//	
//			case KEY_START:		//启动键
////			case L_KEY_START:	//长按启动键
//				break;
//	
//			case KEY_RESET:		//复位键
////			case L_KEY_RESET:	//长按复位键
//				return (FALSE);
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//密码项
//enum PasswordEnum
//{	
//	PASSWORD_MENU_OLD ,
//	PASSWORD_MENU_NEW ,
//	PASSWORD_MENU_NEW2 ,
//};
//==========================================================
//密码项
//const u8 PasswordTab[][11]=
//{
//	"当前密码: ",
//	"新设密码: ",
//	"密码确认: ",
//};
//==========================================================
//函数名称：Disp_Password_Info
//函数功能：显示密码信息
//入口参数：无
//出口参数：无
//创建日期：2015.01.23
//修改日期：2015.08.19 10:45
//备注说明：无
//==========================================================
//void Disp_Password_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<3;i++)//共3项
//	{
//		LcdAddr.x=SETUP_ADDR_X+2;
//		Disp_Str(&PasswordTab[i][0],0);//显示编号
//		Disp_Str("****",0);//显示
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//函数名称：Password_Setup
//函数功能：密码设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.23
//修改日期：2015.08.20 11:03
//备注说明：无
//==========================================================
//void Password_Setup(void)
//{
//	u8 key;
//	u8 index;
//	u16 pw[3];

//	F_Password=FALSE;//进入密码设置，密码验证无效
//	for(index=0;index<3;index++)//共3项
//	{
//		pw[index]=0;
//	}
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("设置密码",0);//显示
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("按<上,下>键修改,<左,右>键移动",0);//显示

//	index=0;//从第一项开始

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		Disp_Password_Info();//显示密码信息

//		LcdAddr.x=SETUP_ADDR_X+2+10;//设置显示地址
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*index;

//		//取设置值
//		NumBox.Num=0;

//		//取上下限阀值
//		NumBox.Max=9999;//Max
//		NumBox.Min=0;//Min
//		NumBox.Dot=0;//Dot

//		key=Number_Setup(&NumBox);//数值框设置
//		switch(key)//按键处理
//		{
//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				break;

//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				break;

//			case KEY_LEFT:	//左键
////			case L_KEY_LEFT:	//长按左键
//				pw[index]=NumBox.Num;//更新当前设置值
//				if(index)
//					index--;
//				else
//					index=2;
//				LcdAddr.x=1;LcdAddr.y=110;
//				if(index==2)//第三项更新提示
//					Disp_Str("按<确认>键输入, <退出>键返回 ",0);//显示
//				else
//					Disp_Str("按<上,下>键修改,<左,右>键移动",0);//显示
//				break;
//	
//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				pw[index]=NumBox.Num;//更新当前设置值
//				index++;
//				if(index>2)
//					index=0;
//				LcdAddr.x=1;LcdAddr.y=110;
//				if(index==2)//第三项更新提示
//					Disp_Str("按<确认>键输入, <退出>键返回 ",0);//显示
//				else
//					Disp_Str("按<上,下>键修改,<左,右>键移动",0);//显示
//				break;

//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
//				break;
//	
//			case KEY_ENTER:		//确认键
////			case L_KEY_ENTER:	//长按确认键
//				pw[index]=NumBox.Num;//更新当前设置值
//				key=0;//状态
//				if(pw[0]==SaveData.Factory.Password)//当前密码判别
//				{
//					key=1;
//					if(pw[1]==pw[2])//新设密码判别
//					{
//						key=2;
//						if((pw[0]==0)&&(pw[1]==0))//密码为空
//						{
//							key=3;
//						}
//						else
//						{
//							SaveData.Factory.Password=pw[1];//密码更新
//							SaveFactory();//保存密码
//						}
//					}
//				}
//				if(key<3)
//				{
////					Disp_Clr();//清屏
////					LcdAddr.x=8;LcdAddr.y=88;
//					LcdAddr.x=9;LcdAddr.y=2;
//					if(key==0)
//					{
//						Disp_Str("当前密码错误",1);//显示
//						Beep_Two();//响两声
//					}
//					else if(key==1)
//					{
//						Disp_Str("密码设置错误",1);//显示
//						Beep_Two();//响两声
//					}
//					else if(key==2)
//					{
//						Disp_Str("密码修改成功",1);//显示
//					}
//					Delay_100ms(12);//延时1.2s
//				}
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//	
//			case KEY_START:		//启动键
////			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_START);//启动测试状态
//				break;
//	
//			case KEY_RESET:		//复位键
////			case L_KEY_RESET:	//长按复位键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//函数名称：FactoryInfo_Setup
//函数功能：出厂信息设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.14
//修改日期：2015.08.24 11:54
//备注说明：
//按上下键：显示仪器信息；
//长按右键：进入出厂配置设置界面
//长按左键：加载默认出厂设置值
//长按设置：系统复位处理
//==========================================================
//void FactoryInfo_Setup(void)
//{
//	u8 key;

//	LcdAddr.x=7;LcdAddr.y=2;
//	Disp_Product_Model();//显示产品型号
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	Disp_Factory_Info();//显示出厂信息
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	LcdAddr.x=7;LcdAddr.y=110;
//	Disp_Str("按<确认>键退出",0);//显示

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
////			case KEY_SET:	//设置键
//			case L_KEY_SET:	//长按设置键
//				ResetSys();//软件复位
//				break;

//			case KEY_UP:	//上键
//			case L_KEY_UP:	//长按上键
////				break;
//			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
//				Disp_Instrument_Info();//显示仪器信息
//				return;
////				break;
//	
////			case KEY_LEFT:	//左键
//			case L_KEY_LEFT:	//长按左键
//#if (MENU_CONFIG_SUPPORT)
//				if(Password_Check())//密码校验,TRUE有效
//				{
//					LoadDefaultSet();//调用默认设置值
//					LoadDefaultCalibrate();//加载默认校准值
//					Beep_One();//蜂鸣器响一声
//				}
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//#endif
//				break;

////			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
//#if (MENU_CONFIG_SUPPORT)
//				if(Password_Check())//密码校验,TRUE有效
//					Config_Setup();//出厂配置值设置处理
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//#endif
//				break;

//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_START);//启动测试状态
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//函数名称：Disp_Factory_Info
//函数功能：显示出厂信息
//入口参数：无
//出口参数：无
//创建日期：2015.01.09
//修改日期：2015.08.19 10:01
//备注说明：无
//==========================================================
//void Disp_Factory_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<4;i++)//共4项
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&NumTab[i][0],0);//显示编号
//		switch(i)
//		{
//			case 0:
//				Disp_Software_Version();//显示软件版本
//				break;
//			case 1:
//				Disp_Hardware_Version();//显示硬件版本
//				break;
//			case 2:
//				Disp_Boot_Number();//开机次数
//				break;
//			case 3:
//				Disp_Compile_Date();//显示编译日期
//				break;
//			default:
//				break;

//		}
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//函数名称：Disp_Instrument_Info
//函数功能：显示仪器信息
//入口参数：无
//出口参数：无
//创建日期：2015.01.22
//修改日期：2015.08.20 15:52
//备注说明：无
//==========================================================
//void Disp_Instrument_Info(void)
//{
//	u8 key;

//	Disp_Clr( );//清屏

//	LcdAddr.x=0;LcdAddr.y=1;
//	Disp_Software_Version();//显示软件版本
//	LcdAddr.x=15;
//	Disp_Boot_Number();//开机次数

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Hardware_Version();//显示硬件版本
//	LcdAddr.x=15;
//	Disp_Product_ID();//显示出厂编号	
//	
//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Compile_Date();//显示编译日期

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Chip_ID();//显示软件编号

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Lcd_Draw_Line(0,LcdAddr.y,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度
//	LcdAddr.y+=2;
//	Lcd_Draw_Line(0,LcdAddr.y,LCD_ADDR_X_MAX);//X=0:画横线，否则画竖线，len:长度或高度

//	LcdAddr.y+=2;
//	Disp_Company_Name();//显示厂商名称

//	LcdAddr.x=0;LcdAddr.y+=17;
//	Disp_Company_Http();//显示厂商主页

//	LcdAddr.x=0;LcdAddr.y+=17;
//	Disp_Company_Telephone();//显示厂商电话

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
//				break;
//	
//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				break;
//	
//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				break;
//	
//			case KEY_LEFT:	//左键
////			case L_KEY_LEFT:	//长按左键
//				break;

//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				break;

//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_START);//启动测试状态
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//配置项
//enum ConfigMenuEnum
//{	
//	CONFIG_MENU_BOOTNUM ,
//	CONFIG_MENU_FACTORYID ,
//	CONFIG_MENU_PASSWORD ,
//};
//==========================================================
//配置项
//const u8 ConfigTab[][13]=
//{
//	"1.开机次数: ",
//	"2.出厂编号: ",
//	"3.设置密码: ",
//};
//==========================================================
//配置项上、下限
//const u16 ConfigLimit[][2]=
//{
//	{ 9999, 1},//开机次数
//	{ 9999, 0},//出厂编号
//	{ 9999, 0},//设置密码
//};
 
//==========================================================
//函数名称：Check_Config_Limit
//函数功能：配置值检查
//入口参数：步骤
//出口参数：无
//创建日期：2015.01.22 
//修改日期：2015.09.06 11:15
//备注说明：含上限、下限检查
//==========================================================
//void Check_Config_Limit(void)
//{
//	u8 i;
//	u16 *pt;

//	//初始数据判别
//	pt=(u16* )&SaveData.Factory;
//	for(i=0;i<CONFIG_MENU_MAX;i++)//共3项
//	{
//		if(*pt!=65535)
//			break;
//	}
//	if(i>=CONFIG_MENU_MAX)//空数据
//	{
//		LoadDefaultSet();//调用默认设置值
//		LoadDefaultCalibrate();//加载默认校准值
//		Beep_One();//蜂鸣器响一声
//	}
//	else
//	{
//		pt=(u16* )&SaveData.Factory;
//		for(i=0;i<CONFIG_MENU_MAX;i++)//共3项
//		{
//			if(*pt>ConfigLimit[i][0])//Max
//				*pt= ConfigLimit[i][1];//Min
//			if(*pt<ConfigLimit[i][1])//Min
//				*pt=ConfigLimit[i][1];//Min
//			pt++;
//		}
//	}
//}

//==========================================================
//函数名称：Disp_Config_Info
//函数功能：显示配置信息
//入口参数：无
//出口参数：无
//创建日期：2015.01.21
//修改日期：2015.08.19 10:17
//备注说明：无
//==========================================================
//void Disp_Config_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<CONFIG_MENU_MAX;i++)//共3项
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&ConfigTab[i][0],0);//显示
//		Disp_Config_Value(i);//显示配置值
//		LcdAddr.x++;
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//函数名称：Disp_Config_Menu
//函数功能：显示配置界面
//入口参数：无
//出口参数：无
//创建日期：2015.01.22
//修改日期：2015.08.19 10:16
//备注说明：无
//==========================================================
void Comp_test(u16 comp_data)
{
//	if(SaveData.System.Res_Lo!=0)
//	{
//		if(SaveData.System.Res_Lo>comp_data)
//		{
//			SetSystemMessage(MSG_LOW);//系统信息-测试
////			Led_Pass_Off();//关合格灯
////			Led_Fail_On();//开报警灯
//			F_Fail=TRUE;
//		
//		}
//	
//	}
//	if(!F_Fail)
//	{
//		
//		if(SaveData.System.Res_Hi!=0)
//		{
//			if(SaveData.System.Res_Hi<comp_data)
//			{
//				SetSystemMessage(MSG_HIGH);//系统信息-上限报警
////				Led_Pass_Off();//关合格灯
////				Led_Fail_On();//开报警灯
//				F_Fail=TRUE;	
//			}
//		
//		}
//		if(!F_Fail)
//		{
//			SetSystemMessage(MSG_PASS);//系统信息-测试
////			Led_Pass_On();//关合格灯
////			Led_Fail_Off();//开报警灯
////		
//		}
//	}

}

//==========================================================
//函数名称：Disp_Config_Value
//函数功能：显示配置值
//入口参数：index:第几项参数
//出口参数：无
//创建日期：2015.01.22
//修改日期：2015.08.19 10:22
//备注说明：数值位数+小数点+单位的长度固定为4个字符
//==========================================================
//void Disp_Config_Value(u8 index)
//{
//	index%=CONFIG_MENU_MAX;//最大配置项
//	
//	switch(index)
//	{
//		case CONFIG_MENU_BOOTNUM:
//			Hex_Format(SaveData.Factory.BootNum,0,4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,0);//显示
//			break;

//		case CONFIG_MENU_FACTORYID:
//			Hex_Format(SaveData.Factory.ProductId,0,4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,0);//显示
//			break;

//		case CONFIG_MENU_PASSWORD:
//			Hex_Format(SaveData.Factory.Password,0,4,1);//数据格式化到DispBuf
//			Disp_Str(DispBuf,0);//显示
//			break;

//		default:
//			break;
//	}
//}

//==========================================================
//函数名称：Config_Setup
//函数功能：配置设置处理
//入口参数：无
//出口参数：无
//创建日期：2015.01.22
//修改日期：2015.08.19 10:29
//备注说明：无
//==========================================================
//void Config_Setup(void)
//{
//	u16 *pt;
//	u8 key;
//	u8 index;
//	Bool f_disp;//显示更新

//	Disp_Config_Menu();//显示配置界面
//	f_disp=FALSE;
//	index=0;//从第一项开始

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//显示更新
//		{
//			f_disp=FALSE;
//			Disp_Config_Info();//显示配置信息
//		}

//		LcdAddr.x=SETUP_ADDR_X+1+12;//数值显示地址
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*index;

//		//取设置值
//		pt=(u16* )&SaveData.Factory+index;
//		NumBox.Num=*pt;

//		//取上下限阀值
//		NumBox.Max=ConfigLimit[index][0];//Max
//		NumBox.Min=ConfigLimit[index][1];//Min
//		NumBox.Dot=0;//Dot

//		switch(index)//数值设置处理
//		{
//			case CONFIG_MENU_BOOTNUM:
//			case CONFIG_MENU_FACTORYID:
//			case CONFIG_MENU_PASSWORD:
//				key=Number_Setup(&NumBox);//列表框设置
//				break;
//	
//			default:
//				break;
//		}

//		*pt=NumBox.Num;//更新设置值
//		Check_Config_Limit();//配置值检查
//		f_disp=TRUE;//显示更新

//		//按键处理
//		switch(key)
//		{
//			case KEY_UP:	//上键
////			case L_KEY_UP:	//长按上键
//				break;

//			case KEY_DOWN:		//下键
////			case L_KEY_DOWN:	//长按下键
//				break;

//			case KEY_LEFT:	//左键
////			case L_KEY_LEFT:	//长按左键
//				if(index)
//					index--;
//				else
//					index=CONFIG_MENU_MAX-1;
//				break;

//			case KEY_RIGHT:		//右键
////			case L_KEY_RIGHT:	//长按右键
//				index++;
//				if(index>=CONFIG_MENU_MAX)
//					index=0;
//				break;
//	
//			case KEY_SET:	//设置键
////			case L_KEY_SET:	//长按设置键
//				break;
//	
//			case KEY_ENTER:		//确认键
////			case L_KEY_ENTER:	//长按确认键
//				//参数保存
//				SaveFactory();//保存开机次数
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				SetSystemStatus(SYS_STATUS_START);//启动测试状态
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				SetSystemStatus(SYS_STATUS_IDLE);//待机状态
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

////==========================================================
////系统状态
//const u8 SysStatusList[][5+1]=
//{
//	{"Idle "},
//	{"Test "},
//	{"Stop "},
//	{"Clr  "},
//	{"Set  "},
//};
////==========================================================
////函数名称：Disp_SysStatus
////函数功能：显示系统状态
////入口参数：无
////出口参数：无
////创建日期：2014.10.15
////修改日期：2014.10.15 15:17
////备注说明：无
////==========================================================
//void Disp_SysStatus(void)
//{
//	Disp_Str(SysStatusList[GetSystemStatus()],0);//显示系统状态
//}
//
//==========================================================
//系统信息
//const u8 SysMessageList[][5]=
//{	
//	{"Idle"},
//	{"Ramp"},
//	{"Test"},
//	{"Stop"},
//	{"Pass"},
//	{"Arc "},
//	{"High"},
//	{"Low "},
//	{"Over"},
//	{"Err "},
//};
//==========================================================
//函数名称：Disp_SysMessage
//函数功能：显示系统信息
//入口参数：无
//出口参数：无
//创建日期：2014.10.15
//修改日期：2014.10.15 15:17
//备注说明：无
//==========================================================
//void Disp_SysMessage(void)
//{
//	Disp_Str(SysMessageList[GetSystemMessage()],0);//显示系统信息
////	Disp_Txt_Str(SysMessageList[GetSystemMessage()]);//显示系统信息
//}

//==========================================================
//开机界面-整屏图片格式
//常州扬子(48*48)
//常州扬子电子有限公司(16*16)
//常州市新北区庆阳路2号
//电话：88226706 8826707
//const u8 Kjjm_Pic[]=
//{
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//};


u16 Da_out(u16 v_value,u8 V_range) // 1   500V   0  50V
{
	//3160;
	u32 return_value;
//	Calibrate.IRVol[0].Num=902;
//	Calibrate.IRVol[1].Num=88;
	
//	if(V_range)
//	{
//		return_value=((u32)v_value*CAL_500V)/Calibrate.IRVol[0].Num;
//		return_value=return_value-140/v_value;
//	}
//	else
//	{
//		return_value=((u32)v_value*CAL_50V)/Calibrate.IRVol[1].Num;
//		return_value=return_value-140/v_value;
//	}
	return	return_value;
}
//电阻计算，电压/电流*倍率
void Get_Res(void)
{
	Res_count.r=Res_count.v*Res_count.rate/Res_count.i;
}
/********************************
函数名称: void DispF(float f)
功能 ：用科学记数法显示浮点数，在float全范围内精确显示，超出范围给出提示。
说明 ：浮点数表示范围为+-1.175494E-38到+-3.402823E+38
入口参数：f为要显示的浮点数
返回值 ：无
********************************/
void DispF(float f)   
{
	float  tf, b;
	unsigned long w;
	s8 i, j;
	if(f<0)
	{
	//         PrintChar('-');
		f=-1.0*f;
		Float.Sign=1;
	}
	if(f<1.175494E-38)
	{
		//printf("?.??????");   //太小了，超出了最小范围。
		return;
	}
	if(f>1E35)            //f>10^35
	{
		tf=f/1E35;
		b=1000.0;
		for(i=0,j=38;i<4;i++,j--)
		{
			if(tf/b<1)
			b=b/10.0;
			else 
				break;
			w=f/(1E29*b);      //1E35*b/1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E28)
	{
		tf=f/1E28;
		b=1E7;
		for(i=0,j=35;i<8;i++,j--)
		{
			if(tf/b<1)
			b=b/10.0;
			else
				break;
			w=f/(1E22*b);     //1E28*b/1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E21)
	{
		tf=f/1E21;
		b=1E7;
		for(i=0,j=28;i<8;i++,j--)
		{
			if(tf/b<1)
			b=b/10.0;
			else
				break;
			w=f/(1E15*b);      //1E21*b/1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E14)
	{
		tf=f/1E14;
		b=1E7;
		for(i=0,j=21;i<8;i++,j--)
		{
			if(tf/b<1)
				b=b/10.0;
			else 
				break;
			w=f/(1E8*b);       //1E14*b/1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E7)
	{
		tf=f/1E7;
		b=1E7;
		for(i=0,j=13;i<8;i++,j--)
			{
			if(tf/b<1) 
				b=b/10.0;
			else 
				break;
			w=f/(10.0*b);      //1E28*b/1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1)
	{
		tf=f;
		b=1E7;
		for(i=0,j=7;i<8;i++,j--)
		{
			if(tf/b<1)
				b=b/10.0;
			else 
				break;
		}
		w=f/(1E-6*b);       //1E0*b/1E6
		//PrintW(w,j);
		Float.Digit=w;
		Float.Exponent=j;
	}
	else if(f>1E-7)
	{
		tf=f*1E7;           //10^-7      
		b=1E7;
		for(i=0,j=0;i<8;i++,j--)
		{
			if(tf/b<1) 
				b=b/10.0;
			else 
				break;
			w=f*(1E13/b);     //(1E7/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E-14)
	{
		tf=f*1E14;        //10^-14        
		b=1E7;
		for(i=0,j=-7;i<8;i++,j--)
		{
			if(tf/b<1)
				b=b/10.0;
			else 
				break;
			w=f*(1E20/b);    //(1E14/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E-21)
	{
		tf=f*1E21;       //10^-21
		b=1E7;
		for(i=0,j=-14;i<8;i++,j--)
		{
			if(tf/b<1)
				b=b/10.0;
			else 
				break;
			w=f*(1E27/b);    //(1E21/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E-28)
	{
		tf=f*1E28;            //10^-28
		b=1E7;
		for(i=0,j=-21;i<8;i++,j--)
		{
			if(tf/b<1) 
				b=b/10.0;
			else
				break;
			w=f*(1E34/b);      //(1E28/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else if(f>1E-35)
	{
		tf=f*1E35;             //10^-35
		b=1E7;
		for(i=0,j=-28;i<8;i++,j--)
		{
			if(tf/b<1)
				b=b/10.0;
			else 
				break;
			w=f*(1E35/b)*1E6;   //(1E35/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
	else
	{
		tf=f*1E38;                 //f<=10^-35
		b=1000.0;
		for(i=0,j=-35;i<4;i++,j--)
		{
			if(tf/b<1) 
				b=b/10.0;
			else 
				break;
			w=f*(1E38/b)*1E6;      //(1E38/b)*1E6
			//PrintW(w,j);
			Float.Digit=w;
			Float.Exponent=j;
		}
	}
}

void Dma_Int(void)
{
	MYDMA_Config(DMA1_Channel2,(u32)&GPIOC->ODR,(u32)Sin,256);
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送  
	
	MYDMA_Enable(DMA1_Channel2);//开始一次DMA传输！
}
//（2）显示十进制尾数和阶的子函数。
/********************************
函数名称: void PrintW(unsigned long w,char j)
功能 ：科学记数法，显示十进制尾数和阶码
入口参数：w为尾数，j为阶码
返回值 ：无
********************************/
//void PrintW(unsigned long w,char j) 
//{
//	char i;
//	unsigned long tw,b;
//	if(j<-38)                //太小了，超出最小表数范围。
//	{
//		printf("?.??????");
//		return;
//	}           
//	if(j>38)                   //此算法不会出现j>38的情况
//	{
//		printf("*.******");
//		return;
//	}
//	tw=w/1000000;
//	PrintChar(tw+’0’);
//	PrintChar(’-’);
//	w=w-tw*1000000;
//	b=100000;
//	for(i=0;i<6;i++)
//	{
//		tw=w/b;
//		PrintChar(tw+’0’);
//		w=w-tw*b;
//		b=b/10;
//	}
//	printf("E%d",(int)j);
//}

//==========================================================
//END
//==========================================================
 u32 jisuandianzu(u16 bzdzn,u16 bzdzadn,u16 I_ad,u16 V_ad,u16 bzdy)
 {
  unsigned long a,b,jieguo;
  
 // unsigned int jieguo;
  a=bzdzn;
  b=bzdzadn;
  if(I_ad==0)
  I_ad=1;
  jieguo=((a*b/bzdy)*V_ad)/I_ad;
 return jieguo;//测试电阻
 }
 
 /*************************************************************************************************************************
*函数 ? ? ? ? : void HextoBCD(u8 *pBuff,u8 len)
*功能 ? ? ? ? : 十六进制转为BCD码
*参数 ? ? ? ? : pBuff:输入的十六进制数组,len:数组长度
*返回 ? ? ? ? : 无
*依赖 : 底层宏定义
* 作者 : li_qcxy@126.com
* 时间 : 2017-1-5
* 最后修改时间:?
*说明 ? ? ? ? : 
*************************************************************************************************************************/
void HextoBCD(u8 *pBuff,u8 len) //十六进制转为BCD码
{
	u8 i,temp;
	for(i=0;i<len;i++)
	{
		temp=pBuff[i]/10;
		//time[i]=pBuff[i]%10+temp*16;
	}
}


/*************************************************************************************************************************
*函数 ? ? ? ? : void BCDtoHex(u8 *pBuff,u8 len)
*功能 ? ? ? ? : BCD码转为十六进制
*参数 ? ? ? ? : pBuff:输入的十六进制数组,len:数组长度
*返回 ? ? ? ? : 无
*依赖 : 底层宏定义
* 作者 : li_qcxy@126.com
* 时间 : 2017-1-5
* 最后修改时间:?
*说明 ? ? ? ? : 
*************************************************************************************************************************/
void BCDtoHex(u8 *pBuff,u8 len) //BCD码转为十六进制
{
	u8 i,temp;
	for(i = 0;i < len;i ++)
	{
		temp =pBuff[i] / 16;
		pBuff[i] = temp * 10 + pBuff[i] % 16;
	}
}
u8 BCDtoHex1(u8 pBuff,u8 len) //BCD码转为十六进制
{
	u8 i,temp;
	
	temp =pBuff / 16;
	pBuff = temp * 10 + pBuff % 16;
	return pBuff;
}




