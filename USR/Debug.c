//==========================================================
//�ļ����ƣ�Debug.c
//�ļ����������������ӳ���
//�ļ��汾��Ver1.0
//�������ڣ�2015.10.26
//�޸����ڣ�2015.10.29 14:38
//�ļ����ߣ��ƺ���
//��ע˵������
//ע�������
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
//Ĭ��У׼����
u8 calitem;

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
//У׼ֵ�ϡ�����
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
//���Բ˵�
//==========================================================
//У���˵�
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
	"(11)1000 M   ADJ",
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
	"11.1000 M  ",

};
//==========================================================
//ȷ����ʾ
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
//�������ƣ�Disp_Debug_Menu
//�������ܣ���ʾ�˵�
//��ڲ�����index:�ڼ���
//���ڲ�������
//�������ڣ�2015.10.29
//�޸����ڣ�2015.10.29 14:42
//��ע˵������
//==========================================================
void Disp_Debug_Menu(u8 index)
{
	//��һ��
	LcdAddr.x=0;LcdAddr.y=0;
	Disp_StrAt((u8 *)&DebugMenu[index%DEBUG_MENU_MAX][0]);
	LcdAddr.x=9;LcdAddr.y=0;
	Lcd_SetAddr();
	
		
//	//�ڶ���
	LcdAddr.x=0;LcdAddr.y=1;
	Disp_StrAt((u8 *)EnterTab1);//��ʾȷ����ʾ
}

//==========================================================
//�������ƣ�Debug_Process
//�������ܣ��������ô���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.29
//�޸����ڣ�2015.10.29 14:43
//��ע˵������
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
	f_disp=TRUE;//��ʾ

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if(f_disp==TRUE)//��ʾ����
		{
			f_disp=FALSE;
			Disp_Debug_Menu(index);//��ʾ����	
			
		}

		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//���ü�
			//case L_KEY_SET:	//�������ü�
				Disp_Clr( );//����
				Res_Calibrate(index);//����У׼����

				f_disp=TRUE;
				break;
	
			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
				if(index<(DEBUG_MENU_MAX-1))index++;
				else index=0;
				calitem = index;
				f_disp=TRUE;//��ʾ
				break;

			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
				if(index>0)index--;
				else index=(DEBUG_MENU_MAX-1);
				calitem = index;
				f_disp=TRUE;//��ʾ
				break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				SetSystemStatus(SYS_STATUS_TEST);//����״̬
//				break;
	
			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				i=11;
				pt=(u8*)(&SaveData.Calibrate);//У׼ֵ�׵�ַ
				pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
				key=i*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//У��ͱ���У׼����
				StoreCalDate();//����У׼ֵ
				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				//SetSystemStatus(SYS_STATUS_IDLE);//����״̬
				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//�������ƣ�Default_Calibrate
//�������ܣ�����Ĭ��У׼ֵ
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.02.13
//�޸����ڣ�2015.08.31 10:29
//��ע˵������
//==========================================================
void Default_Calibrate(void)
{
	u8 key;

	Disp_Clr();//����
	LcdAddr.x=5;LcdAddr.y=0;
	Disp_Str("�ָ�Ĭ��ֵ?");//��ʾ
	LcdAddr.x=1;LcdAddr.y=1;
	Disp_Str("��<ȷ��>���ָ�,<��,��>������");//��ʾ

	while(SystemStatus==SYS_STATUS_DEBUG)
	{
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
//			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				break;
//	
//			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
//				break;
//	
//			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
//				break;
//	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
//				break;
//
			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				return;
//				break;

			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				LoadDefaultCalibrate();//����Ĭ��У׼ֵ
				LcdAddr.x=8;LcdAddr.y=20;
				Disp_Str("�ָ�Ĭ��ֵ�ɹ�");//��ʾ
//				Beep_One();//��������һ��
//				Delay_100ms(12);//��ʱ1.2s
				return;
//				break;
//	
//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				return;
//				break;
			
			default:
				break;
		}
	}
}

//==========================================================
//��ԵУ׼�˵�

//==========================================================
//��ԵУ׼��
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
//�������ƣ�Res_Calibrate
//�������ܣ�����У׼����
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.02.13
//�޸����ڣ�2015.08.31 10:29
//��ע˵������
//==========================================================
void Res_Calibrate(u8 num)
{
	u8 i;
	
	u8 key;
	u8 dot,lenth;
	u16 set_high,set_low;
	u8 F_Disp;//��ʾ���±�־
	u8 *pt;
	u8 *pt2;
	F_Disp=TRUE;//��ʾ����
//	MenuSelect=0;//ȡ��ǰ��

	delay_ms(50);//Ӳ�����

	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)&DebugMenu[num][0]);//��ǰ�������ʾ
	LcdAddr.y=1;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)Debugext);
	//CalibrateLimit	
	for(i=0;i<DEBUG_MENU_MAX;i++)
	{
		if((Cal[i].Num>CalibrateLimit[num][0])||(Cal[i].Num<CalibrateLimit[num][1]))
			Cal[i].Num=CalibrateLimitvalue[i];
	
	}
	pt=(u8*)(&SaveData.Calibrate);//У׼ֵ�׵�ַ
	pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
	key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
	set_high=CalibrateLimit[num][0];//����
	set_low=CalibrateLimit[num][1];//����
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

