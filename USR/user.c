//==========================================================
//�ļ����ƣ�User.c
//�ļ��������˵������ӳ���
//�ļ��汾��Ver1.0
//�������ڣ�2014.12.15
//�޸����ڣ�2015.09.06 11:15
//�ļ����ߣ�
//��ע˵������
//ע�������
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
//λ����������ֵ
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

//����
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
//Ѷ��
const u8 BeepTab[][4+1]=
{
	"OFF ",
	"Pass",
	"Fail",
};

//==========================================================
//����
const u8 SwitchTab[][4+1]=
{
	"OFF ",
	"ON  ",
};
#define FACTORY_MENU_MAX (sizeof(FactoryTab)/sizeof(FactoryTab[0])-1)
//==========================================================
//���ò˵�
const u8 SetupMenu[][20+1]=
{
	"1.PARAMETER SETUP   ",
	"2.COMPARE SETUP     ",
	"3.PASSWORD SETUP    ",
	"4.FACTORY INFO      ",
};
//==========================================================
//ȷ����ʾ
const u8 EnterTab[20+1]=
{
	"  Enter by <SET>    ",
};
//==========================================================
//��ֵ��ʾ
const u8 NumberTab[][20+1]=
{
	"Range:  5 - 500 ",
	"Range:  0 - 999.9 ",
	"Range:  0 - 9999 ",
	"Range:  0 - 9999 ",
};
//==========================================================
//ѡ����ʾ
const u8 SelectTab[20+1]=
{
	" Select by arrow    ",
};
//==========================================================
//�����˵�
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
//���
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
//ϵͳ�˵�
const u8 SystemTab[][12+1]=
{
	"(1)Vol_Out= ",
	"(2)T_Time = ",
	"(3)Res_Hi = ",
	"(4)Res_Lo = ",

};
//==========================================================
//ϵͳ���ϡ�����
const u16 SystemLimit[][2]=
{
	{500, 5},
	{9999, 0},
	{9999, 0},
	{9999, 0},
};
//==========================================================
//ϵͳ���ϡ�����
const u16 SystemLimitDot[5]=
{
	0,1,0,0
	
};
//==========================================================
//�������ϡ�����
//const u16 ParameterLimit[][2]=
//{
//	{ 3, 0},//ѡ�������
//	{ 1, 0},//��Ŀ ѡ��AD/DC
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
	{ 3, 0},//ѡ�������
	{ 1, 0},//��Ŀ ѡ��AD/DC
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
//	{ 3, 0},//ѡ�������
//	{ 1, 0},//��Ŀ ѡ��AD/DC
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
	{ 3, 0},//ѡ�������
	{ 1, 0},//��Ŀ ѡ��AD/DC
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
	{ 3, 0},//ѡ�������
	{ 1, 0},//��Ŀ ѡ��AD/DC
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
//ϵͳ״̬
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
//������Ϣ
const u8 FactoryTabS[][20+1]=
{	
//	{"                "},//�ͺ�
	{"     JINKO      "},//�ͺ�
	{" 7122  VER:2.12 "},//����
	{" Tel:0519-88226706  "},//�绰
	{" Fax:0519-88226808  "},//����
	{" "},//��ҳ
};

const u8 FactoryTab[][20+1]=
{	
//	{"                "},//�ͺ�
	{"     JINKO      "},//�ͺ�
	{" 7122  VER:2.12S"},//����
	{" Tel:0519-88226706  "},//�绰
	{" Fax:0519-88226808  "},//����
	{" "},//��ҳ
};
//2.11���Ӿ�Ե1GУ׼��
//2.12�޸�ͨѶЭ��ѡ��bug
//==========================================================
////����ֵС����̶�(0-3: xxxx xxx.x xx.xx x.xxx)
const u8 ParameterDotTab[][PARAMETER_MENU_MAX]=
{
	{0,0,2,2,1,1,2,0},//ACW
	{0,0,2,2,1,1,2,0},//DCW
	{0,0,0,0,1,1,0,0},//IR
	{0,2,0,0,1,1,0,0},//GND
};
//==========================================================
//�����˵���
enum ParameterMenuEnum
{	
	PARAMETER_MENU_RANGE ,
	PARAMETER_MENU_BEEP ,
	PARAMETER_MENU_CLEAR ,
	PARAMETER_MENU_TRIG ,
	PARAMETER_MENU_UART ,
};

//==========================================================
//ϵͳ�˵���
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
	Lcd_SetAddr();//��������
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
			if(GetSystemMessage()==MSG_RAMP)//����
			{
				Disp_Str((u8 *)W_TEST_DISP[1]);
			}else//����
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
			if(run_stemp==0)//��һ��
			{
				Disp_Str((u8 *)I_TEST_DISP[1]);
				LcdAddr.x=6;LcdAddr.y=1;
				Disp_StrAt((u8 *)"DC");
				LcdAddr.x=14;LcdAddr.y=1;
				Disp_StrAt((u8*)"M");
				Lcd_WriteData(OHM);
			}else//�ڶ���
			{
				if(GetSystemMessage()==MSG_RAMP)//����
				{
					Disp_Str((u8 *)W_TEST_DISP[1]);
				}else//����
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
			if(run_stemp==0)//��һ��
			{
				if(GetSystemMessage()==MSG_RAMP)//����
				{
					Disp_Str((u8 *)W_TEST_DISP[1]);
				}else//����
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
			
			}else//�ڶ���
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
	
	
	//Lcd_SetAddr();//��������
	//Disp_Product_Model();//��ʾ��Ʒ�ͺ�
	
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
//�������ƣ�InitGlobalValue
//�������ܣ���ʼ��ȫ�ֱ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 15:33
//��ע˵������
//==========================================================
void InitGlobalValue(void)
{
	u16 len;
	u8 * buf;
						 
	buf=(u8 *)&SaveData;//�����׵�ַ
	len=sizeof(Save_TypeDef);
	while(len--)
	{
		*buf=0;//���
		buf++;
	}
	F_Password=FALSE;//������Ч��־	
}
//==========================================================
//�������ƣ�Parameter_valuecomp
//�������ܣ���ʼ��ֵ�ñȽ�
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 15:33
//��ע˵������
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
//�������ƣ�Hex_Format
//�������ܣ���ʽ������ֵ��DispBuf
//��ڲ�����������С��λ������ֵλ������ʾ��
//���ڲ�������
//�������ڣ�2014.12.15
//�޸����ڣ�2015.01.14 13:12
//��ע˵����dot=0-XXXXX XXXX.X XXX.XX XX.XXX X.XXXX-Dot=4
//ע��������5λ��
//==========================================================
void Hex_Format(u16 dat , u8 Dot , u8 len , bool dispzero)
{
	u8 i,j;

	if(len>5)len=5;//��󳤶�5
	if(len==0)len=1;
	if(Dot>4)Dot=4;//���С����4
	if(Dot>len)Dot=len;

	for(i=0;i<sizeof(DispBuf);i++)	//��ջ�����
		DispBuf[i]=' ';

	for(i=len;i>0;i--)	//����ת��
	{
		DispBuf[i-1] = dat%10 + '0';//תΪASCII
		dat/=10;
	}
	
	if(Dot)//��С����
	{
		j=len;
		i=Dot;//ȡС����λ��
		while(i--)
		{
			DispBuf[j]=DispBuf[j-1];
			j--;
		}
		DispBuf[j]='.';//����С����
	}

	if(dispzero==FALSE)//����ʾ��Ч��
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
	for(i=len;i<sizeof(DispBuf);i++)//ĩβ��������'\0'
	{
		DispBuf[i]=0;
	}			
}
//==========================================================
//�������ƣ�Disp_Product_Model
//�������ܣ���ʾ��Ʒ�ͺ�
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.27
//�޸����ڣ�2015.10.27 16:00
//��ע˵������
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
//�������ƣ�Disp_Software_Version
//�������ܣ���ʾ����汾
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.27
//�޸����ڣ�2015.10.27 16:00
//��ע˵������
//==========================================================
void Disp_Software_Version(void)
{
//	Disp_Str("Ver:");
//	memset(DispBuf,'\0',sizeof(DispBuf));//���
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
//�������ƣ�Disp_Compile_Date
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.27
//�޸����ڣ�2015.10.27 16:00
//��ע˵������
//==========================================================
void Disp_Compile_Date(void)
{
//	Disp_Str("Comp:");
//	Disp_Str(__DATE__ );//��ʾ��������-Mmm dd yyyy
	Disp_Str(__DATE__);//��ʾ��������-mm/dd/yy
}

//==========================================================
//�������ƣ�Disp_PowerOn_Menu
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.26
//�޸����ڣ�2015.10.26 15:00
//��ע˵������
//==========================================================
void Disp_PowerOn_Menu(void)
{
	//��һ��
	LcdAddr.x=0;LcdAddr.y=0;
	Lcd_SetAddr();//��������
	Disp_Product_Model();//��ʾ��Ʒ�ͺ�
	
	//�ڶ���
	LcdAddr.x=0;LcdAddr.y=1;
	Lcd_SetAddr();//��������
	Disp_Software_Version();//��ʾ����汾
	
//	LcdAddr.x=11;LcdAddr.y=1;
//	Lcd_SetAddr();//��������
//	Disp_Compile_Date();//��ʾ��������
}
//==========================================================
//�������ƣ�Number_Setup
//�������ܣ���ֵ�����ô���
//��ڲ�����NumBox_TypeDef
//���ڲ�������ֵ
//�������ڣ�2015.01.07
//�޸����ڣ�2015.08.19 13:53
//��ע˵������
//==========================================================
//u8 Number_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;
//	u8 count;//����������
//	u8 current;//��ǰ����λ
//	bool blink;//��ʾ��˸��־
//	LcdAddr_TypeDef addr;//��ʾ��ַ����

////	//���ޡ����ޡ�С������
////	if(pt->Num > NumBox.Max)
////		pt->Num=NumBox.Max;
////	if(pt->Num < NumBox.Min)
////		pt->Num=NumBox.Min;
////	if(pt->Dot != NumBox.Dot)
////		pt->Dot=NumBox.Dot;

//	addr.x=LcdAddr.x;//��ʾ��ַ����
//	addr.y=LcdAddr.y;
////	SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����
//	
//	count=0;//����������
//	blink=TRUE;//��ʾ��˸��־
//	if(pt->Dot==0)
//		current=3;//��ǰ����λ
//	else
//		current=4;//��ǰ����λ

//	while(1)
//	{
//		LcdAddr.x=addr.x;//��ʾ��ַ
//		LcdAddr.y=addr.y;
//		Hex_Format(pt->Num,pt->Dot,4,TRUE);//��ֵ��ʽ����4λ��ֵ

////		if( GetSoftTimerOut(DISP_SOFTTIMER) )//�ȴ���ʱ����
////		{
////			SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����
////			blink=!blink;
////		}
//		if(blink)//�ȴ���ʱ����
////		{
////			len=DispBuf[current];//����
////			DispBuf[current]=CURSORCHAR;
////			Disp_Str(DispBuf,1);//��ʾ�˵�ֵ
////			DispBuf[current]=len;//�ָ�
//////			if(pt->Dot==0)
//////				len=4;//��λ��
//////			else
//////				len=5;//��λ��
//////			while(len--)
//////				Disp_Str(" ",0);
////		}
////		else
//		{
//			Disp_Str(DispBuf,1);//��ʾ�˵�ֵ
//		}

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
////				count=0;//����������
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//С����̶�
////					current++;
////				if(NumBox.Dot!=0)//��С����
////					current%=5;//�5λ
////				else
////					current%=4;//�4λ
////				return(KEY_SET);
//				break;

//			case KEY_DOWN:		//�¼�
//				blink=TRUE;//��ʾ��˸��־
//				count=0;//����������
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//������
//				}
//				break;

//			case L_KEY_DOWN:	//�����¼�
//				blink=TRUE;//��ʾ��˸��־
//				count++;//����������
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				if(count>28)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>19)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//����������
//				{
//					if(len>0)len--;
//				}
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//������
//				}
//				break;

//			case KEY_UP:	//�ϼ�
//				blink=TRUE;//��ʾ��˸��־
//				count=0;//����������
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
//					pt->Num=pt->Min;
////					Beep_Two();//������
//				}
//				break;

//			case L_KEY_UP:	//�����ϼ�
//				blink=TRUE;//��ʾ��˸��־
//				count++;//����������
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				if(count>28)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>19)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//����������
//				{
//					if(len>0)len--;
//				}
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
//					pt->Num=pt->Min;
////					Beep_Two();//������
//				}
//				break;

