//==========================================================
//ÎÄ¼şÃû³Æ£ºDebug.c
//ÎÄ¼şÃèÊö£ºµ÷ÊÔÉèÖÃ×Ó³ÌĞò
//ÎÄ¼ş°æ±¾£ºVer1.0
//´´½¨ÈÕÆÚ£º2015.10.26
//ĞŞ¸ÄÈÕÆÚ£º2015.10.29 14:38
//ÎÄ¼ş×÷Õß£º»ÆºêÁé
//±¸×¢ËµÃ÷£ºÎŞ
//×¢ÒâÊÂÏî£ºÎŞ
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
//Ä¬ÈÏĞ£×¼Êı¾İ


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
//Ğ£×¼ÖµÉÏ¡¢ÏÂÏŞ
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
//µ÷ÊÔ²Ëµ¥
//==========================================================
//Ğ£Õı²Ëµ¥
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
//È·ÈÏÌáÊ¾
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
//º¯ÊıÃû³Æ£ºDisp_Debug_Menu
//º¯Êı¹¦ÄÜ£ºÏÔÊ¾²Ëµ¥
//Èë¿Ú²ÎÊı£ºindex:µÚ¼¸Ïî
//³ö¿Ú²ÎÊı£ºÎŞ
//´´½¨ÈÕÆÚ£º2015.10.29
//ĞŞ¸ÄÈÕÆÚ£º2015.10.29 14:42
//±¸×¢ËµÃ÷£ºÎŞ
//==========================================================
void Disp_Debug_Menu(u8 index)
{
	//µÚÒ»ĞĞ
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8 *)&DebugMenu[index%DEBUG_MENU_MAX][0]);
	LcdAddr.x=9;LcdAddr.y=0;
	Lcd_SetAddr();
	
		
//	//µÚ¶şĞĞ
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8 *)EnterTab1);//ÏÔÊ¾È·ÈÏÌáÊ¾
}