//		Test_value.Test_I=Read_Channel(1);//��ѹADֵ  channel1  ����
//		AD7705_init(0);
//		Test_value.Test_v.Test_v=Read_Channel(0);//����ADֵ	
	i=1;
	//while(SystemStatus==SYS_STATUS_DEBUG)
	while(i)
	{
//		Read_Ad();
//		Get_Result();
		if(F_Disp==TRUE)
		{
			F_Disp=FALSE;//��ʾ����
			dot=Debug_Dot[num];
			lenth=4;
			Hex_Format(Cal[num].Num, dot, lenth, FALSE);
			LcdAddr.y=0;
			LcdAddr.x=10;
			Disp_StrAt(DispBuf);
			
			LcdAddr.y=0;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)&DebugMenu[num][0]);//��ǰ�������ʾ
			LcdAddr.y=1;
			LcdAddr.x=0;
			Disp_StrAt((u8 *)Debugext);
//			LcdAddr.x=15;
//			Lcd_SetAddr();

		}				
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//���ü�
			case L_KEY_SET:	//�������ü�
				CalTest_Process(num);//У׼���Դ���
				Disp_Clr( );//����
				F_Disp=TRUE;//��ʾ����
				i=0;
				break;

//			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
//				break;
	
//			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
//				break;

			case KEY_UP:	//���
				
//					if(Cal[num].Num>set_high)
//						Cal[num].Num=set_low;
//					
//					else
//						Cal[num].Num++;	
					F_Disp=TRUE;
			break;
			case L_KEY_UP:	//�������
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
//				F_Disp=TRUE;//��ʾ����
				break;

			case KEY_DOWN:		//�Ҽ�

				F_Disp=TRUE;
				break;
			case L_KEY_DOWN:	//�����Ҽ�

				F_Disp=TRUE;

				break;
	
			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
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
	
			case KEY_START:		//������
//			case L_KEY_START:	//����������
				CalTest_Process(num);//У׼���Դ���
				Disp_Clr( );//����
				F_Disp=TRUE;//��ʾ����
				i=0;
				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				return;
//				break;
			
			default:
				break;
		}
		
	}
	
}