//			case KEY_LEFT:		//���
////			case L_KEY_LEFT:	//�������
////				count=0;//����������
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//С����̶�
////					current++;
////				if(NumBox.Dot!=0)//��С����
////					current%=5;//�5λ
////				else
////					current%=4;//�4λ
//				return(KEY_LEFT);
//				break;

//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
////				count=0;//����������
////				blink=TRUE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
////				current++;
////				if(DispBuf[current]=='.')//С����̶�
////					current++;
////				if(NumBox.Dot!=0)//��С����
////					current%=5;//�5λ
////				else
////					current%=4;//�4λ
//				return(KEY_RIGHT);
//				break;

//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				return(KEY_ENTER);
//				break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				return(KEY_START);
//				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				return(KEY_RESET);
//				break;

//			default:
//				if(Keyboard.continuance!=TRUE) //��������
//					count=0;//����������
//				break;
//		}
//	}
//}

//==========================================================
//�������ƣ�ListBox_Setup
//�������ܣ��б������
//��ڲ�������
//���ڲ�������ֵ
//�������ڣ�2015.01.08
//�޸����ڣ�2015.08.19 13:48
//��ע˵�����б�����ⳤ�ȹ̶�Ϊ8���ַ�
//==========================================================
//u8 ListBox_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;//�������ַ�����
//	bool blink=TRUE;//��˸��־
//	LcdAddr_TypeDef addr;

//	len=strlen(pt->Title);//�������ַ�����
//	addr.x=LcdAddr.x;//��ʾ��ַ����
//	addr.y=LcdAddr.y;
////	SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����
//	
//	while(1)
//	{
//		LcdAddr.x=addr.x;//��ʾ��ַ
//		LcdAddr.y=addr.y;
////		if( GetSoftTimerOut(DISP_SOFTTIMER) )//�ȴ���ʱ����
////		{
////			SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����
////			blink=!blink;
////		}
//		if(blink)
////		{
////			key=len;//�б�����ⳤ��
////			while(key--)
////				Disp_Str(" ",0);//��ʾ�ո�;
////		}
////		else
//			Disp_Str(pt->Title+(len+1)*pt->Num,1);//��ʾ�˵�ֵ

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
//				return(KEY_SET);
//				break;

//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				blink=TRUE;
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				if(pt->Num>pt->Min)
//					pt->Num--;
//				else
//				{
//					pt->Num=pt->Max;
////					Beep_Two();//������
//				}
//				break;

//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				blink=TRUE;
////				blink=FALSE;
////				SetSoftTimer(DISP_SOFTTIMER,BLINK_TICKS_SOFTTIMER);//������˸��ʱ����(1000/3=333mS)
//				pt->Num++;
//				if(pt->Num>pt->Max)
//				{
//					pt->Num=pt->Min;
////					Beep_Two();//������
//				}
//				break;

//			case KEY_LEFT:		//���
////			case L_KEY_LEFT:	//�������
//				return(KEY_LEFT);
////				break;

//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				return(KEY_RIGHT);
//				break;

//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				return(KEY_ENTER);
//				break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				return(KEY_START);
//				break;

//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				return(KEY_RESET);
//				break;

//			default:
//				break;
//		}
//	}
//}

//==========================================================
//�������ƣ�Disp_Frame
//�������ܣ���ʾ������
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.12.26
//�޸����ڣ�2015.08.18 16:30
//��ע˵������������
//==========================================================
//void Disp_Frame( void )
//{
//	Lcd_Draw_Line(9,0,LCD_ADDR_Y_MAX);//����,�߶�ΪLCD_ADDR_Y_MAX
//	Lcd_Draw_Line(0,0,LCD_ADDR_X_MAX);//����,����ΪLCD_ADDR_X_MAX
//	Lcd_Draw_Line(0,32*1,9);//����
//	Lcd_Draw_Line(0,32*2,9);//����
//	Lcd_Draw_Line(0,32*3,9);//����
//	Lcd_Draw_Line(0,127,LCD_ADDR_X_MAX);//����
//}

//==========================================================
//�������ƣ�Disp_Boot_Number
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.13
//�޸����ڣ�2014.11.13 12:42
//��ע˵������
//==========================================================
//void Disp_Boot_Number(void)
//{
//	Disp_Str("��������: ",0);
//	Hex_Format(SaveData.Factory.BootNum,0,4,TRUE);//��ֵ��ʽ��
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//�������ƣ�Disp_Software_Version
//�������ܣ���ʾ����汾
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.01.09 15:13
//��ע˵������
//==========================================================
//void Disp_Software_Version(void)
//{
//	Disp_Str("����汾: ",0);
//	memset(DispBuf,'\0',sizeof(DispBuf));//���
//	DispBuf[0]='0'+((SOFTWARE_VERSION&0xf0)>>4);
//	DispBuf[1]='0'+((SOFTWARE_VERSION&0x0f));
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//�������ƣ�Disp_Hardware_Version
//�������ܣ���ʾӲ���汾
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.01.09 15:13
//��ע˵������
//==========================================================
//void Disp_Hardware_Version(void)
//{
//	Disp_Str("Ӳ���汾: ",0);
//	memset(DispBuf,'\0',sizeof(DispBuf));//���
//	DispBuf[0]='0'+((HARDWARE_VERSION&0xf0)>>4);
//	DispBuf[1]='0'+((HARDWARE_VERSION&0x0f));
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//�������ƣ�Disp_Compile_Date
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.01.09 15:13
//��ע˵������
//==========================================================
//void Disp_Compile_Date(void)
//{
//	Disp_Str("��������: ",0);
////	Disp_Str(__DATE__ ,0);//��ʾ��������-Mmm dd yyyy
//	Disp_Str(__DATE2__,0);//��ʾ��������-mm/dd/yy
//}

//==========================================================
//�������ƣ�Disp_Product_Model
//�������ܣ���ʾ��Ʒ�ͺ�
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.01.09 15:13
//��ע˵������
//==========================================================
//void Disp_Product_Model(void)
//{
//	Disp_Str("YD9860B �ۺϰ���",0);
//}

//==========================================================
//�������ƣ�Disp_Company_Name
//�������ܣ���ʾ��˾����
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.01.09 15:13
//��ע˵������
//==========================================================
//void Disp_Company_Name(void)
//{
//	Disp_Str("���������ӵ������޹�˾",0);//��������
//}
//==========================================================
//�������ƣ�Disp_Company_Telephone
//�������ܣ���ʾ���̵绰
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.09.06 10:07
//��ע˵������
//==========================================================
//void Disp_Company_Telephone(void)
//{
//	Disp_Str("�绰: ",0);
//	Disp_Str("0519-88226706 88226707",0);//�绰
//}

//==========================================================
//�������ƣ�Disp_Company_Http
//�������ܣ���ʾ������ҳ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.09.06 10:07
//��ע˵������
//==========================================================
//void Disp_Company_Http(void)
//{
//	Disp_Str("��ҳ: ",0);
//	Disp_Str("www.cz-yangzi.com",0);//��ҳ
//}

//==========================================================
//�������ƣ�Disp_Chip_ID
//�������ܣ���ʾоƬID��
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.13
//�޸����ڣ�2014.11.13 13:31
//��ע˵������
//==========================================================
//STC12ϵ��CPU�ڲ�ID���׵�ַ����(F1-F7ΪID��)
#define MCU_ID_ADDR (0xF1)
//==========================================================
//void Disp_Chip_ID(void)
//{
//	u8 i;
//	u8 dat;
//	u8 idata *addr;

//	Disp_Str("������: ",0);
////	memset(DispBuf,'\0',sizeof(DispBuf));//���
//	addr=MCU_ID_ADDR;//ID���׵�ַ
//	i=7;
//	while(i--)
//	{
//		dat=(*addr&0xf0)>>4;//ID�Ÿ�4λ
//		DispBuf[0]=(dat>9)?(dat-0x0a+'A'):(dat+'0');
//		dat=(*addr&0x0f);//ID�ŵ�4λ
//		DispBuf[1]=(dat>9)?(dat-0x0a+'A'):(dat+'0');
//		if(i!=0)
//			DispBuf[2]='-';
//		else
//			DispBuf[2]=0;
//		DispBuf[3]=0;
//		Disp_Str(DispBuf,0);//��ʾ
//		addr++;
//	}
//}
//==========================================================
////�����кŵ���ʾ�̶�ֵ
//void Disp_Chip_ID(void)
//{
//	u8 i=7;
//	u8 dat=0;
//
//	Disp_Str("������: ",0);
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
//�������ƣ�Disp_Product_ID
//�������ܣ���ʾ�������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.08.19 10:03
//��ע˵������
//==========================================================
//void Disp_Product_ID(void)
//{
//	Hex_Format(SaveData.Factory.ProductId,0,4,1);//���ݸ�ʽ����DispBuf
//	Disp_Str("�������: ",0);
//	Disp_Str(DispBuf,0);
//}

//==========================================================
//�������ƣ�Disp_PowerOn_Menu
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.12.26
//�޸����ڣ�2015.08.18 09:38
//��ע˵������
//==========================================================
//void Disp_PowerOn_Menu(void)
//{
////	Disp_Kjjm();//��ʾ��������(����ͼƬ��ʾ)

//	LcdAddr.x=7;LcdAddr.y=15;
//	Disp_Product_Model();//��ʾ��Ʒ�ͺ�

//	LcdAddr.x=9;LcdAddr.y=55;
//	Disp_Software_Version();//��ʾ����汾
//	
//	LcdAddr.x=4;LcdAddr.y=95;
//	Disp_Company_Name();//��ʾ��������
//}

//==========================================================
//�������ƣ�Disp_Group
//�������ܣ���ʾ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.05
//�޸����ڣ�2015.01.05 13:18
//��ע˵������
//==========================================================
//void Disp_Group(u8 highlight)
//{
////	Hex_Format(SaveData.Group+1,0,1,0);//���ݸ�ʽ����DispBuf
//	Hex_Format(SaveData.Group+1,0,2,1);//���ݸ�ʽ����DispBuf
//	Disp_Str(DispBuf,highlight);//��ʾ
//	Disp_Str("��",highlight);//��ʾ
//}

//==========================================================
//�������ƣ�Disp_Parameter_Value
//�������ܣ���ʾ����ֵ
//��ڲ�����step:�ڼ����裻index:�ڼ��������highlight:���������ʾ
//���ڲ�������
//�������ڣ�2015.01.05
//�޸����ڣ�2015.09.06 09:14
//��ע˵������ֵλ��+С����+��λ�ĳ��ȹ̶�Ϊ7���ַ�
//==========================================================
//void Disp_Parameter_Value(u8 step ,u8 index, u8 highlight)
//{
//	u8 item;
//	
//	step%=STEP_MAX;//�����
//	index%=PARAMETER_MENU_MAX;//��������
//	item=SaveData.Setup[step].Item;//��Ŀ
//		
//	switch(index)
//	{
//		case PARAMETER_MENU_ITEM://��Ŀ
//			Disp_Str(&ItemTab[item],highlight);//��ʾ��Ŀ
//			break;