//==========================================================
//º¯ÊıÃû³Æ£ºDebug_Process
//º¯Êı¹¦ÄÜ£ºµ÷ÊÔÉèÖÃ´¦Àí
//Èë¿Ú²ÎÊı£ºÎŞ
//³ö¿Ú²ÎÊı£ºÎŞ
//´´½¨ÈÕÆÚ£º2015.10.29
//ĞŞ¸ÄÈÕÆÚ£º2015.10.29 14:43
//±¸×¢ËµÃ÷£ºÎŞ
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
	f_disp=TRUE;//ÏÔÊ¾

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if(f_disp==TRUE)//ÏÔÊ¾¸üĞÂ
		{
			f_disp=FALSE;
			Disp_Debug_Menu(index);//ÏÔÊ¾½çÃæ	
			
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//µÈ´ı°´¼ü(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//ÉèÖÃ¼ü
			//case L_KEY_SET:	//³¤°´ÉèÖÃ¼ü
				Disp_Clr( );//ÇåÆÁ
				Res_Calibrate(index);//µç×èĞ£×¼´¦Àí

				f_disp=TRUE;
				break;
	
			case KEY_UP:	//ÉÏ¼ü
//			case L_KEY_UP:	//³¤°´ÉÏ¼ü
				if(index<(DEBUG_MENU_MAX-1))index++;
				else index=0;
				f_disp=TRUE;//ÏÔÊ¾
				break;

			case KEY_DOWN:		//ÏÂ¼ü
//			case L_KEY_DOWN:	//³¤°´ÏÂ¼ü
				if(index>0)index--;
				else index=(DEBUG_MENU_MAX-1);
				f_disp=TRUE;//ÏÔÊ¾
				break;

//			case KEY_START:		//Æô¶¯¼ü
//			case L_KEY_START:	//³¤°´Æô¶¯¼ü
//				SetSystemStatus(SYS_STATUS_TEST);//²âÊÔ×´Ì¬
//				break;
	
			case KEY_ENTER:		//È·ÈÏ¼ü
			case L_KEY_ENTER:	//³¤°´È·ÈÏ¼ü
				i=11;
				pt=(u8*)(&SaveData.Calibrate);//Ğ£×¼ÖµÊ×µØÖ·
				pt2=(u8*)(&Cal);//¸üĞÂÍ¨ÓÃĞ£×¼Öµ
				key=i*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//Ğ£ÑéºÍ±£´æĞ£×¼Êı¾İ
				StoreCalDate();//±£´æĞ£×¼Öµ
				SetSystemStatus(SYS_STATUS_IDLE);//´ı»ú×´Ì¬
				break;
	
			case KEY_RESET:		//¸´Î»¼ü
			case L_KEY_RESET:	//³¤°´¸´Î»¼ü
				//SetSystemStatus(SYS_STATUS_IDLE);//´ı»ú×´Ì¬
				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//º¯ÊıÃû³Æ£ºDefault_Calibrate
//º¯Êı¹¦ÄÜ£º¼ÓÔØÄ¬ÈÏĞ£×¼Öµ
//Èë¿Ú²ÎÊı£ºÎŞ
//³ö¿Ú²ÎÊı£ºÎŞ
//´´½¨ÈÕÆÚ£º2015.02.13
//ĞŞ¸ÄÈÕÆÚ£º2015.08.31 10:29
//±¸×¢ËµÃ÷£ºÎŞ
//==========================================================
void Default_Calibrate(void)
{
	u8 key;

	Disp_Clr();//ÇåÆÁ
	LcdAddr.x=5;LcdAddr.y=0;
	Disp_Str("»Ö¸´Ä¬ÈÏÖµ?");//ÏÔÊ¾
	LcdAddr.x=1;LcdAddr.y=1;
	Disp_Str("°´<È·ÈÏ>¼ü»Ö¸´,<×ó,ÓÒ>¼ü·µ»Ø");//ÏÔÊ¾

	while(SystemStatus==SYS_STATUS_DEBUG)
	{
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//µÈ´ı°´¼ü(100*10ms/10=100ms)
		switch(key)
		{
//			case KEY_SET:	//ÉèÖÃ¼ü
//			case L_KEY_SET:	//³¤°´ÉèÖÃ¼ü
//				break;
//	
//			case KEY_UP:	//ÉÏ¼ü
//			case L_KEY_UP:	//³¤°´ÉÏ¼ü
//				break;
//	
//			case KEY_DOWN:		//ÏÂ¼ü
//			case L_KEY_DOWN:	//³¤°´ÏÂ¼ü
//				break;
//	
			case KEY_LEFT:		//×ó¼ü
//			case L_KEY_LEFT:	//³¤°´×ó¼ü
//				break;
//
			case KEY_RIGHT:		//ÓÒ¼ü
//			case L_KEY_RIGHT:	//³¤°´ÓÒ¼ü
				return;
//				break;

			case KEY_ENTER:		//È·ÈÏ¼ü
//			case L_KEY_ENTER:	//³¤°´È·ÈÏ¼ü
//				LoadDefaultCalibrate();//¼ÓÔØÄ¬ÈÏĞ£×¼Öµ
				LcdAddr.x=8;LcdAddr.y=20;
				Disp_Str("»Ö¸´Ä¬ÈÏÖµ³É¹¦");//ÏÔÊ¾
//				Beep_One();//·äÃùÆ÷ÏìÒ»Éù
//				Delay_100ms(12);//ÑÓÊ±1.2s
				return;
//				break;
//	
//			case KEY_START:		//Æô¶¯¼ü
//			case L_KEY_START:	//³¤°´Æô¶¯¼ü
//				break;
	
			case KEY_RESET:		//¸´Î»¼ü
			case L_KEY_RESET:	//³¤°´¸´Î»¼ü
				return;
//				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//¾øÔµĞ£×¼²Ëµ¥

//==========================================================
//¾øÔµĞ£×¼Ïî
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
//º¯ÊıÃû³Æ£ºRes_Calibrate
//º¯Êı¹¦ÄÜ£ºµç×èĞ£×¼´¦Àí
//Èë¿Ú²ÎÊı£ºÎŞ
//³ö¿Ú²ÎÊı£ºÎŞ
//´´½¨ÈÕÆÚ£º2015.02.13
//ĞŞ¸ÄÈÕÆÚ£º2015.08.31 10:29
//±¸×¢ËµÃ÷£ºÎŞ
//==========================================================
void Res_Calibrate(u8 num)
{
	u8 i;
	
	u8 key;
	u8 dot,lenth;
	u16 set_high,set_low;
	u8 F_Disp;//ÏÔÊ¾¸üĞÂ±êÖ¾
	u8 *pt;
	u8 *pt2;
	F_Disp=TRUE;//ÏÔÊ¾¸üĞÂ
//	MenuSelect=0;//È¡µ±Ç°Ïî

	delay_ms(50);//Ó²¼şÑÓÊ

	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)&DebugMenu[num][0]);//µ±Ç°Ïî¸ßÁÁÏÔÊ¾
	LcdAddr.y=1;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)Debugext);
	//CalibrateLimit	
	for(i=0;i<DEBUG_MENU_MAX;i++)
	{
		if((Cal[i].Num>CalibrateLimit[num][0])||(Cal[i].Num<CalibrateLimit[num][1]))
			Cal[i].Num=CalibrateLimitvalue[i];
	
	}
	pt=(u8*)(&SaveData.Calibrate);//Ğ£×¼ÖµÊ×µØÖ·
	pt2=(u8*)(&Cal);//¸üĞÂÍ¨ÓÃĞ£×¼Öµ
	key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
	set_high=CalibrateLimit[num][0];//ÉÏÏŞ
	set_low=CalibrateLimit[num][1];//ÏÂÏŞ
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

//		Test_value.Test_I=Read_Channel(1);//µçÑ¹ADÖµ  channel1  µçÁ÷
//		AD7705_init(0);
//		Test_value.Test_v.Test_v=Read_Channel(0);//µçÁ÷ADÖµ	
	i=1;
	//while(SystemStatus==SYS_STATUS_DEBUG)
	while(i)
	{
//		Read_Ad();
//		Get_Result();
		if(F_Disp==TRUE)
		{
			F_Disp=FALSE;//ÏÔÊ¾¸üĞÂ
			dot=Debug_Dot[num];
			lenth=4;
			Hex_Format(Cal[num].Num, dot, lenth, FALSE);
			LcdAddr.y=0;
			LcdAddr.x=10;
			Disp_StrAt(DispBuf);
			
			LcdAddr.y=0;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)&DebugMenu[num][0]);//µ±Ç°Ïî¸ßÁÁÏÔÊ¾
			LcdAddr.y=1;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)Debugext);