//==========================================================
//�������ƣ�CalTest_Process
//�������ܣ�У׼���Դ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.08.31
//�޸����ڣ�2015.08.31 10:29
//��ע˵������
//==========================================================
void CalTest_Process(u8 num)
{
	u8 *pt;
	u8 *pt2;
	
	u8 i;
	u8 blinkT;
	vu8 key;
	u8 count;//����������
	
	vu16 dat;
	vu32 temp;

	u8 f_disp=FALSE;//��ʾ���±�־

//	bool f_sort=FALSE;//��ѡ��־
//	bool f_upper=FALSE;//���̹�ѹ��־
//	bool f_below=FALSE;//����Ƿѹ��־
//	bool f_switch=FALSE;//�����л���־

	vu16 set_high;//����ֵ����
	vu16 set_low;//����ֵ����
	vu16 ad_high;//ADֵ����
	vu16 ad_low;//ADֵ����

	Disp_Clr( );//����

	//��ȡУ׼ֵ������
//	i=MenuSelect;//��ǰѡ����
//	i*=4;//ÿ��4�ֽ�
	set_high=CalibrateLimit[i][0];//����
	set_low=CalibrateLimit[i][1];//����
//	i++;
//	ad_high=CalibrateLimit[i][0];//����
//	ad_low=CalibrateLimit[i][1];//����

	//��ȡ��ǰ��Ŀ��У׼ֵ
		i=11;//IR
	pt=(u8*)(&SaveData.Calibrate);//У׼ֵ�׵�ַ
	pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
	key=i*sizeof(Cal_TypeDef);
	for(i=0;i<key;i++)
	{
		*pt2++=*pt++;
	}
//	Electro_Test(1);
	//ȫ�ֱ�������
	Voltage=0;//��ѹ
	Current=0;//����
	Resistance=0;//����
 	Range=0;//���̳�ʼ��
	F_100ms=FALSE;//100ms��ʱ


	//����״̬����
	Led_Pass_Off();//�غϸ��
	Led_Fail_Off();//�ر�����
	Led_HV_On();//����ѹ��
	Beep_One();//��һ��

	count=0;//����������
	SetSystemMessage(MSG_TEST);//ϵͳ��Ϣ
	SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//������ʱʱ�䣬1000/10=100mS
	LcdAddr.y=1;
	LcdAddr.x=2;
	Disp_StrAt((u8 *)Debugtext);
	LcdAddr.y=0;
	LcdAddr.x=0;
	Disp_StrAt((u8 *)CalTestTab[num]);
	Da_Out(0);
	switch(num)
	{
		case 0://����
			Dc_Output_Off();//DC����Ͳ���
			Frequency_Control(FREQ_50);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			Da_Out(DefaultCalDaOut[0]);//4000V��DAֵ2430
			//Range_Control(0);
			break;
		case 1:
			Dc_Output_On();//DC����Ͳ���
			Frequency_Control(FREQ_400);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			Da_Out(DefaultCalDaOut[1]);//4000V��DAֵ
			
			break;
		case 2:
			Dc_Output_On();//DC����Ͳ���
			Frequency_Control(FREQ_400);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			Da_Out(DefaultCalDaOut[2]);

			break;
		case 3://ֱ��
			
			//break;
		case 4:
			Dc_Output_Off();//DC����Ͳ���
			Frequency_Control(FREQ_50);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			//Da_Out(610);//610
			Da_Out(DefaultCalDaOut[2]);
		break;
		case 5:
			Dc_Output_On();//DC����Ͳ���
			Frequency_Control(FREQ_400);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			Da_Out(360);
		break;
		case 6:

		case 7:
		case 8:
		case 9:
		case 10:
			Dc_Output_On();//DC����Ͳ���
			Frequency_Control(FREQ_400);//���Ƶ�ʿ���
			Sin_Clk_Enable();//������Ҳ�Ƶ��
			Plc_Start_On();//��PLC����
			Da_Out(DefaultCalDaOut[2]);
			//Da_Out(610);//610
			break;
		default:
		Da_Out(0);
			break;
	
	}

	while(GetSystemStatus()==SYS_STATUS_DEBUG)
	{
		if( GetSoftTimerOut(DISP_SOFTTIMER) )//�ȴ���ʱ����
		{
			F_100ms=TRUE;
			SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//������ʱʱ�䣬1000/10=100mS
		}

		if(F_100ms==TRUE)//100ms��ʱ����
		{
			
			F_100ms=FALSE;
			f_disp=TRUE;//��ʾ����

			//���Ե���˸����
			blinkT++;//��˸ʱ���ʱ
			blinkT%=9;
			if(blinkT<5)//����˸ʱ��
				Led_HV_On();//�����Ե�
			else
				Led_HV_Off();//�ز��Ե�

		}

		//��ȡA/Dֵ
		Test_value.Test_I=Read_Ad_Ch1();//��ѹADֵ  channel1  ����
		Test_value.Test_v.Test_v=Read_Ad_Ch0();//����ADֵ	
		//Read_Ad();//��ȡADֵ
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
			
			if(num == 10)
			{
				Cal[num].NumAd=Res_count.i * 10;
			}else{
				Cal[num].NumAd=Res_count.i;
			}
		
		}


 		//�������б�
//		if(f_sort==TRUE)
		{
//					if(MenuSelect==0)
//						dat=Voltage;
//					else
//						dat=Resistance;

			//�����ޱ���
			if((dat>set_high)||(dat<set_low))//��������
			{
//				Beep_One();//��������һ��
			}
		}

		if(f_disp==TRUE)//��ʾ����
		{
			f_disp=FALSE;//��ʾ����
			LcdAddr.x=10; LcdAddr.y=0;

			Hex_Format(Cal[num].Num,Debug_Dot[num],4,TRUE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);
//			LcdAddr.x=DATA_ADDR_X+WIDTH_OF_VALUE;
//			Hex_Format(Current,2,4,1);//���ݸ�ʽ����DispBuf
		}
		
		key=Key_Read();//��ȡ����
		switch(key)
		{
//			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				break;
	
			case KEY_UP:	//�ϼ�
				count=0;//����������
				Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_UP:	//�����ϼ�
				count++;//����������
				if(count>10)//����������
					Cal[num].Num+=10;
				else
					Cal[num].Num++;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_DOWN:		//�¼�
				count=0;//����������
				Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;

			case L_KEY_DOWN:	//�����¼�
				count++;//����������
				if(count>10)//����������
					Cal[num].Num-=10;
				else
					Cal[num].Num--;
				if(Cal[num].Num>CalibrateLimit[num][0])
					Cal[num].Num=CalibrateLimit[num][1];
				break;
	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
				count=0;//����������
				break;

			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				count=0;//����������
				break;

			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				Sin_Clk_Disable();//������Ҳ�Ƶ��
				Plc_Start_Off();//��PLC����
				Da_Out(0);//4000V��DAֵ
//				Output_Off();//����ر�
				Led_HV_Off();
				//���µ�ǰ��Ŀ��У׼ֵ
					//i=5;//IR
//					pt=(u8*)(&SaveData.Calibrate);//У׼ֵ�׵�ַ
//				pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
				pt=(u8*)(&SaveData.Calibrate);//У׼ֵ�׵�ַ
				pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
				key=DEBUG_MENU_MAX*sizeof(Cal_TypeDef);
				for(i=0;i<key;i++)
				{
					*pt++=*pt2++;
				}
				//У��ͱ���У׼����
//				SaveCalibrate();//����У׼ֵ
				StoreCalDate();
				Led_HV_Off();
				return;
//				break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				break;

			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				Sin_Clk_Disable();//������Ҳ�Ƶ��
				Plc_Start_Off();//��PLC����
				Da_Out(0);//4000V��DAֵ
//				Output_Off();//����ر�
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