//		case PARAMETER_MENU_OUTPUT://���
//			Hex_Format(SaveData.Setup[step].Output,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//					Disp_Str("V ",0);//��ʾV
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("A ",0);//��ʾA
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[step][item]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;
//		
//		case PARAMETER_MENU_LIMITH://����
//			Hex_Format(SaveData.Setup[step].High,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//��ʾ
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;

//		case PARAMETER_MENU_LIMITL://����
//			Hex_Format(SaveData.Setup[step].Low,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//��ʾ
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;

//		case PARAMETER_MENU_TESTTIME:
//			Hex_Format(SaveData.Setup[step].TestTime,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//				case ITEM_GND:
//					Disp_Str("s ",0);//��ʾ
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;
//		
//		case PARAMETER_MENU_RAMPDELAY:
//			Hex_Format(SaveData.Setup[step].RampDelay,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//				case ITEM_IR:
//				case ITEM_GND:
//					Disp_Str("s ",0);//��ʾ
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;

//		case PARAMETER_MENU_ZERO:
//			Hex_Format(SaveData.Setup[step].Zero,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			switch(item)//����Ŀ��ʾ��λ
//			{
//				case ITEM_ACW:
//				case ITEM_DCW:
//					Disp_Str("mA",0);//��ʾ
//					break;
//		
//				case ITEM_IR:
//					Disp_Str("M",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				case ITEM_GND:
//					Disp_Str("m",0);//��ʾ
//					Disp_Char(OHM,0);//��ʾ��
//					break;
//				
//				default:
//					Disp_Str("  ",0);//��ʾ
//					break;
//			}
//			if(ParameterDotTab[item][index]==0)//��С���㲹1λ�ո�
//				Disp_Str(" ",0);//��ʾ
//			break;

//		case PARAMETER_MENU_ARC:
//			Hex_Format(SaveData.Setup[step].Arc,ParameterDotTab[item][index],4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,highlight);//��ʾ
//			Disp_Str("   ",0);//��ʾ3���ո���С����1���޵�λ2
//			break;

//		default:
//			break;
//	}
//}

//==========================================================
//�������ƣ�Disp_SysMessage
//�������ܣ���ʾϵͳ��Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.10.15
//�޸����ڣ�2014.10.15 15:17
//��ע˵������
//==========================================================
void Disp_SysMessage(void)
{
//	if(SaveData.Setup[SaveData.Group].Group_Item>3)
//		SaveData.Setup[SaveData.Group].Group_Item=0;
//	Disp_StrAt((u8 *)GROUP_DISP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//��ʾϵͳ��Ϣ
	//switch()
	Disp_StrAt((u8 *)MsgTab[GetSystemMessage()]);//��ʾϵͳ��Ϣ
}

//==========================================================
//�������ƣ�Disp_Idle_Menu
//�������ܣ���ʾ����˵�
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.26
//�޸����ڣ�2015.10.29 10:27
//��ע˵������
//==========================================================
void Disp_Idle_Menu(void)
{
	//��һ��
	if(SaveData.Setup.Group_Item>3)
		SaveData.Setup.Group_Item=0;
	LcdAddr.x=MSG_ADDR_X;LcdAddr.y=0;
	Lcd_SetAddr();//��������
	Disp_StrAt((u8 *)GROUP_ITEM[SaveData.Setup.Group_Item]);//��ʾϵͳ��Ϣ
	//Disp_SysMessage();//��ʾϵͳ��Ϣ
	LcdAddr.x=GROUP_ADDR_X;LcdAddr.y=0;
	Hex_Format(SaveData.Group+1,0,1,TRUE);//��ʾ��ǰ���
	Disp_StrAt((u8*)"M");
	Disp_Str(DispBuf);
//	if(SaveData.Group==0)
//		SaveData.Group=1;
	if(SaveData.Setup.Group_Item>1)
		Disp_Str((u8*)"_");
	else
		Disp_Str((u8*)" ");
	LcdAddr.x=TIME_ADDR_X;
	if(SaveData.Setup.Group_Item==3||SaveData.Setup.Group_Item==1)//��Ե����
		Hex_Format((u16)SaveData.Setup.I_Delay,1,4,FALSE);//��ʾ����ʱ��
	else
		Hex_Format((u16)SaveData.Setup.TestTime,1,4,FALSE);//��ʾ����ʱ��
	Disp_StrAt(DispBuf);
	Disp_Str((u8*)"s");

	//�ڶ���
	LcdAddr.x=V_ADDR_X;LcdAddr.y=1;
	if(SaveData.Setup.Item==0)
	{
		if(SaveData.Setup.Output>600)
			SaveData.Setup.Output=600;
		
	
	}
	if(/*SaveData.Setup.Group_Item==3||*/SaveData.Setup.Group_Item==1)//��Ե����
	{
		Hex_Format((u16)SaveData.Setup.I_Volt,2,3,FALSE);//��ʾ����ʱ��
		SaveData.Setup.Item=1;
		
	}else if(SaveData.Setup.Group_Item==3){
		Hex_Format((u16)SaveData.Setup.I_Volt,2,3,FALSE);//��ʾ����ʱ��
	}
	else{
		Hex_Format((u16)SaveData.Setup.Output,2,3,FALSE);//��ʾ����ʱ��
	}
	Disp_StrAt(DispBuf);
	Disp_Str((u8*)"kV");
	
	memset(sendbuff,0,20);
	memcpy(sendbuff,DispBuf,4);
	strcat(sendbuff,"kV;");
	if(SaveData.Setup.Item==0 && SaveData.Setup.Group_Item != I_WSETUP)//AC ע��  ���õ�ʱ�� ��Ե����Ҫ�̶�ΪDC
		Disp_Str((u8*)"AC");
	else
		Disp_Str((u8*)"DC");
	
	
	if(SaveData.Setup.Group_Item==3||SaveData.Setup.Group_Item==1)//��Ե����
	{
		LcdAddr.x=RES_ADDR_X+1;
		Hex_Format((u16)SaveData.Setup.I_High,0,4,FALSE);//��ʾ���޵���
		Disp_StrAt(DispBuf);
		Disp_Str((u8*)"M");
		Lcd_WriteData(OHM);
		strcat(sendbuff,(char*)DispBuf);
		strcat(sendbuff,"M��;");
		
	}
	else
	{
		LcdAddr.x=RES_ADDR_X;
		Hex_Format((u16)SaveData.Setup.High,2,4,FALSE);//��ʾ����ʱ��
		Disp_StrAt(DispBuf);
		Disp_Str((u8*)"mA");
		strcat(sendbuff,(char*)DispBuf);
		strcat(sendbuff,"mA;");
	}
		

}
//==========================================================
//�������ƣ�Check_Parameter_Limit
//�������ܣ�����ֵ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28 
//�޸����ڣ�2015.10.28 13:50
//��ע˵�������ޡ����޼��,	L<=x<=H
//==========================================================
//void Check_Parameter_Limit(void)
//{
//	u8 i;
//	u8 *pt;

//	pt=(u8* )&SaveData.Parameter;
//	for(i=0;i<PARAMETER_MENU_MAX;i++)//��5��
//	{
//		if(*pt>ParameterLimit[i][0])//Max
//			*pt= ParameterLimit[i][0];//Max
//		if(*pt<ParameterLimit[i][1])//Min
//			*pt=ParameterLimit[i][1];//Min
//		pt++;
//	}
//}
//==========================================================
//�������ƣ�Range_Control
//�������ܣ����̿���
//��ڲ�����u8 dat
//���ڲ�������
//�������ڣ�2014.09.25
//�޸����ڣ�2015.09.04 15:35
//��ע˵��������(0-4) 100 1k 10k 100k 1M
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
//			//�����ڲ��Ŵ�8��
//		break;
//		case 6:
//			//�����ڲ��Ŵ�64��
//		break;
//		case 7:
//			//�����ڲ��Ŵ�128��
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
//�������ƣ�Disp_Setup_Menu
//�������ܣ���ʾ���ò˵�
//��ڲ�����index:�ڼ���
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 13:25
//��ע˵������
//==========================================================
void Disp_Setup_Menu(u8 index)
{
	//��һ��
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8*)&SetupMenu[index%SETUP_MENU_MAX][0]);
	
	//�ڶ���
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8*)EnterTab);//��ʾȷ����ʾ
}
//==========================================================
//�������ƣ�Disp_Parameter_Value
//�������ܣ���ʾ����
//��ڲ�����index:�ڼ������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 11:25
//��ע˵������
//==========================================================
//void Disp_Parameter_Value(u8 index)
//{
//	index%=PARAMETER_MENU_MAX;//���ϵͳ��
//	
//	switch(index)
//	{
//		case PARAMETER_MENU_RANGE://����ģʽ
////			if(SaveData.Parameter.Range>7)
////				SaveData.Parameter.Range=0;
//			Disp_Str((u8*)&RangeTab[SaveData.Parameter.Range]);
//			break;

//		case PARAMETER_MENU_BEEP://Ѷ��ģʽ
////			if(SaveData.Parameter.Beep>3)
////				SaveData.Parameter.Beep=0;
//			Disp_Str((u8*)&BeepTab[SaveData.Parameter.Beep]);
//			break;

//		case PARAMETER_MENU_CLEAR://���㿪��
////			if(SaveData.Parameter.ClrOn>2)
////				SaveData.Parameter.ClrOn=0;
//			Disp_Str((u8 *)&SwitchTab[SaveData.Parameter.ClrOn]);
//			break;

//		case PARAMETER_MENU_TRIG://�ⲿ��������
////			if(SaveData.Parameter.ExTrig>2)
////				SaveData.Parameter.ExTrig=0;
//			Disp_Str((u8*)&SwitchTab[SaveData.Parameter.ExTrig]);
//			break;

//		case PARAMETER_MENU_UART://���ڿ���
////			if(SaveData.Parameter.UartOn>2)
////				SaveData.Parameter.UartOn=0;
//			Disp_Str((u8*)&SwitchTab[SaveData.Parameter.UartOn]);
//			break;

//		default:
//			break;
//	}
//}
//==========================================================
//�������ƣ�ListBox_Setup
//�������ܣ��б������
//��ڲ�������
//���ڲ�������ֵ
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 09:50
//��ע˵�����������ַ�����,TITLE_LEN_MAX=8
//==========================================================
u8 ListBox_Setup(NumBox_TypeDef * pt)
{
	u8 key;
	u8 len;
	bool blink;//��˸��־
	LcdAddr_TypeDef addr;

	blink=TRUE;//��˸��־

	addr.x=LcdAddr.x;//��ʾ��ַ����
	addr.y=LcdAddr.y;

	len=strlen((const char *)(pt->Title));//�������ַ�����
	len++;//������
	if(len>TITLE_LEN_MAX)len=TITLE_LEN_MAX;//��󳤶��޶�
	
	while(1)
	{
		if(blink)
		{
			LcdAddr.x=addr.x;//��ʾ��ַ
			LcdAddr.y=addr.y;
			Disp_StrAt((u8*)(pt->Title+len*pt->Num));//��ʾ�˵�ֵ
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//���ü�
			case L_KEY_SET:	//�������ü�
				return(KEY_SET);
				//break;

			case KEY_DOWN:		//�¼�
			case L_KEY_DOWN:	//�����¼�
				blink=TRUE;
				if(pt->Num>pt->Min)
					pt->Num--;
				else
				{
					pt->Num=pt->Min;
					Beep_Two();//������
				}
				break;

			case KEY_UP:	//�ϼ�
			case L_KEY_UP:	//�����ϼ�
				blink=TRUE;
				pt->Num++;
				if(pt->Num>pt->Max)
				{
					pt->Num=pt->Max;
					Beep_Two();//������
				}
				break;

			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				return(KEY_ENTER);
				//break;

			case KEY_START:		//������
			case L_KEY_START:	//����������
				//return(KEY_START);
				//break;

			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				return(KEY_RESET);
				//break;

			default:
				break;
		}
	}
}
//==========================================================
//�������ƣ�Disp_Parameter_Menu
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 13:20
//��ע˵������
//==========================================================
void Disp_Parameter_Menu(u8 index)
{
	//��һ��
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8*)ParameterTab[index]);//��ʾ�����˵�
//	Disp_Parameter_Value(index);//��ʾ����ֵ
	
	//�ڶ���
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8*)SelectTab);//��ʾѡ����ʾ
}