//			LcdAddr.x=15;
//			Lcd_SetAddr();

		}				
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//µÈ´ı°´¼ü(100*10ms/10=100ms)
		switch(key)
		{
//			case KEY_SET:	//ÉèÖÃ¼ü
//			case L_KEY_SET:	//³¤°´ÉèÖÃ¼ü
//				break;

//			case KEY_UP:	//ÉÏ¼ü
//			case L_KEY_UP:	//³¤°´ÉÏ¼ü
//				break;
	
//			case KEY_DOWN:		//ÏÂ¼ü
//			case L_KEY_DOWN:	//³¤°´ÏÂ¼ü
//				break;

			case KEY_UP:	//×ó¼ü
				
//					if(Cal[num].Num>set_high)
//						Cal[num].Num=set_low;
//					
//					else
//						Cal[num].Num++;	
					F_Disp=TRUE;
			break;
			case L_KEY_UP:	//³¤°´×ó¼ü
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
//				F_Disp=TRUE;//ÏÔÊ¾¸üĞÂ
				break;

			case KEY_DOWN:		//ÓÒ¼ü

				F_Disp=TRUE;
				break;
			case L_KEY_DOWN:	//³¤°´ÓÒ¼ü

				F_Disp=TRUE;

				break;
	
			case KEY_ENTER:		//È·ÈÏ¼ü
			case L_KEY_ENTER:	//³¤°´È·ÈÏ¼ü
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
	
			case KEY_START:		//Æô¶¯¼ü
			case L_KEY_START:	//³¤°´Æô¶¯¼ü
				CalTest_Process(num);//Ğ£×¼²âÊÔ´¦Àí
				Disp_Clr( );//ÇåÆÁ
				F_Disp=TRUE;//ÏÔÊ¾¸üĞÂ
			i=0;
				break;
	
			case KEY_RESET:		//¸´Î»¼ü
			case L_KEY_RESET:	//³¤°´¸´Î»¼ü
				return;
//				break;
			
			default:
				break;
		}
		
	}
	
}