//==========================================================
//�������ƣ�Parameter_Setup
//�������ܣ������˵����ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 11:49
//��ע˵������
//==========================================================
//void Parameter_Setup(void)
//{
//	u8 *pt;
//	u8 key;
//	u8 index;
//	bool f_disp;

//	index=0;//��һ��
//	f_disp=TRUE;//��ʾ

//	while(GetSystemStatus()==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//��ʾ����
//		{
//			f_disp=FALSE;
//			Disp_Parameter_Menu(index);//��ʾ����

//			//ȡ����ֵ��������
//			pt=(u8* )&SaveData.Parameter + index;
//			NumBox.Num=*pt;
//			NumBox.Max=ParameterLimit[index][0];//Max
//			NumBox.Min=ParameterLimit[index][1];//Min
//			NumBox.Dot=0;//Dot
//		
//			//��ʾ��ַ	  SaveData.Parameter.Range
//			LcdAddr.x=12;LcdAddr.y=0;
//	
//			switch(index)//��ֵ���ô���
//			{
//				case PARAMETER_MENU_RANGE://����ģʽ
//					NumBox.Title=(u8*)RangeTab[0];
//					key=ListBox_Setup(&NumBox);//�б������
//					break;
//		
//				case PARAMETER_MENU_BEEP://Ѷ��ģʽ
//					NumBox.Title=(u8*)BeepTab[0];
//					key=ListBox_Setup(&NumBox);//�б������
//					break;
//		
//				case PARAMETER_MENU_CLEAR://���㿪��
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//�б������
//					break;
//		
//				case PARAMETER_MENU_TRIG://�ⲿ��������
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//�б������
//					break;
//	
//				case PARAMETER_MENU_UART://���ڿ���
//					NumBox.Title=(u8*)SwitchTab[0];
//					key=ListBox_Setup(&NumBox);//�б������
//					if(SaveData.Parameter.UartOn==1)
//						;//Start_Uart();//���ڿ���
//					else
//						;//Stop_Uart();//���ڹر�
//					break;
//	
//				default:
//					break;
//			}
//	
//			*pt=NumBox.Num;//��������ֵ
////			Check_Parameter_Limit();//ֵ���
//	
//			//��������
//			switch(key)
//			{
//				case KEY_SET:	//���ü�
//				case L_KEY_SET:	//�������ü�
//					f_disp=TRUE;//��ʾ
//					index++;
//					if(index>=PARAMETER_MENU_MAX)
//						index=0;
//					break;

//				case KEY_UP:	//�ϼ�
//				case L_KEY_UP:	//�����ϼ�
//					break;
//	
//				case KEY_DOWN:		//�¼�
//				case L_KEY_DOWN:	//�����¼�
//					break;
//	
//				case KEY_ENTER:		//ȷ�ϼ�
////				case L_KEY_ENTER:	//����ȷ�ϼ�
//					//SaveParameter();//�������
//					SetSystemStatus(SYS_STATUS_SETUP);//����״̬
//					if(SaveData.Parameter.Range)
//					Range_Control(SaveData.Parameter.Range);
//					Store_set_flash();
//					break;
//		
//				case KEY_START:		//������
//				case L_KEY_START:	//����������
//					SetSystemStatus(SYS_STATUS_TEST);//��������״̬
//					break;
//		
//				case KEY_RESET:		//��λ��
//				case L_KEY_RESET:	//������λ��
//					SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//					break;
//				
//				default:
//					break;
//			}
//		}
//	}
//}
//==========================================================
//�������ƣ�Disp_System_Value
//�������ܣ���ʾϵͳֵ
//��ڲ�����index:�ڼ������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 14:20
//��ע˵������
//==========================================================
void Disp_System_Value(u8 index)
{
	index%=SYSTEM_MENU_MAX;//�����
	switch(index)
	{
		
		case SYSTEM_MENU_VOUT ://�����ѹ����
//			Hex_Format(SaveData.System.Vol_Out,0,4,TRUE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);//��ʾ
			Disp_Char(' ');
			Disp_Char('V');
			Disp_Char(' ');
			break;
		case SYSTEM_MENU_Ttime://����ʱ������
//			Hex_Format(SaveData.System.Set_Time,1,4,TRUE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);//��ʾ
			Disp_Char(' ');
			Disp_Char('s');
			break;
		case SYSTEM_MENU_RH://����
//			Hex_Format(SaveData.System.Res_Hi,0,4,TRUE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);//��ʾ
			Disp_Char(' ');
			Disp_Char('M');
			Disp_Char(OHM);
			break;

		case SYSTEM_MENU_RL://����
//			Hex_Format(SaveData.System.Res_Lo,0,4,TRUE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);//��ʾ
			Disp_Char(' ');
			Disp_Char('M');
			Disp_Char(OHM);
			break;
	
	

		default:
			break;
	}
}

//==========================================================
//�������ƣ�Disp_System_Menu
//�������ܣ���ʾϵͳ����
//��ڲ�����index:�ڼ������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 14:23
//��ע˵������
//==========================================================
void Disp_System_Menu(u8 index)
{
	//��һ��
	LcdAddr.x=0;LcdAddr.y=0;
	switch(index)
	{
		case 0:
	
		Disp_StrAt((u8*)"Memory=         ");//��ʾ�˵�
		//Hex_Format(SaveData.Group,0,1,FALSE);
		//LcdAddr.x=10;LcdAddr.y=0;
		//Disp_StrAt(DispBuf);
		
		LcdAddr.x=0;LcdAddr.y=1;
		Disp_StrAt((u8*)"Range:1-9      ");//��ʾ��ֵ��Χ
		break;
		case 1:
	 
		Disp_StrAt((u8*)"Test  =        ");//��ʾ�˵�
		//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
		//LcdAddr.x=10;LcdAddr.y=0;
		//Disp_StrAt((u8*)GROUP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//��ʾ��Ŀ
		
		LcdAddr.x=0;LcdAddr.y=1;
		Disp_StrAt((u8*)I_Sel_Tab[0]);//��ʾ��ֵ��Χ
		break;
		case 2:
	
		switch(SaveData.Setup.Group_Item)//ѡ�������Ŀ
		{
			case I_SETUP:
				Disp_StrAt((u8*)I_SET[index-2]);//��ʾ�˵�
				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
				//LcdAddr.x=10;LcdAddr.y=0;
				//Disp_StrAt((u8*)GROUP_ITEM[SaveData.Setup[SaveData.Group].Group_Item]);//��ʾ��Ŀ
				
				LcdAddr.x=0;LcdAddr.y=1;
				Disp_StrAt((u8*)I_Sel_Tab[index-1]);//��ʾ��ֵ��Χ
				
				break;
			case W_SETUP://��ACDC
//				Disp_StrAt((u8*)W_SET[index-2]);//��ʾ�˵�
//				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
//				//LcdAddr.x=10;LcdAddr.y=0;
//				//Disp_StrAt((u8*)AC_DC_SET[SaveData.Setup[SaveData.Group].Item]);//��ʾ��Ŀ
//				
//				LcdAddr.x=0;LcdAddr.y=1;
//				Disp_StrAt((u8*)W_Sel_Tab[index-2]);//��ʾ��ֵ��Χ
//				break;
			case I_WSETUP://��ACDC
				
				//break;
			case W_ISETUP://��ACDC
				LcdAddr.x=0;LcdAddr.y=0;
				Disp_StrAt((u8*)W_SET[index-2]);//��ʾ�˵�
				//Hex_Format(SaveData.Setup[SaveData.Group].Group_Item,0,1,FALSE);
				//LcdAddr.x=10;LcdAddr.y=0;
				//Disp_StrAt((u8*)AC_DC_SET[SaveData.Setup[SaveData.Group].Item]);//��ʾ��Ŀ
				
				LcdAddr.x=0;LcdAddr.y=1;
				if(SaveData.Setup.Item==0)
					Disp_StrAt((u8*)W_Sel_Tab[index-2]);//��ʾ��ֵ��Χ
				else
					Disp_StrAt((u8*)I_WDC_Sel_Tab[index-2]);//��ʾ��ֵ��Χ
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
		switch(SaveData.Setup.Group_Item)//ѡ�������Ŀ
		{
			case I_SETUP:
				Disp_StrAt((u8*)I_SET[index-2]);//��ʾ�˵�
				
				
				LcdAddr.x=0;LcdAddr.y=1;
				Disp_StrAt((u8*)I_Sel_Tab[index-1]);//��ʾ��ֵ��Χ
				
				break;
			case W_SETUP://��ACDC
				
				
			case I_WSETUP://��ACDC
				
				
			case W_ISETUP://��ACDC
				Disp_StrAt((u8*)I_W_SET[index-2]);//��ʾ�˵�
				LcdAddr.x=0;LcdAddr.y=1;
				if(SaveData.Setup.Item==0)
					Disp_StrAt((u8*)W_Sel_Tab[index-1]);//��ʾ��ֵ��Χ
				else
					Disp_StrAt((u8*)I_WDC_Sel_Tab[index-1]);//��ʾ��ֵ��Χ
				break;
				
			default:
				
				break;

		}//
		break;
		case 10:
		case 11:
		case 12:
		case 13:
			Disp_StrAt((u8*)I_W_SET[index-2]);//��ʾ�˵�
			if(index==12||index==11)
			{
				LcdAddr.x=14;LcdAddr.y=0;
				Disp_CharAt(OHM);
				//Disp_StrAt((u8*));//��ʾ��ֵ��Χ
			}
			LcdAddr.x=0;LcdAddr.y=1;
			Disp_StrAt((u8*)I_W_Sel_Tab[index-1]);//��ʾ��ֵ��Χ
			break;
				
	

	
	}
	
	
	
	
}
//==========================================================
//�������ƣ�Number_Setup
//�������ܣ���ֵ�����ô���
//��ڲ�����NumBox_TypeDef
//���ڲ�������ֵ
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 09:44
//��ע˵������
//==========================================================
u8 Number_Setup(NumBox_TypeDef * pt)
{
	u8 key;
	u8 len;
	u8 count;//����������
	u8 current;//��ǰ����λ
	bool blink;//��ʾ��˸��־
	LcdAddr_TypeDef addr;//��ʾ��ַ����

	blink=TRUE;//��ʾ��˸��־

	addr.x=LcdAddr.x;//��ʾ��ַ����
	addr.y=LcdAddr.y;

	count=0;//����������
	if(pt->Dot==0)
		current=3;//��ǰ����λ
	else
		current=4;//��ǰ����λ

	while(1)
	{
		if(blink)//��ʾ
		{
			LcdAddr.x=addr.x;//��ʾ��ַ
			LcdAddr.y=addr.y;
			//if(in)
			Hex_Format(pt->Num,pt->Dot,pt->Len,FALSE);//��ֵ��ʽ����4λ��ֵ
			Disp_StrAt(DispBuf);//��ʾ�˵�ֵ
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//���ü�
			case L_KEY_SET:	//�������ü�
				return(KEY_SET);
				//break;

			case KEY_DOWN:		//�¼�
				blink=TRUE;//��ʾ��˸��־
				count=0;//����������
				if(current>(3-NumBox.Dot))//С����λ
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
								Beep_Two();//������
							}
						}
						
						if(pt->Min == 5)
						{
							if(pt->Num != 0)
							{
								pt->Num = 0;
							}else{
								Beep_Two();//������
							}
						}
					}else{
						
					}
				}
				break;

			case L_KEY_DOWN:	//�����¼�
				blink=TRUE;//��ʾ��˸��־
				count++;//����������
				if(current>(3-NumBox.Dot))//С����λ
					len=current-1;
				else
					len=current;
				if(count>28)//����������
				{
					if(len>0)len--;
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>19)//����������
				{
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>10)//����������
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
							Beep_Two();//������
						}
					}
					
					if(pt->Min == 5)
					{
						if(pt->Num != 0)
						{
							pt->Num = 0;
						}else{
							Beep_Two();//������
						}
					}
				}
				break;

			case KEY_UP:	//�ϼ�
				blink=TRUE;//��ʾ��˸��־
				count=0;//����������
				if(current>(3-NumBox.Dot))//С����λ
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
						Beep_Two();//������
					}
				}
				break;

			case L_KEY_UP:	//�����ϼ�
				blink=TRUE;//��ʾ��˸��־
				count++;//����������
				if(current>(3-NumBox.Dot))//С����λ
					len=current-1;
				else
					len=current;
				if(count>28)//����������
				{
					if(len>0)len--;
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>19)//����������
				{
					if(len>0)len--;
					if(len>0)len--;
				}
				else if(count>10)//����������
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
						Beep_Two();//������
					}
				}
				break;

			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				return(KEY_ENTER);
				//break;

			case KEY_START:		//������
			case L_KEY_START:	//����������
//				return(KEY_START);
				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				return(KEY_RESET);
//				break;

			default:
				if(Keyboard.continuance!=TRUE) //��������
					count=0;//����������
				break;
		}
	}
}

//==========================================================
//�������ƣ�Range_Changecomp
//�������ܣ�������Ի���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.26 
//�޸����ڣ�2015.10.29 13:35
//��ע˵������
//==========================================================
void Range_Changecomp(void)
{
	
//	bool f_disp=FALSE;//��ʾ��־
	bool f_upper=FALSE;//���̹�ѹ��־
	bool f_below=FALSE;//����Ƿѹ��־
	bool f_switch=FALSE;//�����л���־
	u8 i;
	//�����Զ�������?
	if(Test_value.Test_I>RANGR_LIMIT_HIGH)//������������
	{
		f_upper=TRUE;//���̹�ѹ��־
		f_below=FALSE;//����Ƿѹ��־
		for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
	}
	else if(Test_value.Test_I<RANGR_LIMIT_LOW)//������������
	{
		f_below=TRUE;//���̵�ѹ��־
		f_upper=FALSE;//����Ƿѹ��־
	}
	else
	{
		f_upper=FALSE;//���̹�ѹ��־
		f_below=FALSE;//����Ƿѹ��־
	}
	f_switch=FALSE;//�����л���־
	//f_switch=TRUE;
	
		if((Range>0)&&(f_upper==TRUE))//���̷�����ҵ�ѹ
		{
			Range--;
			f_switch=TRUE;//�����л���־
			for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
		}
		if((Range<RANGE_MAX)&&(f_below==TRUE))//���̷�����ҹ�ѹ
		{
			Range++;
			f_switch=TRUE;//�����л���־
			for(i=0;i<FIT_INUM;i++)
			i_buff[i]=0;
			ffit_data1=0;
			count_ffit=0;
		}
	
	if(f_switch==TRUE)//�����л���־
	{
		Range_Control(Range);//���̿���
		//Range_Control(2);
		
		delay_ms(50);//Ӳ����ʱ
	}
}
//==========================================================
//�������ƣ�Get_FFT
//�������ܣ��������ֵ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.08 
//�޸����ڣ�2015.08.27 14:43
//��ע˵��������Voltage
//==========================================================
void Get_FFT(void)
{
	float dat=0;
	u8 i;
	ffit_data1++;	
	//fft_flag=Range;
	//�����ж�  û�л�����ʱ�� ffit_data1������ Range
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
//	if(Voltage>AD_MAX)//���ADֵ�б�
//		Voltage=AD_MAX;
//
//	//У׼����
//	dat=Voltage*10;//�Ŵ�10��
//	dat*=Cal[0].Num;
//	dat/=Cal[0].NumAd;
//
//	//��������
//	if(dat%10>4)dat+=10;
//	dat/=10;
//	//Voltage=(u16)dat;Res.Real
//	Voltage=Res.Real;
//	//���ADֵ�б�
//	if(Current>AD_MAX)//���ADֵ�б�
//		Current=AD_MAX;
//
//	//У׼����
//	dat=Current*10;//�Ŵ�10��	
//	dat*=Cal[Range+1].Num;
//	dat/=Cal[Range+1].NumAd;
//
//	//��������
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
//�������ƣ�Read_Ad
//�������ܣ���ȡA/Dֵ
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.08 
//�޸����ڣ�2015.08.26 10:32
//��ע˵������
//==========================================================
//void Read_Ad(void)
//{
//	
//	//AD7705_write_Reg(0x11);//д��ͨ�żĴ���������Ϊд���üĴ���

////	AD7705_init(1);
//	Hex_Format(Test_value.Test_Time,1,4,TRUE);//��ʾʱ��
//	LcdAddr.x=TIM_ADDR_X;LcdAddr.y=0;
//	Disp_StrAt(DispBuf);//��ʾ����ֵ
//	Disp_StrAt((u8 *)" S");
//	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
//	{
//	}
//	//delay_ms(120);
////	//AD7705_write_Reg(0x44);//��У׼������Ϊ1��������ģ�����롢Ƭ�ڻ�������FSYNC��0
////	Test_value.Test_I=Read_Channel(1);//��ѹADֵ  channel1  ����
////	AD7705_init(0);
//	Hex_Format(Test_value.Test_Time,1,4,TRUE);//��ʾʱ��
//	LcdAddr.x=TIM_ADDR_X;LcdAddr.y=0;
//	Disp_StrAt(DispBuf);//��ʾ����ֵ
//	Disp_StrAt((u8 *)" S");
////	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
////	{
////	}
//	delay_ms(30);
////	Test_value.Test_v.Test_v=Read_Channel(0);//����ADֵ
//		
//	
//	
//}
//==========================================================
//�������ƣ�System_Setup
//�������ܣ�ϵͳ���ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 14:27
//��ע˵������
//==========================================================
void Step_Setup(void)
{
	u16 *pt;
	u8 key;
	u8 keymax;
	u8 index;
	bool f_disp;

	index=0;//�ӵ�һ�ʼ
	f_disp=TRUE;//��ʾ

	while(SystemStatus==SYS_STATUS_SETUP)
	{
		if(f_disp==TRUE)
		{
			f_disp=FALSE;
			switch(index)
			{
				case 0://�������
						pt=(u16*)(&SaveData.Group);
						NumBox.Num=*pt+1;
						NumBox.Max=9;//Max
						NumBox.Min=1;//Min
						NumBox.Dot=0;//Dot
						NumBox.Len=1;
					break;
				case 1://������Ŀ
						pt=(u16*)(&SaveData.Setup.Group_Item);
						NumBox.Title=(u8*)GROUP_DISP_ITEM[0];
						NumBox.Num=*pt;
						NumBox.Max=3;//Max
						NumBox.Min=0;//Min
						NumBox.Dot=0;//Dot
						NumBox.Len=1;

						
					break;
				case 2:// AC/DCѡ��  ��Ե�����ֱ������ȥ
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
						if(SaveData.Setup.Item==0)//��������
						{
							
							
							NumBox.Title=(u8*)W_SET[0];
							NumBox.Num=*pt;
							NumBox.Max=(u16)ParameterLimit_AC[index-1][0];//Max
							NumBox.Min=(u16)ParameterLimit_AC[index-1][1];//Max;//Min
							NumBox.Dot=ParameterLimit_dot[index-3];//Dot
							NumBox.Len=ParameterLimit_len[index];
						}
						else//ֱ������
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
			Disp_System_Menu(index);//��ʾϵͳ����

			//ȡ����ֵ��������
//			u8 ListBox_Setup(NumBox_TypeDef * pt)
			
			switch(index)
			{
				case 0:
					LcdAddr.x=10;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					
					break;
				case 1:
					LcdAddr.x=8;LcdAddr.y=0;//��ʾ��ַ
					key=ListBox_Setup(&NumBox);
					break;
				case 2:
					LcdAddr.x=10;LcdAddr.y=0;//��ʾ��ַ
					key=ListBox_Setup(&NumBox);
					break;
				case 3:
					LcdAddr.x=10;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 4:
					LcdAddr.x=7;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 5:
					LcdAddr.x=7;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 6:
					LcdAddr.x=7;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 7:
					LcdAddr.x=8;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 8:
					LcdAddr.x=7;LcdAddr.y=0;//��ʾ��ַ
					key=ListBox_Setup(&NumBox);
					break;
				case 9:
					LcdAddr.x=7;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
					break;
				case 10:
					LcdAddr.x=10;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
				break;
					
				case 11:
//					LcdAddr.x=8;LcdAddr.y=0;//��ʾ��ַ
//					key=Number_Setup(&NumBox);//��ֵ������
//				break;
				case 12:
				case 13:
					LcdAddr.x=8;LcdAddr.y=0;//��ʾ��ַ
					key=Number_Setup(&NumBox);//��ֵ������
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
				Parameter_valuecomp();//�Ƚ����ò���
				
			}
			else
				*pt=NumBox.Num;//��������ֵ
//		 	Check_Parameter_Limit();//��������ֵ���
	
			//��������
			switch(key)
			{
				case KEY_SET:	//���ü�
				case L_KEY_SET:	//�������ü�
					if(SaveData.Setup.Group_Item==1&&index==1)
					{
						index=9;
					}
					if(SaveData.Setup.Item==1&&index==7)//ֱ��
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
							SetSystemStatus(SYS_STATUS_IDLE);//����״̬
							Store_set_flash();
							
						}
					}
					f_disp=TRUE;
					break;

				case KEY_UP:	//�ϼ�
				case L_KEY_UP:	//�����ϼ�
					break;
	
				case KEY_DOWN:		//�¼�
				case L_KEY_DOWN:	//�����¼�
					break;
	
				case KEY_ENTER:		//ȷ�ϼ�
//				case L_KEY_ENTER:	//����ȷ�ϼ�
					//SaveSystem();//��������
					if(SaveData.Setup.Output==1)
						SaveData.Setup.Output=2;
					SetSystemStatus(SYS_STATUS_IDLE);//����״̬
					Store_set_flash();
					SaveGroup();
				
					//ReadSaveData();
					break;
		
				case KEY_START:		//������
				case L_KEY_START:	//����������
					//SetSystemStatus(SYS_STATUS_TEST);//��������״̬
					break;
		
				case KEY_RESET:		//��λ��
				case L_KEY_RESET:	//������λ��
					SetSystemStatus(SYS_STATUS_IDLE);//����״̬
					break;
				
				default:
					break;
			}
		}
	}
	//Parameter_valuecomp();
}

//==========================================================
//�������ƣ�Resistance_Setup
//�������ܣ����������ô���
//��ڲ�����NumBox_TypeDef
//���ڲ�������ֵ
//�������ڣ�2016.03.10
//�޸����ڣ�2016.03.10 13:44
//��ע˵������
//==========================================================
//u8 Resistance_Setup(NumBox_TypeDef * pt)
//{
//	u8 key;
//	u8 len;
//	u8 count;//����������
//	u8 current;//��ǰ����λ
//	bool blink;//��ʾ��˸��־
//	LcdAddr_TypeDef addr;//��ʾ��ַ����
//	u8 tp;//��λ��С����ϵ��(1-4)
//	if(pt->Unit>1)
//		pt->Unit=0;
//	if(pt->Dot>6)
//		pt->Dot=0;
//	tp=3*NumBox.Unit;
//	tp+=3;
//	tp-=NumBox.Dot;

//	blink=TRUE;//��ʾ��˸��־

//	addr.x=LcdAddr.x;//��ʾ��ַ����
//	addr.y=LcdAddr.y;

//	count=0;//����������
//	if(pt->Dot==0)
//		current=3;//��ǰ����λ
//	else
//		current=4;//��ǰ����λ

//	while(1)
//	{
//		if(blink)//��ʾ
//		{
//			LcdAddr.x=addr.x;//��ʾ��ַ
//			LcdAddr.y=addr.y;
//			Hex_Format(NumBox.Num,NumBox.Dot,4,TRUE);//��ֵ��ʽ����4λ��ֵ
//			Disp_StrAt(DispBuf);//��ʾ�˵�ֵ
//			if(pt->Unit==0)Disp_Char('m');
//			if(pt->Unit==1)Disp_Char(' ');
//			Disp_Char(OHM);
//		}

//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				return(KEY_SET);
////				break;

//			case KEY_DOWN:		//�¼�
//				blink=TRUE;//��ʾ��˸��־
//				count=0;//����������
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//������
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

//			case L_KEY_DOWN:	//�����¼�
//				blink=TRUE;//��ʾ��˸��־
//				count++;//����������
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
////				if(count>28)//����������
////				{
////					if(len>0)len--;
////					if(len>0)len--;
////					if(len>0)len--;
////				}
////				else if(count>19)//����������
//				if(count>19)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//����������
//				{
//					if(len>0)len--;
//				}
//				if(pt->Num>=(POW_NUM[len]+pt->Min))
//					pt->Num-=POW_NUM[len];
//				else
//				{
////					pt->Num=pt->Min;
//					pt->Num=pt->Max;
////					Beep_Two();//������
//					if(tp>1)
//					{
//						tp--;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//						count=0;//����������
//					}
//					else
//						pt->Num=pt->Min;
//				}
//				break;

//			case KEY_UP:	//�ϼ�
//				blink=TRUE;//��ʾ��˸��־
//				count=0;//����������
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
////					pt->Num=pt->Min;
////					Beep_Two();//������
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

//			case L_KEY_UP:	//�����ϼ�
//				blink=TRUE;//��ʾ��˸��־
//				count++;//����������
//				if(current>(3-NumBox.Dot))//С����λ
//					len=current-1;
//				else
//					len=current;
////				if(count>28)//����������
////				{
////					if(len>0)len--;
////					if(len>0)len--;
////					if(len>0)len--;
////				}
////				else if(count>19)//����������
//				if(count>19)//����������
//				{
//					if(len>0)len--;
//					if(len>0)len--;
//				}
//				else if(count>10)//����������
//				{
//					if(len>0)len--;
//				}
//				pt->Num+=POW_NUM[len];
//				if(pt->Num>pt->Max)
//				{
////					pt->Num=pt->Max;
////					pt->Num=pt->Min;
////					Beep_Two();//������
//					if(tp<4)
//					{
//						tp++;
//						pt->Num=pt->Max/10+1;
//						pt->Unit=tp/3;
//						pt->Dot=3-tp%3;
//						count=0;//����������
//					}
//					else
//						pt->Num=pt->Max;
//				}
//				break;

//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				return(KEY_ENTER);
//				//break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				return(KEY_START);
////				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				return(KEY_RESET);
////				break;

//			default:
//				if(Keyboard.continuance!=TRUE) //��������
//					count=0;//����������
//				break;
//		}
//	}
//}
//==========================================================
//ϵͳ�˵���
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
//ϵͳ��
//const u8 SystemTab[][13]=
//{
//	"1.���ڿ���: ",
//	"2.����Ƶ��: ",
//	"3.��������: ",
//	"4.����ʱ��: ",
//	"5.Ѷ�쿪��: ",
//	"6.ʧ����ͣ: ",
////	"7.����ɨ��: ",
//};
//==========================================================
//ϵͳ���ϡ�����
//const u8 SystemLimit[][2]=
//{
//	{ 1, 0},//���ڿ���
//	{ 1, 0},//����Ƶ��
//	{ 1, 0},//��������
//	{ 99, 5},//����ʱ��
//	{ 1, 0},//Ѷ�쿪��
//	{ 1, 0},//ʧ����ͣ
////	{ 1, 0},//����ɨ��
//};
//==========================================================
//Ƶ��
//const u8 FrequencyTab[][5]=
//{
//	"50Hz",
//	"60Hz",
//};
//==========================================================
//����
//const u8 SwitchTab[][5]=
//{
//	"�ر�",
//	"��",
//};

//==========================================================
//�������ƣ�Check_System_Limit
//�������ܣ�ϵͳֵ���
//��ڲ���������
//���ڲ�������
//�������ڣ�2015.01.22 
//�޸����ڣ�2015.08.18 13:28
//��ע˵���������ޡ����޼��
//==========================================================
//void Check_System_Limit(void)
//{
//	u8 i;
//	u8 *pt;

//	pt=(u8* )&SaveData.System;
//	for(i=0;i<SYSTEM_MENU_MAX;i++)//��8��
//	{
//		if(*pt>SystemLimit[i][0])//Max
//			*pt= SystemLimit[i][0];//Max
//		if(*pt<SystemLimit[i][1])//Min
//			*pt=SystemLimit[i][1];//Min
//		pt++;
//	}
//}

//==========================================================
//�������ƣ�Disp_System_Info
//�������ܣ���ʾϵͳ��Ϣ
//��ڲ�����u8 index-�ڼ���
//���ڲ�������
//�������ڣ�2015.01.21
//�޸����ڣ�2015.08.19 09:48
//��ע˵������index���з�ҳ��ʾ
//==========================================================
//void Disp_System_Info(u8 index)
//{
//	u8 i;
//	u8 begin;
//	u8 end;
//	u8 page;

//	begin=index/SYSTEM_MENU_PAGE*SYSTEM_MENU_PAGE;//��ʼ��
//	end=begin+SYSTEM_MENU_PAGE;//������
//	if(end>SYSTEM_MENU_MAX)
//		end=SYSTEM_MENU_MAX;
//	page=(SYSTEM_MENU_MAX-1)/SYSTEM_MENU_PAGE+'1';//��ҳ��
//	
//	LcdAddr.x=19;LcdAddr.y=2;
//	Disp_Char(index/SYSTEM_MENU_PAGE+'1',0);//��ʾ��ǰҳ��
//	Disp_Char('/',0);
//	Disp_Char(page,0);//��ʾ��ҳ��

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=begin;i<end;i++)
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&SystemTab[i][0],0);//��ʾ���
//		Disp_System_Value(i);//��ʾϵͳֵ
//		LcdAddr.x++;
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//�������ƣ�Disp_System_Menu
//�������ܣ���ʾϵͳ����
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.22
//�޸����ڣ�2015.08.19 09:00
//��ע˵������
//==========================================================
//void Disp_System_Menu(void)
//{
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("ϵͳ����",0);//��ʾ
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("��<��,��>���޸�,<��,��>���ƶ�",0);//��ʾ
//}

//==========================================================
//�������ƣ�Disp_System_Value
//�������ܣ���ʾϵͳֵ
//��ڲ�����index:�ڼ������
//���ڲ�������
//�������ڣ�2015.01.21
//�޸����ڣ�2015.09.06 09:06
//��ע˵������ֵλ��+С����+��λ�ĳ��ȹ̶�Ϊ4���ַ�
//==========================================================
//void Disp_System_Value(u8 index)
//{
//	index%=SYSTEM_MENU_MAX;//���ϵͳ��
//	
//	switch(index)
//	{
//		case SYSTEM_MENU_UART://���ڿ���
//			Disp_Str(&SwitchTab[SaveData.System.Uart],0);//��ʾ
//			break;

//		case SYSTEM_MENU_FREQ60://�������Ƶ��
//			Disp_Str(&FrequencyTab[SaveData.System.Freq60],0);//��ʾ
//			break;

//		case SYSTEM_MENU_CONNECT://��������
//			Disp_Str(&SwitchTab[SaveData.System.Connect],0);//��ʾ
//			break;

//		case SYSTEM_MENU_CONNECT_TIME://����ʱ��
//			Hex_Format(SaveData.System.ConnectTime,1,2,0);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,0);//��ʾ
//			Disp_Str("s",0);//��ʾ�ո�
//			Disp_Str(" ",0);//��ʾ�ո�
//			break;

//		case SYSTEM_MENU_BEEP://Ѷ�쿪��
//			Disp_Str(&SwitchTab[SaveData.System.Beep],0);//��ʾ
//			break;

//		case SYSTEM_MENU_FAIL_PAUSE://ʧ����ͣ����
//			Disp_Str(&SwitchTab[SaveData.System.FailPause],0);//��ʾ
//			break;

////		case SYSTEM_MENU_BAR_SCAN://����ɨ�迪��
////			Disp_Str(&SwitchTab[SaveData.System.BarScan],0);//��ʾ
////			break;

//		default:
//			break;
//	}
//}

//==========================================================
//�������ƣ�System_Setup
//�������ܣ�ϵͳ���ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.21
//�޸����ڣ�2015.09.06 09:10
//��ע˵������
//==========================================================
//void System_Setup(void)
//{
//	u8 *pt;
//	u8 key;
//	u8 index;
//	Bool f_disp;//��ʾ����

//	f_disp=TRUE;
//	index=0;//�ӵ�һ�ʼ
//	Disp_System_Menu();//��ʾϵͳ����

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//��ʾ����
//		{
////			Disp_Clr( );//����
//			//���Ǻ�2�����������������������˸����
//			if((index>=SYSTEM_MENU_PAGE))//�ڶ�ҳ
//			{
//				LcdAddr.x=SETUP_ADDR_X+1;//��ʾ��ַ
//				LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*2;//������
//				Disp_Str("                ",0);//16���ո�
//				LcdAddr.x=SETUP_ADDR_X+1;//��ʾ��ַ
//				LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*3;//������
//				Disp_Str("                ",0);//1���ո�
//				Disp_Str(" ",0);//1���ո�
//			}
//			f_disp=FALSE;
////			Disp_System_Menu();//��ʾϵͳ����
//			Disp_System_Info(index);//��ʾϵͳ��Ϣ
//		}

//		LcdAddr.x=SETUP_ADDR_X+1+12;//��ֵ��ʾ��ַ
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*(index%SYSTEM_MENU_PAGE);

//		//ȡ����ֵ
//		pt=(u8* )&SaveData.System + index;
//		NumBox.Num=*pt;

//		//ȡ�����޷�ֵ
//		NumBox.Max=SystemLimit[index][0];//Max
//		NumBox.Min=SystemLimit[index][1];//Min
//		NumBox.Dot=0;//Dot

//		switch(index)//��ֵ���ô���
//		{
//			case SYSTEM_MENU_UART://���ڿ���
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//�б������
//				if(SaveData.System.Uart==1)
//					Start_Uart();//���ڿ���
//				else
//					Stop_Uart();//���ڹر�
//				break;

//			case SYSTEM_MENU_FREQ60://Ƶ��
//				NumBox.Title=FrequencyTab[0];
//				key=ListBox_Setup(&NumBox);//�б������
//				break;

//			case SYSTEM_MENU_CONNECT://��������
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//�б������
//				break;

//			case SYSTEM_MENU_CONNECT_TIME://����ʱ��
//				NumBox.Dot=1;//Dot
//				key=Number_Setup(&NumBox);//��ֵ������
//				break;

//			case SYSTEM_MENU_BEEP://Ѷ�쿪��
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//�б������
//				break;

//			case SYSTEM_MENU_FAIL_PAUSE://ʧ����ͣ����
//				NumBox.Title=SwitchTab[0];
//				key=ListBox_Setup(&NumBox);//�б������
//				break;

////			case SYSTEM_MENU_BAR_SCAN://����ɨ�迪��
////				NumBox.Title=SwitchTab[0];
////				key=ListBox_Setup(&NumBox);//�б������
////				break;

//			default:
//				break;
//		}

//		//��������ֵ
//		*pt=NumBox.Num;
//		Check_System_Limit();//ϵͳֵ���
//		f_disp=TRUE;//��ʾ����

//		//��������
//		switch(key)
//		{
//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				break;