//==========================================================
//º¯ÊıÃû³Æ£ºCalTest_Process
//º¯Êı¹¦ÄÜ£ºĞ£×¼²âÊÔ´¦Àí
//Èë¿Ú²ÎÊı£ºÎŞ
//³ö¿Ú²ÎÊı£ºÎŞ
//´´½¨ÈÕÆÚ£º2015.08.31
//ĞŞ¸ÄÈÕÆÚ£º2015.08.31 10:29
//±¸×¢ËµÃ÷£ºÎŞ
//==========================================================
void CalTest_Process(u8 num)
{
	u8 *pt;
	u8 *pt2;
	
	u8 i;
	u8 blinkT;
	vu8 key;
	u8 count;//²½½ø¼ÆÊıÆ÷
	
	vu16 dat;
	vu32 temp;

	u8 f_disp=FALSE;//ÏÔÊ¾¸üĞÂ±êÖ¾

//	bool f_sort=FALSE;//·ÖÑ¡±êÖ¾
//	bool f_upper=FALSE;//Á¿³Ì¹ıÑ¹±êÖ¾
//	bool f_below=FALSE;//Á¿³ÌÇ·Ñ¹±êÖ¾
//	bool f_switch=FALSE;//Á¿³ÌÇĞ»»±êÖ¾

	vu16 set_high;//²âÊÔÖµÉÏÏŞ
	vu16 set_low;//²âÊÔÖµÏÂÏŞ
	vu16 ad_high;//ADÖµÉÏÏŞ
	vu16 ad_low;//ADÖµÏÂÏŞ

	Disp_Clr( );//ÇåÆÁ

	//¶ÁÈ¡Ğ£×¼ÖµÉÏÏÂÏŞ
//	i=MenuSelect;//µ±Ç°Ñ¡ÔñÏî
//	i*=4;//Ã¿Ïî4×Ö½Ú
	set_high=CalibrateLimit[i][0];//ÉÏÏŞ
	set_low=CalibrateLimit[i][1];//ÏÂÏŞ
//	i++;
//	ad_high=CalibrateLimit[i][0];//ÉÏÏŞ
//	ad_low=CalibrateLimit[i][1];//ÏÂÏŞ

	//¶ÁÈ¡µ±Ç°ÏîÄ¿µÄĞ£×¼Öµ
		i=11;//IR
	pt=(u8*)(&SaveData.Calibrate);//Ğ£×¼ÖµÊ×µØÖ·
	pt2=(u8*)(&Cal);//¸üĞÂÍ¨ÓÃĞ£×¼Öµ
	key=i*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
//	Electro_Test(1);
	//È«¾Ö±äÁ¿´¦Àí
	Voltage=0;//µçÑ¹
	Current=0;//µçÁ÷
	Resistance=0;//µç×è
 	Range=0;//Á¿³Ì³õÊ¼»¯
	F_100ms=FALSE;//100ms¶¨Ê±


	//Éù¹â×´Ì¬¿ØÖÆ
	Led_Pass_Off();//¹ØºÏ¸ñµÆ
	Led_Fail_Off();//¹Ø±¨¾¯µÆ
	Led_HV_On();//¿ª¸ßÑ¹µÆ
	Beep_One();//ÏìÒ»Éù

	count=0;//²½½ø¼ÆÊıÆ÷
	SetSystemMessage(MSG_TEST);//ÏµÍ³ĞÅÏ¢
	SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//ÉèÖÃÑÓÊ±Ê±¼ä£¬1000/10=100mS
	LcdAddr.y=1;
	LcdAddr.x=2;
	Disp_StrAt((u8 *)Debugtext);
	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)CalTestTab[num]);
	Da_Out(0);
	switch(num)
	{
		case 0://½»Á÷
			Dc_Output_Off();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_50);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			Da_Out(DefaultCalDaOut[0]);//4000VµÄDAÖµ2430
			//Range_Control(0);
			break;
		case 1:
			Dc_Output_On();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_400);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			Da_Out(DefaultCalDaOut[1]);//4000VµÄDAÖµ
			
			break;
		case 2:
			Dc_Output_On();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_400);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			Da_Out(DefaultCalDaOut[2]);

			break;
		case 3://Ö±Á÷
			
			//break;
		case 4:
			Dc_Output_Off();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_50);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			//Da_Out(610);//610
			Da_Out(DefaultCalDaOut[2]);
		break;
		case 5:
			Dc_Output_On();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_400);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			Da_Out(360);
		break;
		case 6:

		case 7:
		case 8:
		case 9:
		case 10:
			Dc_Output_On();//DCÊä³öºÍ²ÉÑù
			Frequency_Control(FREQ_400);//Êä³öÆµÂÊ¿ØÖÆ
			Sin_Clk_Enable();//Êä³öÕıÏÒ²¨ÆµÂÊ
			Plc_Start_On();//¿ªPLCÆô¶¯
			Da_Out(DefaultCalDaOut[2]);
			//Da_Out(610);//610
			break;
		default:
		Da_Out(0);
			break;
	
	}

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if( GetSoftTimerOut(DISP_SOFTTIMER) )//µÈ´ıÑÓÊ±½áÊø
		{
			F_100ms=TRUE;
			SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//ÉèÖÃÑÓÊ±Ê±¼ä£¬1000/10=100mS
		}

		if(F_100ms==TRUE)//100ms¶¨Ê±´¦Àí
		{
			
			F_100ms=FALSE;
			f_disp=TRUE;//ÏÔÊ¾¸üĞÂ

			//²âÊÔµÆÉÁË¸¿ØÖÆ
			blinkT++;//ÉÁË¸Ê±¼ä¼ÆÊ±
			blinkT%=9;
			if(blinkT<5)//µÆÉÁË¸Ê±¼ä
				Led_HV_On();//¿ª²âÊÔµÆ
			else
				Led_HV_Off();//¹Ø²âÊÔµÆ

		}

		//¶ÁÈ¡A/DÖµ
		Test_value.Test_I=Read_Ad_Ch1();//µçÑ¹ADÖµ  channel1  µçÁ÷
		Test_value.Test_v.Test_v=Read_Ad_Ch0();//µçÁ÷ADÖµ	
		//Read_Ad();//¶ÁÈ¡ADÖµ
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


 		//ÉÏÏÂÏŞÅĞ±ğ