//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				break;

//			case KEY_LEFT:		//���
////			case L_KEY_LEFT:	//�������
//				if(index)
//					index--;
//				else
//					index=SYSTEM_MENU_MAX-1;
//				break;
//	
//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				index++;
//				if(index>=SYSTEM_MENU_MAX)
//					index=0;
//				break;

//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
//				break;
//	
//			case KEY_ENTER:		//ȷ�ϼ�
////			case L_KEY_ENTER:	//����ȷ�ϼ�
//				//��������
//				SaveSystem();//����ϵͳ����
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//	
//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_START);//��������״̬
//				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//�������ƣ�Password_Check
//�������ܣ�����У��
//��ڲ�������
//���ڲ�����TRUE:��Ч
//�������ڣ�2015.01.29 
//�޸����ڣ�2015.08.24 11:40
//��ע˵������
//==========================================================
//Bool Password_Check(void)
//{
//	u8 key;

//	if(MenuIndex!=2)//������Ϣ����
//	{
//		if(F_Password==TRUE)//������Ч��־	
//			return (TRUE);
//	
//		if(SaveData.Factory.Password==0)//����Ϊ��ʱ����У��
//			return (TRUE);
//	}
//	else
//	{
//		Disp_Clr( );//����
//	}
//	
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("����������",0);//��ʾ
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("��<��,��>���޸�,<ȷ��>������",0);//��ʾ

//	while(1)
//	{
//		LcdAddr.x=13;//������ʾ��ַ
//		LcdAddr.y=50;
//		Disp_Str("****",0);//��ʾ

//		LcdAddr.x=13;//������ʾ��ַ
//		NumBox.Num=0;//Value
//		NumBox.Max=9999;//Max
//		NumBox.Min=0;//Min
//		NumBox.Dot=0;//Dot

//		key=Number_Setup(&NumBox);//��ֵ������
//		switch(key)//��������
//		{
//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				break;

//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				break;

//			case KEY_LEFT:	//���
////			case L_KEY_LEFT:	//�������
//				break;
//	
//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
////				break;

//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				break;
//	
//			case KEY_ENTER:		//ȷ�ϼ�
////			case L_KEY_ENTER:	//����ȷ�ϼ�
//				Disp_Clr();//����
//				if(MenuIndex==2)//������Ϣ����
//				{
//					if(NumBox.Num==918)//������������
//						return (TRUE);
//					else
//						return (FALSE);
//				}
//				else
//				{
//					if(NumBox.Num==SaveData.Factory.Password)//��ǰ�����б�
//					{
//						F_Password=TRUE;//������֤��Ч
//						return (TRUE);
//					}
//					else
//						return (FALSE);
//				}
//				break;
//	
//			case KEY_START:		//������
////			case L_KEY_START:	//����������
//				break;
//	
//			case KEY_RESET:		//��λ��
////			case L_KEY_RESET:	//������λ��
//				return (FALSE);
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//������
//enum PasswordEnum
//{	
//	PASSWORD_MENU_OLD ,
//	PASSWORD_MENU_NEW ,
//	PASSWORD_MENU_NEW2 ,
//};
//==========================================================
//������
//const u8 PasswordTab[][11]=
//{
//	"��ǰ����: ",
//	"��������: ",
//	"����ȷ��: ",
//};
//==========================================================
//�������ƣ�Disp_Password_Info
//�������ܣ���ʾ������Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.23
//�޸����ڣ�2015.08.19 10:45
//��ע˵������
//==========================================================
//void Disp_Password_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<3;i++)//��3��
//	{
//		LcdAddr.x=SETUP_ADDR_X+2;
//		Disp_Str(&PasswordTab[i][0],0);//��ʾ���
//		Disp_Str("****",0);//��ʾ
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//�������ƣ�Password_Setup
//�������ܣ��������ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.23
//�޸����ڣ�2015.08.20 11:03
//��ע˵������
//==========================================================
//void Password_Setup(void)
//{
//	u8 key;
//	u8 index;
//	u16 pw[3];

//	F_Password=FALSE;//�����������ã�������֤��Ч
//	for(index=0;index<3;index++)//��3��
//	{
//		pw[index]=0;
//	}
//	LcdAddr.x=10;LcdAddr.y=2;
//	Disp_Str("��������",0);//��ʾ
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	LcdAddr.x=1;LcdAddr.y=110;
//	Disp_Str("��<��,��>���޸�,<��,��>���ƶ�",0);//��ʾ

//	index=0;//�ӵ�һ�ʼ

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		Disp_Password_Info();//��ʾ������Ϣ

//		LcdAddr.x=SETUP_ADDR_X+2+10;//������ʾ��ַ
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*index;

//		//ȡ����ֵ
//		NumBox.Num=0;

//		//ȡ�����޷�ֵ
//		NumBox.Max=9999;//Max
//		NumBox.Min=0;//Min
//		NumBox.Dot=0;//Dot

//		key=Number_Setup(&NumBox);//��ֵ������
//		switch(key)//��������
//		{
//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				break;

//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				break;

//			case KEY_LEFT:	//���
////			case L_KEY_LEFT:	//�������
//				pw[index]=NumBox.Num;//���µ�ǰ����ֵ
//				if(index)
//					index--;
//				else
//					index=2;
//				LcdAddr.x=1;LcdAddr.y=110;
//				if(index==2)//�����������ʾ
//					Disp_Str("��<ȷ��>������, <�˳�>������ ",0);//��ʾ
//				else
//					Disp_Str("��<��,��>���޸�,<��,��>���ƶ�",0);//��ʾ
//				break;
//	
//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				pw[index]=NumBox.Num;//���µ�ǰ����ֵ
//				index++;
//				if(index>2)
//					index=0;
//				LcdAddr.x=1;LcdAddr.y=110;
//				if(index==2)//�����������ʾ
//					Disp_Str("��<ȷ��>������, <�˳�>������ ",0);//��ʾ
//				else
//					Disp_Str("��<��,��>���޸�,<��,��>���ƶ�",0);//��ʾ
//				break;

//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
//				break;
//	
//			case KEY_ENTER:		//ȷ�ϼ�
////			case L_KEY_ENTER:	//����ȷ�ϼ�
//				pw[index]=NumBox.Num;//���µ�ǰ����ֵ
//				key=0;//״̬
//				if(pw[0]==SaveData.Factory.Password)//��ǰ�����б�
//				{
//					key=1;
//					if(pw[1]==pw[2])//���������б�
//					{
//						key=2;
//						if((pw[0]==0)&&(pw[1]==0))//����Ϊ��
//						{
//							key=3;
//						}
//						else
//						{
//							SaveData.Factory.Password=pw[1];//�������
//							SaveFactory();//��������
//						}
//					}
//				}
//				if(key<3)
//				{
////					Disp_Clr();//����
////					LcdAddr.x=8;LcdAddr.y=88;
//					LcdAddr.x=9;LcdAddr.y=2;
//					if(key==0)
//					{
//						Disp_Str("��ǰ�������",1);//��ʾ
//						Beep_Two();//������
//					}
//					else if(key==1)
//					{
//						Disp_Str("�������ô���",1);//��ʾ
//						Beep_Two();//������
//					}
//					else if(key==2)
//					{
//						Disp_Str("�����޸ĳɹ�",1);//��ʾ
//					}
//					Delay_100ms(12);//��ʱ1.2s
//				}
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//	
//			case KEY_START:		//������
////			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_START);//��������״̬
//				break;
//	
//			case KEY_RESET:		//��λ��
////			case L_KEY_RESET:	//������λ��
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//�������ƣ�FactoryInfo_Setup
//�������ܣ�������Ϣ���ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.14
//�޸����ڣ�2015.08.24 11:54
//��ע˵����
//�����¼�����ʾ������Ϣ��
//�����Ҽ�����������������ý���
//�������������Ĭ�ϳ�������ֵ
//�������ã�ϵͳ��λ����
//==========================================================
//void FactoryInfo_Setup(void)
//{
//	u8 key;

//	LcdAddr.x=7;LcdAddr.y=2;
//	Disp_Product_Model();//��ʾ��Ʒ�ͺ�
//	Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	Disp_Factory_Info();//��ʾ������Ϣ
//	Lcd_Draw_Line(0,107,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	LcdAddr.x=7;LcdAddr.y=110;
//	Disp_Str("��<ȷ��>���˳�",0);//��ʾ

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
//		switch(key)
//		{
////			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				ResetSys();//�����λ
//				break;

//			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
////				break;
//			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
//				Disp_Instrument_Info();//��ʾ������Ϣ
//				return;
////				break;
//	
////			case KEY_LEFT:	//���
//			case L_KEY_LEFT:	//�������
//#if (MENU_CONFIG_SUPPORT)
//				if(Password_Check())//����У��,TRUE��Ч
//				{
//					LoadDefaultSet();//����Ĭ������ֵ
//					LoadDefaultCalibrate();//����Ĭ��У׼ֵ
//					Beep_One();//��������һ��
//				}
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//#endif
//				break;

////			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
//#if (MENU_CONFIG_SUPPORT)
//				if(Password_Check())//����У��,TRUE��Ч
//					Config_Setup();//��������ֵ���ô���
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//#endif
//				break;

//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//	
//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_START);//��������״̬
//				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//�������ƣ�Disp_Factory_Info
//�������ܣ���ʾ������Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.09
//�޸����ڣ�2015.08.19 10:01
//��ע˵������
//==========================================================
//void Disp_Factory_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<4;i++)//��4��
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&NumTab[i][0],0);//��ʾ���
//		switch(i)
//		{
//			case 0:
//				Disp_Software_Version();//��ʾ����汾
//				break;
//			case 1:
//				Disp_Hardware_Version();//��ʾӲ���汾
//				break;
//			case 2:
//				Disp_Boot_Number();//��������
//				break;
//			case 3:
//				Disp_Compile_Date();//��ʾ��������
//				break;
//			default:
//				break;

//		}
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//�������ƣ�Disp_Instrument_Info
//�������ܣ���ʾ������Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.22
//�޸����ڣ�2015.08.20 15:52
//��ע˵������
//==========================================================
//void Disp_Instrument_Info(void)
//{
//	u8 key;

//	Disp_Clr( );//����

//	LcdAddr.x=0;LcdAddr.y=1;
//	Disp_Software_Version();//��ʾ����汾
//	LcdAddr.x=15;
//	Disp_Boot_Number();//��������

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Hardware_Version();//��ʾӲ���汾
//	LcdAddr.x=15;
//	Disp_Product_ID();//��ʾ�������	
//	
//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Compile_Date();//��ʾ��������

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Disp_Chip_ID();//��ʾ������

//	LcdAddr.x=0;LcdAddr.y+=18;
//	Lcd_Draw_Line(0,LcdAddr.y,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	LcdAddr.y+=2;
//	Lcd_Draw_Line(0,LcdAddr.y,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�

//	LcdAddr.y+=2;
//	Disp_Company_Name();//��ʾ��������

//	LcdAddr.x=0;LcdAddr.y+=17;
//	Disp_Company_Http();//��ʾ������ҳ

//	LcdAddr.x=0;LcdAddr.y+=17;
//	Disp_Company_Telephone();//��ʾ���̵绰

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
//		switch(key)
//		{
//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
//				break;
//	
//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				break;
//	
//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				break;
//	
//			case KEY_LEFT:	//���
////			case L_KEY_LEFT:	//�������
//				break;

//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				break;

//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//	
//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_START);//��������״̬
//				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

//==========================================================
//������
//enum ConfigMenuEnum
//{	
//	CONFIG_MENU_BOOTNUM ,
//	CONFIG_MENU_FACTORYID ,
//	CONFIG_MENU_PASSWORD ,
//};
//==========================================================
//������
//const u8 ConfigTab[][13]=
//{
//	"1.��������: ",
//	"2.�������: ",
//	"3.��������: ",
//};
//==========================================================
//�������ϡ�����
//const u16 ConfigLimit[][2]=
//{
//	{ 9999, 1},//��������
//	{ 9999, 0},//�������
//	{ 9999, 0},//��������
//};
 
//==========================================================
//�������ƣ�Check_Config_Limit
//�������ܣ�����ֵ���
//��ڲ���������
//���ڲ�������
//�������ڣ�2015.01.22 
//�޸����ڣ�2015.09.06 11:15
//��ע˵���������ޡ����޼��
//==========================================================
//void Check_Config_Limit(void)
//{
//	u8 i;
//	u16 *pt;

//	//��ʼ�����б�
//	pt=(u16* )&SaveData.Factory;
//	for(i=0;i<CONFIG_MENU_MAX;i++)//��3��
//	{
//		if(*pt!=65535)
//			break;
//	}
//	if(i>=CONFIG_MENU_MAX)//������
//	{
//		LoadDefaultSet();//����Ĭ������ֵ
//		LoadDefaultCalibrate();//����Ĭ��У׼ֵ
//		Beep_One();//��������һ��
//	}
//	else
//	{
//		pt=(u16* )&SaveData.Factory;
//		for(i=0;i<CONFIG_MENU_MAX;i++)//��3��
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
//�������ƣ�Disp_Config_Info
//�������ܣ���ʾ������Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.21
//�޸����ڣ�2015.08.19 10:17
//��ע˵������
//==========================================================
//void Disp_Config_Info(void)
//{
//	u8 i;

//	LcdAddr.y=SETUP_ADDR_Y;
//	for(i=0;i<CONFIG_MENU_MAX;i++)//��3��
//	{
//		LcdAddr.x=SETUP_ADDR_X+1;
//		Disp_Str(&ConfigTab[i][0],0);//��ʾ
//		Disp_Config_Value(i);//��ʾ����ֵ
//		LcdAddr.x++;
//		LcdAddr.y+=HEIGHT_OF_SETUP;
//	}
//}

//==========================================================
//�������ƣ�Disp_Config_Menu
//�������ܣ���ʾ���ý���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.22
//�޸����ڣ�2015.08.19 10:16
//��ע˵������
//==========================================================
void Comp_test(u16 comp_data)
{
//	if(SaveData.System.Res_Lo!=0)
//	{
//		if(SaveData.System.Res_Lo>comp_data)
//		{
//			SetSystemMessage(MSG_LOW);//ϵͳ��Ϣ-����
////			Led_Pass_Off();//�غϸ��
////			Led_Fail_On();//��������
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
//				SetSystemMessage(MSG_HIGH);//ϵͳ��Ϣ-���ޱ���
////				Led_Pass_Off();//�غϸ��
////				Led_Fail_On();//��������
//				F_Fail=TRUE;	
//			}
//		
//		}
//		if(!F_Fail)
//		{
//			SetSystemMessage(MSG_PASS);//ϵͳ��Ϣ-����
////			Led_Pass_On();//�غϸ��
////			Led_Fail_Off();//��������
////		
//		}
//	}

}

//==========================================================
//�������ƣ�Disp_Config_Value
//�������ܣ���ʾ����ֵ
//��ڲ�����index:�ڼ������
//���ڲ�������
//�������ڣ�2015.01.22
//�޸����ڣ�2015.08.19 10:22
//��ע˵������ֵλ��+С����+��λ�ĳ��ȹ̶�Ϊ4���ַ�
//==========================================================
//void Disp_Config_Value(u8 index)
//{
//	index%=CONFIG_MENU_MAX;//���������
//	
//	switch(index)
//	{
//		case CONFIG_MENU_BOOTNUM:
//			Hex_Format(SaveData.Factory.BootNum,0,4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,0);//��ʾ
//			break;

//		case CONFIG_MENU_FACTORYID:
//			Hex_Format(SaveData.Factory.ProductId,0,4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,0);//��ʾ
//			break;

//		case CONFIG_MENU_PASSWORD:
//			Hex_Format(SaveData.Factory.Password,0,4,1);//���ݸ�ʽ����DispBuf
//			Disp_Str(DispBuf,0);//��ʾ
//			break;

//		default:
//			break;
//	}
//}

//==========================================================
//�������ƣ�Config_Setup
//�������ܣ��������ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.22
//�޸����ڣ�2015.08.19 10:29
//��ע˵������
//==========================================================
//void Config_Setup(void)
//{
//	u16 *pt;
//	u8 key;
//	u8 index;
//	Bool f_disp;//��ʾ����

//	Disp_Config_Menu();//��ʾ���ý���
//	f_disp=FALSE;
//	index=0;//�ӵ�һ�ʼ

//	while(SystemStatus==SYS_STATUS_SETUP)
//	{
//		if(f_disp==TRUE)//��ʾ����
//		{
//			f_disp=FALSE;
//			Disp_Config_Info();//��ʾ������Ϣ
//		}

//		LcdAddr.x=SETUP_ADDR_X+1+12;//��ֵ��ʾ��ַ
//		LcdAddr.y=SETUP_ADDR_Y+HEIGHT_OF_SETUP*index;

//		//ȡ����ֵ
//		pt=(u16* )&SaveData.Factory+index;
//		NumBox.Num=*pt;

//		//ȡ�����޷�ֵ
//		NumBox.Max=ConfigLimit[index][0];//Max
//		NumBox.Min=ConfigLimit[index][1];//Min
//		NumBox.Dot=0;//Dot

//		switch(index)//��ֵ���ô���
//		{
//			case CONFIG_MENU_BOOTNUM:
//			case CONFIG_MENU_FACTORYID:
//			case CONFIG_MENU_PASSWORD:
//				key=Number_Setup(&NumBox);//�б������
//				break;
//	
//			default:
//				break;
//		}

//		*pt=NumBox.Num;//��������ֵ
//		Check_Config_Limit();//����ֵ���
//		f_disp=TRUE;//��ʾ����

//		//��������
//		switch(key)
//		{
//			case KEY_UP:	//�ϼ�
////			case L_KEY_UP:	//�����ϼ�
//				break;

//			case KEY_DOWN:		//�¼�
////			case L_KEY_DOWN:	//�����¼�
//				break;

//			case KEY_LEFT:	//���
////			case L_KEY_LEFT:	//�������
//				if(index)
//					index--;
//				else
//					index=CONFIG_MENU_MAX-1;
//				break;

//			case KEY_RIGHT:		//�Ҽ�
////			case L_KEY_RIGHT:	//�����Ҽ�
//				index++;
//				if(index>=CONFIG_MENU_MAX)
//					index=0;
//				break;
//	
//			case KEY_SET:	//���ü�
////			case L_KEY_SET:	//�������ü�
//				break;
//	
//			case KEY_ENTER:		//ȷ�ϼ�
////			case L_KEY_ENTER:	//����ȷ�ϼ�
//				//��������
//				SaveFactory();//���濪������
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//	
//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_START);//��������״̬
//				break;
//	
//			case KEY_RESET:		//��λ��
//			case L_KEY_RESET:	//������λ��
//				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
//				break;
//			
//			default:
//				break;
//		}
//	}
//}

////==========================================================
////ϵͳ״̬
//const u8 SysStatusList[][5+1]=
//{
//	{"Idle "},
//	{"Test "},
//	{"Stop "},
//	{"Clr  "},
//	{"Set  "},
//};
////==========================================================
////�������ƣ�Disp_SysStatus
////�������ܣ���ʾϵͳ״̬
////��ڲ�������
////���ڲ�������
////�������ڣ�2014.10.15
////�޸����ڣ�2014.10.15 15:17
////��ע˵������
////==========================================================
//void Disp_SysStatus(void)
//{
//	Disp_Str(SysStatusList[GetSystemStatus()],0);//��ʾϵͳ״̬
//}
//
//==========================================================
//ϵͳ��Ϣ
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
//�������ƣ�Disp_SysMessage
//�������ܣ���ʾϵͳ��Ϣ
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.10.15
//�޸����ڣ�2014.10.15 15:17
//��ע˵������
//==========================================================
//void Disp_SysMessage(void)
//{
//	Disp_Str(SysMessageList[GetSystemMessage()],0);//��ʾϵͳ��Ϣ
////	Disp_Txt_Str(SysMessageList[GetSystemMessage()]);//��ʾϵͳ��Ϣ
//}

//==========================================================
//��������-����ͼƬ��ʽ
//��������(48*48)
//�������ӵ������޹�˾(16*16)
//�������±�������·2��
//�绰��88226706 8826707
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
//������㣬��ѹ/����*����
void Get_Res(void)
{
	Res_count.r=Res_count.v*Res_count.rate/Res_count.i;
}
/********************************
��������: void DispF(float f)
���� ���ÿ�ѧ��������ʾ����������floatȫ��Χ�ھ�ȷ��ʾ��������Χ������ʾ��
˵�� ����������ʾ��ΧΪ+-1.175494E-38��+-3.402823E+38
��ڲ�����fΪҪ��ʾ�ĸ�����
����ֵ ����
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
		//printf("?.??????");   //̫С�ˣ���������С��Χ��
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
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����  
	
	MYDMA_Enable(DMA1_Channel2);//��ʼһ��DMA���䣡
}
//��2����ʾʮ����β���ͽ׵��Ӻ�����
/********************************
��������: void PrintW(unsigned long w,char j)
���� ����ѧ����������ʾʮ����β���ͽ���
��ڲ�����wΪβ����jΪ����
����ֵ ����
********************************/
//void PrintW(unsigned long w,char j) 
//{
//	char i;
//	unsigned long tw,b;
//	if(j<-38)                //̫С�ˣ�������С������Χ��
//	{
//		printf("?.??????");
//		return;
//	}           
//	if(j>38)                   //���㷨�������j>38�����
//	{
//		printf("*.******");
//		return;
//	}
//	tw=w/1000000;
//	PrintChar(tw+��0��);
//	PrintChar(��-��);
//	w=w-tw*1000000;
//	b=100000;
//	for(i=0;i<6;i++)
//	{
//		tw=w/b;
//		PrintChar(tw+��0��);
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
 return jieguo;//���Ե���
 }
 
 /*************************************************************************************************************************
*���� ? ? ? ? : void HextoBCD(u8 *pBuff,u8 len)
*���� ? ? ? ? : ʮ������תΪBCD��
*���� ? ? ? ? : pBuff:�����ʮ����������,len:���鳤��
*���� ? ? ? ? : ��
*���� : �ײ�궨��
* ���� : li_qcxy@126.com
* ʱ�� : 2017-1-5
* ����޸�ʱ��:?
*˵�� ? ? ? ? : 
*************************************************************************************************************************/
void HextoBCD(u8 *pBuff,u8 len) //ʮ������תΪBCD��
{
	u8 i,temp;
	for(i=0;i<len;i++)
	{
		temp=pBuff[i]/10;
		//time[i]=pBuff[i]%10+temp*16;
	}
}


/*************************************************************************************************************************
*���� ? ? ? ? : void BCDtoHex(u8 *pBuff,u8 len)
*���� ? ? ? ? : BCD��תΪʮ������
*���� ? ? ? ? : pBuff:�����ʮ����������,len:���鳤��
*���� ? ? ? ? : ��
*���� : �ײ�궨��
* ���� : li_qcxy@126.com
* ʱ�� : 2017-1-5
* ����޸�ʱ��:?
*˵�� ? ? ? ? : 
*************************************************************************************************************************/
void BCDtoHex(u8 *pBuff,u8 len) //BCD��תΪʮ������
{
	u8 i,temp;
	for(i = 0;i < len;i ++)
	{
		temp =pBuff[i] / 16;
		pBuff[i] = temp * 10 + pBuff[i] % 16;
	}
}
u8 BCDtoHex1(u8 pBuff,u8 len) //BCD��תΪʮ������
{
	u8 i,temp;
	
	temp =pBuff / 16;
	pBuff = temp * 10 + pBuff % 16;
	return pBuff;
}