//		if(f_sort==TRUE)
		{
//					if(MenuSelect==0)
//						dat=Voltage;
//					else
//						dat=Resistance;

			//ÉÏÏÂÏŞ±¨¾¯
			if((dat>set_high)||(dat<set_low))//³¬ÉÏÏÂÏŞ
			{
//				Beep_One();//·äÃùÆ÷ÏìÒ»Éù
			}
		}

		if(f_disp==TRUE)//ÏÔÊ¾¸üĞÂ
		{
			f_disp=FALSE;//ÏÔÊ¾¸üĞÂ
			LcdAddr.x=10; LcdAddr.y=0;

			Hex_Format(Cal[num].Num,Debug_Dot[num],4,TRUE);//Êı¾İ¸ñÊ½»¯µ½DispBuf
			Disp_StrAt(DispBuf);
//			LcdAddr.x=DATA_ADDR_X+WIDTH_OF_VALUE;
//			Hex_Format(Current,2,4,1);//Êı¾İ¸ñÊ½»¯µ½DispBuf
		}
		
		key=Key_Read();//¶ÁÈ¡°´¼ü
		switch(key)
		{
//			case KEY_SET:	//ÉèÖÃ¼ü
//			case L_KEY_SET:	//³¤°´ÉèÖÃ¼ü
//				break;
	
			case KEY_UP:	//ÉÏ¼ü
				count=0;//²½½ø¼ÆÊıÆ÷
				Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_UP:	//³¤°´ÉÏ¼ü
				count++;//²½½ø¼ÆÊıÆ÷
				if(count>10)//²½½ø¼ÆÊıÆ÷
					Cal[num].Num+=10;
				else
					Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_DOWN:		//ÏÂ¼ü
				count=0;//²½½ø¼ÆÊıÆ÷
				Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_DOWN:	//³¤°´ÏÂ¼ü
				count++;//²½½ø¼ÆÊıÆ÷
				if(count>10)//²½½ø¼ÆÊıÆ÷
					Cal[num].Num-=10;
				else
					Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_LEFT:		//×ó¼ü
//			case L_KEY_LEFT:	//³¤°´×ó¼ü
				count=0;//²½½ø¼ÆÊıÆ÷
				break;

			case KEY_RIGHT:		//ÓÒ¼ü
//			case L_KEY_RIGHT:	//³¤°´ÓÒ¼ü
				count=0;//²½½ø¼ÆÊıÆ÷
				break;

			case KEY_ENTER:		//È·ÈÏ¼ü
			case L_KEY_ENTER:	//³¤°´È·ÈÏ¼ü
				Sin_Clk_Disable();//Êä³öÕıÏÒ²¨ÆµÂÊ
				Plc_Start_Off();//¿ªPLCÆô¶¯
				Da_Out(0);//4000VµÄDAÖµ
//				Output_Off();//Êä³ö¹Ø±Õ
				Led_HV_Off();
				//¸üĞÂµ±Ç°ÏîÄ¿µÄĞ£×¼Öµ
					//i=5;//IR
//					pt=(u8*)(&SaveData.Calibrate);//Ğ£×¼ÖµÊ×µØÖ·
//				pt2=(u8*)(&Cal);//¸üĞÂÍ¨ÓÃĞ£×¼Öµ
				pt=(u8*)(&SaveData.Calibrate);//Ğ£×¼ÖµÊ×µØÖ·
				pt2=(u8*)(&Cal);//¸üĞÂÍ¨ÓÃĞ£×¼Öµ
				key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//Ğ£ÑéºÍ±£´æĞ£×¼Êı¾İ
//				SaveCalibrate();//±£´æĞ£×¼Öµ
				StoreCalDate();
				Led_HV_Off();
				return;
//				break;

//			case KEY_START:		//Æô¶¯¼ü
//			case L_KEY_START:	//³¤°´Æô¶¯¼ü
//				break;

			case KEY_RESET:		//¸´Î»¼ü
			case L_KEY_RESET:	//³¤°´¸´Î»¼ü
				Sin_Clk_Disable();//Êä³öÕıÏÒ²¨ÆµÂÊ
				Plc_Start_Off();//¿ªPLCÆô¶¯
				Da_Out(0);//4000VµÄDAÖµ
//				Output_Off();//Êä³ö¹Ø±Õ
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

