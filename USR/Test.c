//==========================================================
//�ļ����ƣ�Test.c
//�ļ����������Գ���
//�ļ��汾��Ver1.0
//�������ڣ�2014.12.29
//�޸����ڣ�2015.09.06 15:06
//�ļ����ߣ�
//��ע˵������
//ע�������
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
#define POWERON_DISP_TIME ((u8)20)	//������ʾ������ʱ20*100mS=2S

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
	   unsigned char  ARC:4;	   //�绡������0000���رյ绡��⣬1001���
	   unsigned char  ACWF:1;    //������ѹƵ�ʣ�1��ʾ60Hz��0��ʾ50Hz
	   unsigned char  ACDC:1;    //����0��ֱ��1
       unsigned char  item:2;    //������Ŀ
      
       
      
   }BIT_FLAG;
}U2;

//==========================================================
//�������ƣ�Power_Process
//�������ܣ��ϵ紦��
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.12.29
//�޸����ڣ�2015.08.18 10:20
//��ע˵������������SET����У׼����ģʽ
//==========================================================
void Power_Process(void)
{
	u8 i;
	u8 key;
	
	Hardware_Init();//Ӳ����ʼ��
	Amp_Output_Off();//��������ر�
	Sin_Clk_Disable();//��ֹ���Ҳ�Ƶ�����

	InitGlobalValue();//��ʼ��ȫ�ֱ���
	ReadGroup();
	ReadGroup();
	ReadSetByGroup();
	ReadPselect();
//	Readaddr();
	ReadCalData();//��ȡ��������
	Parameter_valuecomp();//�Ƚ����ò���
	if(SaveData.Group>GROUP_MAX)
		SaveData.Group=0;
//	SaveData.Factory.BootNum++;//��������	
//	SaveFactory();//���濪������

	
	Beep_Long();//����������һ��
	Beep_Off();
	Disp_PowerOn_Menu();//��ʾ��������

	MenuIndex=0;//�����˵���
	i=0;//��ʾ��ʱ

	while(GetSystemStatus()==SYS_STATUS_POWER)
	{
		i++;
		if(i>POWERON_DISP_TIME)//��ʱ20*100mS=2s���Զ��˳�
			SetSystemStatus(SYS_STATUS_IDLE);//����״̬
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)

		switch(key)
		{
			case KEY_LEFT:
			case L_KEY_LEFT:
				SetSystemStatus(SYS_STATUS_DEBUG);//����״̬
				Beep_One();//��������һ��
				
			break;
			case KEY_SET:		//���ü�
			case L_KEY_SET:		//�������ü�
				
				break;
	
			case KEY_UP:		//�ϼ�
			case L_KEY_UP:		//�����ϼ�
				break;
	
			case KEY_DOWN:		//�¼�
			case L_KEY_DOWN:	//�����¼�
				break;
	
//			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
//				break;

			case KEY_RIGHT:		//�Ҽ�
			case L_KEY_RIGHT:	//�����Ҽ�
				break;

			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				break;
	
			case KEY_START:		//������
//			case L_KEY_START:	//����������
				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				i=POWERON_DISP_TIME;//��ʾ��ʱ����
				break;
			
			default:
				break;
		}
	}
	Amp_Output_On();//���������
}

//==========================================================
//�������ƣ�Idle_Process
//�������ܣ�����������
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.12.15
//�޸����ڣ�2015.08.20 10:49
//��ע˵������
//==========================================================
void Idle_Process(void)
{
	u8 key;
	u8 index;

	//ϵͳ��Ϣ����
	SetSystemMessage(MSG_IDLE);//ϵͳ��Ϣ-����
	Disp_Idle_Menu();//��ʾ�������
	Led_Fail_Off();
	Led_Pass_Off();
	run_stemp=0;
	
	while(GetSystemStatus()==SYS_STATUS_IDLE)
	{
		if(/*ComBuf.rec.end || */FacBuf.rec.end)
		{
			Uart_Process();//���ڴ���
		}
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//�ȴ�����(100*10ms/10=100ms)
		switch(key)
		{
			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
				SetSystemStatus(SYS_STATUS_SETUP);//����״̬
				break;
	
			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
				if(MenuIndex==0)//�������ò˵�
				{
//					if(Password_Check())//����У��,TRUE��Ч
					{
						SaveData.Group++;
						if(SaveData.Group>SET_GROUP_MAX)
							SaveData.Group=0;
						ReadSetByGroup();//��ȡ��ǰ���Ĳ��Բ���
						Parameter_valuecomp();//�Ƚ����ò���
						SaveGroup();//�������
						Disp_Clr( );//����
						Disp_Idle_Menu();//��ʾ�������
					}
				}
				break;
	
			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
				if(MenuIndex==0)//�������ò˵�
				{
//					if(Password_Check())//����У��,TRUE��Ч
					{
						if(SaveData.Group)
							SaveData.Group--;
						else
							SaveData.Group=SET_GROUP_MAX;
						ReadSetByGroup();//��ȡ��ǰ���Ĳ��Բ���
						Parameter_valuecomp();//�Ƚ����ò���
						SaveGroup();//�������
						Disp_Clr( );//����
						Disp_Idle_Menu();//��ʾ�������
					}
				}
				break;
	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
				index=MenuIndex?MenuIndex-1:(IDLE_MENU_MAX-1);
				MenuIndex=index;
//				Disp_Idle_List();//��ʾ�����˵��б�
				break;

			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				index=(MenuIndex<(IDLE_MENU_MAX-1))?MenuIndex+1:0;
				MenuIndex=index;
//				Disp_Idle_List();//��ʾ�����˵��б�
				break;

			case KEY_START:		//������
			case L_KEY_START:	//����������
//				if(SaveData.System.Uart!=TRUE)//���ڿ�ʼʱ��������Ч
					SetSystemStatus(SYS_STATUS_START);//��������״̬
			F_Fail=0;
				break;
	
			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
//				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				MenuIndex=0;//�����˵���
			F_Fail=0;
//				Disp_Idle_List();//��ʾ�����˵��б�
				break;
			
			default:
				break;
		}
	}
}


//==========================================================
//�������ƣ�Setup_Process
//�������ܣ����ó���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.06
//�޸����ڣ�2015.08.19 08:56
//��ע˵������
//==========================================================
void Setup_Process(void)
{
	
		
		Step_Setup();//�������ô���
	
	

}

//==========================================================
//�������ƣ�Start_Process
//�������ܣ��������Դ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.26
//�޸����ڣ�2015.08.22 15:42
//��ע˵������
//ע�������
//==========================================================
void Start_Process(void)
{
	while(GetSystemStatus()==SYS_STATUS_START)
	{
		//ȫ�ֱ�������
		StepIndex=0;//��һ����ʼ
		TotalStep=0;//�����ܲ���
		F_Fail=FALSE;//�����ʧ�ܱ�־

		//״̬����
		Da_Out(0);//���ź�D/A����ر�
		Sin_Clk_Disable();//��ֹ���Ҳ�Ƶ�����
		

		//ϵͳ״̬����
		SetSystemMessage(MSG_RAMP);//ϵͳ��Ϣ-����
		SetSystemStatus(SYS_STATUS_TEST);//ϵͳ״̬-����
	}
}

//==========================================================
//�������ƣ�Output_Off
//�������ܣ�����ر�
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.09.01 
//�޸����ڣ�2015.09.04 14:59
//��ע˵������
//==========================================================
void Output_Off(void)
{
	Da_Out(0);//���ź�D/A����ر�
	Sin_Clk_Disable();//��ֹ���Ҳ�Ƶ�����
	delay_ms(100);//��ʱ100ms
	Led_HV_Off();//�رո�ѹ��
}

//==========================================================
//�������ƣ�Test_Init
//�������ܣ����Գ�ʼ��
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.25 
//�޸����ڣ�2015.08.26 13:48
//��ע˵������ʱԼ100ms/12M
//==========================================================
void Test_Init(void)
{
	u8 i;
	u8 len;
	u8 *pt;
	u8 *pt2;
	u32 dat;
	u16 set_item;//���õ������Ŀ
	u16 set_out;//���õ����ֵ
	u16 set_ramp;//���õĻ�������ʱʱ��
	vu8 set_arc;//���õĵ绡�ȼ�
	vu8 set_acdc;//ѡ��AD����DC

	//ϵͳ��Ϣ����
	SetSystemMessage(MSG_RAMP);//ϵͳ��Ϣ-����

	//��ȡ����ֵ
	
	
	set_item=SaveData.Setup.Group_Item;//��ǰ����
	set_acdc=SaveData.Setup.Item;
	
	U2.BIT_FLAG.ACDC = SaveData.Setup.Item;//��λ������w_ma:d5
	
	set_arc=(u8)SaveData.Setup.Arc;//�绡�ȼ�
	Arc_Out(0);
	//��ȡУ׼ֵ
	if(set_item==W_SETUP)
	{
		Range=0;
		ra_flag=0;
		set_out=SaveData.Setup.Output*10;//���õ����
		if(SaveData.Setup.RampDelay == 1)
		{
			set_ramp = 2;
		}else{
			set_ramp=SaveData.Setup.RampDelay;//��������ʱʱ��
		}
		dat=set_out;
		i=3;//ACW
		rangelomit_low=240;
			rangr_limit_high=3800;
		if(set_acdc==0)//AC
		{
		
			//pt=(u8*)(&SaveData.Calibrate.AcwVol);//У׼ֵ�׵�ַ
			
			dat*=DefaultCalDaOut[0];
			dat/=SaveData.Calibrate.AcwVol[0].Num;
			
			
		}
		else
		{
			//pt=(u8*)(&SaveData.Calibrate.DcwVol);//У׼ֵ�׵�ַ
			dat*=DefaultCalDaOut[1];
			dat/=SaveData.Calibrate.DcwVol[0].Num;
		}
	}
	else if(set_item==I_SETUP)//��Ե
	{
		rangelomit_low=360;
			rangr_limit_high=3800;
		ra_flag=1;
		set_ramp=0;//��������ʱʱ��
		set_out=SaveData.Setup.I_Volt*10;//���õ����
		dat=set_out;
		i=5;//IR
		//pt=(u8*)(&SaveData.Calibrate.IrVol);//У׼ֵ�׵�ַ
		dat*=DefaultCalDaOut[2];
		dat/=SaveData.Calibrate.IrVol[0].Num;
		set_ramp=0;
		
	}
	else if(set_item==I_WSETUP)
	{
		set_out=SaveData.Setup.I_Volt*10;//���õ����
		if(SaveData.Setup.RampDelay == 1)
		{
			set_ramp = 2;
		}else{
			set_ramp=SaveData.Setup.RampDelay;//��������ʱʱ��
		}
		dat=set_out;
		if(run_stemp==0)
		{
			rangelomit_low=360;
			rangr_limit_high=3800;
			ra_flag=1;
		
			i=5;//IR
			set_ramp=0;//��������ʱʱ��=0
			//pt=(u8*)(&SaveData.Calibrate.IrVol);//У׼ֵ�׵�ַ
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
			set_out=SaveData.Setup.Output*10;//���õ����
			dat=set_out;
			
			i=3;//ACW
			if(set_acdc==0)//AC
			{
			
				//pt=(u8*)(&SaveData.Calibrate.AcwVol);//У׼ֵ�׵�ַ
				dat*=DefaultCalDaOut[0];
				dat/=SaveData.Calibrate.AcwVol[0].Num;
				
			}
			else
			{
				//pt=(u8*)(&SaveData.Calibrate.DcwVol);//У׼ֵ�׵�ַ
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
				set_ramp=SaveData.Setup.RampDelay;//��������ʱʱ��
			}
			set_out=SaveData.Setup.Output*10;//���õ����
			dat=set_out;
			i=3;//ACW
			ra_flag=0;
			if(set_acdc==0)//AC
			{
				
				dat*=DefaultCalDaOut[0];
				dat/=SaveData.Calibrate.AcwVol[0].Num;
				//pt=(u8*)(&SaveData.Calibrate.AcwVol);//У׼ֵ�׵�ַ
				
			}
			else
			{
				dat*=DefaultCalDaOut[1];
				dat/=SaveData.Calibrate.DcwVol[0].Num;
				//pt=(u8*)(&SaveData.Calibrate.DcwVol);//У׼ֵ�׵�ַ
			}
		
		}else
		{
			rangelomit_low=360;
			rangr_limit_high=3800;
			set_ramp=0;//��������ʱʱ��
			set_out=SaveData.Setup.I_Volt*10;//���õ����
			dat=set_out;
			i=5;//IR
			ra_flag=1;
			//pt=(u8*)(&SaveData.Calibrate.IrVol);//У׼ֵ�׵�ַ
			dat*=DefaultCalDaOut[2];
			dat/=SaveData.Calibrate.IrVol[0].Num;
		
			set_ramp=0;
		}
		
	}
//	
	pt=(u8*)((&SaveData.Calibrate));
	len=11;
	pt2=(u8*)(&Cal);//����ͨ��У׼ֵ
	len=11*sizeof(Cal_TypeDef);
	for(i=0;i<len;i++)
	{
		*pt2++=*pt++;
	}

	//ȫ�ֱ�������
	Voltage=0;//��ѹ
	Current=0;//����
	Resistance=0;//����
	TestTime=0;//ʱ��
 	AdCount=0;//A/Dֵ��������

	RampStepYs=0;//������������
	RampStepFd=0;//������������
	RampStepTime=0;//��������ʱ��
	TestOut=0;//�������
	FullOut=0;//�������
	F_100ms=FALSE;//100ms��ʱ
	
	//AD���������
	for(i=0;i<(AD_BUF_LENGTH);i++)
	{
		Vbuf[i]=0;
		Ibuf[i]=0;
	}

	//����D/A���ֵ����
	
	
	
	FullOut=(u16)dat;

	//����ֵ����
	if(set_ramp)//����ʱ��
	{
		RampStepTime=1;//��������ʱ��,100ms
		dat=FullOut;dat/=set_ramp;
		RampStepFd=(u16)dat;//������������
		dat=FullOut;dat%=set_ramp;
		RampStepYs=(u16)dat;//������������
		if(RampStepFd<1)
		{
			RampStepTime=10;//��������ʱ��,1s
			dat=FullOut;dat*=10;dat/=set_ramp;
			RampStepFd=(u16)dat;//������������
			dat=FullOut;dat*=10;dat%=set_ramp;
			RampStepYs=(u16)dat;//������������
			if(RampStepFd<1)
			{
				RampStepTime=100;//��������ʱ��,10s
				dat=FullOut;dat*=10;dat/=set_ramp;
				RampStepFd=(u16)dat;//������������
				dat=FullOut;dat*=10;dat%=set_ramp;
				RampStepYs=(u16)dat;//������������
			}
		}
	}
//	Dma_Int();
	
	//�������
	switch(set_item)//����
	{
		case I_SETUP:
			Dc_Output_On();//DC����Ͳ���
			Frequency_Control(FREQ_400);//���Ƶ�ʿ���
			SetSystemMessage(MSG_TEST);//ϵͳ��Ϣ-���ز���
		
		

			break;

		case W_SETUP:
			if(set_acdc)//ֱ��
			{
				Dc_Output_On();//DC����Ͳ���
				Frequency_Control(FREQ_400);//���Ƶ�ʿ���
				Arc_Out(set_arc);//�绡�ȼ����
			}
			else
			{
				Dc_Output_Off();//DC����Ͳ����ر�
				if(SaveData.Setup.Freq)
					Frequency_Control(FREQ_60);//���Ƶ�ʿ���
				else
					Frequency_Control(FREQ_50);//���Ƶ�ʿ���
				Arc_Out(set_arc);//�绡�ȼ����
			
			}
			break;

		case I_WSETUP:
			if(run_stemp==0)
			{
				Dc_Output_On();//DC����Ͳ���
				Frequency_Control(FREQ_400);//���Ƶ�ʿ���
				SetSystemMessage(MSG_TEST);//ϵͳ��Ϣ-���ز���
				
			}
			else
			{
			
				if(set_acdc)//ֱ��
				{
					Dc_Output_On();//DC����Ͳ���
					Frequency_Control(FREQ_400);//���Ƶ�ʿ���
					Arc_Out(set_arc);//�绡�ȼ����
				}
				else
				{
					Dc_Output_Off();//DC����Ͳ����ر�
					if(SaveData.Setup.Freq)
						Frequency_Control(FREQ_60);//���Ƶ�ʿ���
					else
						Frequency_Control(FREQ_50);//���Ƶ�ʿ���
					Arc_Out(set_arc);//�绡�ȼ����
				
				}
			}
			break;

		case W_ISETUP:
			if(run_stemp==0)
			{
				if(set_acdc)//ֱ��
				{
					Dc_Output_On();//DC����Ͳ���
					Frequency_Control(FREQ_400);//���Ƶ�ʿ���
					Arc_Out(set_arc);//�绡�ȼ����
				}
				else
				{
					Dc_Output_Off();//DC����Ͳ����ر�
					if(SaveData.Setup.Freq)
						Frequency_Control(FREQ_60);//���Ƶ�ʿ���
					else
						Frequency_Control(FREQ_50);//���Ƶ�ʿ���
					Arc_Out(set_arc);//�绡�ȼ����
				
				}
			}else
				{
					Dc_Output_On();//DC����Ͳ���
					Frequency_Control(FREQ_400);//���Ƶ�ʿ���
					SetSystemMessage(MSG_TEST);//ϵͳ��Ϣ-���ز���
				}
			break;
	
		default:
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//������ͣ״̬
			return;
			
	}	
	
	Da_Out(0);
	Sin_Clk_Enable();//������Ҳ�Ƶ��
	Plc_Start_On();//��PLC����
 	Range=0;//���̳�ʼ��
	Range_Control(Range);//���̿���
	

	//����״̬����
	Led_Pass_Off();//�غϸ��
	Led_Fail_Off();//�ر�����
	Led_HV_On();//����ѹ��
//	if(SaveData.System.Beep)
//		Beep_One();//��һ��

	//��ʾ���Խ���
	LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//	Disp_Str("������..",0);//��ʾ����״̬
	//��ʾ���Բ���
	LcdAddr.x=TITLE_ADDR_X+14; LcdAddr.y=TITLE_ADDR_Y;
//	Disp_Str(&ItemTab[set_item],0);//��ʾ����

	//��ʾ������
//	Lcd_Draw_Line(0,TITLE_ADDR_Y+18,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
//	Lcd_Draw_Line(0,TITLE_ADDR_Y+20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�

	//��ʾ�������
	LcdAddr.x=STEP_ADDR_X; LcdAddr.y=STEP_ADDR_Y+TotalStep*HEIGHT_OF_STEP;
//	Disp_Str(&NumTab[TotalStep][0],0);//��ʾ�����ܲ���
//	Disp_Str(&ItemCharTab[set_item],0);//��ʾ������д�ַ�

	//��ʾ��ʼ��
	LcdAddr.x=DATA_ADDR_X; LcdAddr.y=DATA_ADDR_Y+HEIGHT_OF_STEP*TotalStep;
	switch(set_item)//����Ŀ��ʾ
	{
		case ITEM_ACW:
		case ITEM_DCW:
//			Disp_Txt_Str("-----V -----mA -----s ");//��ʾ����ֵ
			break;

		case ITEM_IR:
//			Disp_Txt_Str("----V  ----M  -----s ");//��ʾ����ֵ
			break;

		case ITEM_GND:
//			Disp_Txt_Str("-----A ----m  -----s ");//��ʾ����ֵ
			break;
		
		default:
			break;
	}

	//��ʾ������Ϣ
	LcdAddr.x=MSG_ADDR_X;
	Disp_SysMessage();//��ʾ��Ϣ

}

//==========================================================
//�������ƣ�Test_Process
//�������ܣ�����������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.25 
//�޸����ڣ�2015.09.06 15:06
//��ע˵������ֵˢ��8.4ms��״̬ˢ��3.6ms��12MHz/12����
//��ע˵����ȱ�ٵ绡�жϡ������жϴ���
//==========================================================
void Test_Process(void)
{
	vu8 key;
	vu8 max;//�������
	vu16 sortT;//��ѡ��ʱ
	vu8 stepT;//����ʱ���ʱ
	vu8 blinkT;//��˸ʱ���ʱ
//	char sendbuff[20];
	vu32 dat;
	vu32 temp;

	bool f_disp=FALSE;//��ʾ���±�־
	bool f_msgdisp=FALSE;//��Ϣ��ʾ��־

	bool f_sort=FALSE;//��ѡ��־
	bool f_upper=FALSE;//���̹�ѹ��־
	bool f_below=FALSE;//����Ƿѹ��־
	bool f_switch=FALSE;//�����л���־

	vu16 set_item;//������Ŀ
//	vu16 set_time;//���õĲ���ʱ��
//	vu16 set_ramp;//���õĻ�������ʱʱ��
//	vu16 set_high;//���õ�����
//	vu16 set_low;//���õ�����
	vu16 set_zero;//���õ���ֵ

//	Check_Parameter_Limit(StepIndex);//��ǰ����Ĳ�������ֵ���

	//��������ֵ
	Test_mid.set_item=SaveData.Setup.Group_Item;//��ǰ����
//	set_high=SaveData.Setup[StepIndex].High;//���õ�����
//	set_low=SaveData.Setup[StepIndex].Low;//���õ�����
//	set_time=SaveData.Setup[StepIndex].TestTime;//����ʱ��
//	set_ramp=SaveData.Setup[StepIndex].RampDelay;//��������ʱʱ��
//	set_zero=SaveData.Setup[StepIndex].Zero;//��ֵ
//	
	//����ֵ����
	switch(Test_mid.set_item)//��Ŀ
	{
		case I_SETUP://��Ե�������
			U2.BIT_FLAG.item = 1;
			Test_mid.set_high=SaveData.Setup.I_High;
			Test_mid.set_low=SaveData.Setup.I_Low;
			Test_mid.set_time=SaveData.Setup.I_Delay;
			max=2;//�������-4��
			break;

		case W_SETUP://��ѹ����
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
		
//			max=1;//�������-2��
			max=0;
			break;

		case I_WSETUP://��Ե��ѹ����
			U2.BIT_FLAG.item = 3;
			if(run_stemp==0)
			{
				Test_mid.set_high=SaveData.Setup.I_High;
				Test_mid.set_low=SaveData.Setup.I_Low;
				Test_mid.set_time=SaveData.Setup.I_Delay;
				max=2;//�������-4��
				
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

		case W_ISETUP://��ѹ��Ե����
			U2.BIT_FLAG.item = 2;
			if(run_stemp==0)
			{
				max=0;
//				max=1;//�������-1��
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

		case ITEM_NONE://�޲�����Ŀ
			break;

		default:
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-��ͣ����
			return;
			
	}		
	
	Test_Init();//���Գ�ʼ��
	

	stepT=0;//����ʱ���ʱ
	sortT=0;//��ѡ��ʱ
	blinkT=0;//��˸ʱ���ʱ
	Test_Time=0;
	Test_value.Test_Time=0;
	TestOut=0;
	Range=max;
	Range_Control(Range+ra_flag);
	while(GetSystemStatus()==SYS_STATUS_TEST)
	{
		sendflag = 0;
		if(F_100ms==TRUE)//100ms��ʱ����
		{
			F_100ms=FALSE;
			f_disp=TRUE;//��ʾ����

			if(sortT<9999)sortT++;

			if(GetSystemMessage()==MSG_RAMP)//ϵͳ��Ϣ-����
			{
				stepT++;//����ʱ���ʱ
				if(stepT>=RampStepTime)//��������ʱ��
				{
					stepT=0;//����ʱ���ʱ
					TestOut+=RampStepFd;//�������ֵ����
//					if(RampStepYs)//������������  ����
//					{
//						TestOut+=RampStepYs;//�������ֵ����
//					  	RampStepYs--;//������������
//					}
				}
				

				if(Test_value.Test_Time>=Test_mid.set_ramp)//����ʱ���б�
				{
					Test_value.Test_Time=0;//����ʱ������
					TestOut=FullOut;//�������ֵ����
					SetSystemMessage(MSG_TEST);//ϵͳ��Ϣ-���ز���
					f_msgdisp=TRUE;//��Ϣ��ʾ��־
				}
			}
			else
			{
				TestOut=FullOut;//�������ֵ����
				if(Test_mid.set_time>0)//����ʱ��Ϊ0����������
				{
					if(Test_value.Test_Time>=Test_mid.set_time)//����ʱ���б�
					{
						if(Test_mid.set_item == W_SETUP 
						|| (Test_mid.set_item == W_ISETUP && run_stemp == 0)
						|| (Test_mid.set_item == I_WSETUP && run_stemp == 1))
						{
							if(Voltage < SaveData.Setup.Output*0.8)
							{
								f_sort=TRUE;//��ѡ��־
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = W_F_LO;
							}else{
								SetSystemStatus(SYS_STATUS_TEST_PAUSE);//������ͣ״̬
								SetSystemMessage(MSG_PASS);//ϵͳ��Ϣ-���Ժϸ�
								f_msgdisp=TRUE;//��Ϣ��ʾ��־
							}
						}else{
							if(Voltage < SaveData.Setup.I_Volt*0.8)
							{
								f_sort=TRUE;//��ѡ��־
								SetSystemMessage(MSG_LOW);
								sendbuff2[2] = W_F_LO;
							}else{
								SetSystemStatus(SYS_STATUS_TEST_PAUSE);//������ͣ״̬
								SetSystemMessage(MSG_PASS);//ϵͳ��Ϣ-���Ժϸ�
								f_msgdisp=TRUE;//��Ϣ��ʾ��־
							}
						}
					}
				}
			}
			
			//�ź��������
			Da_Out(TestOut);//�ź�D/A���
			
			//���Ե���˸����
			blinkT++;//��˸ʱ���ʱ
			blinkT%=9;
			if(blinkT<5)//����˸ʱ��
				Led_Test_On();//�����Ե�
			else
				Led_Test_Off();//�ز��Ե�
			Disp_TestMessage();
		}

		//��ȡA/Dֵ
		Read_Ad();//��ȡADֵ
		Ad_Filter();//ADֵ�˲�
		Get_Result();//�������ֵ
		if(Test_mid.set_item == I_SETUP ||(Test_mid.set_item == W_ISETUP && run_stemp == 1) 
		|| (Test_mid.set_item == W_ISETUP && run_stemp == 1)
		|| (Test_mid.set_item == I_WSETUP && run_stemp == 0))
		{
			//�����Զ���������
			if(Current>rangr_limit_high)//������������
			{
				f_upper=TRUE;//���̹�ѹ��־
				f_below=FALSE;//����Ƿѹ��־
			}
			else if(Current<rangelomit_low)//������������
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
			if((Range<max)&&(f_below==TRUE))//���̷�����ҵ�ѹ
			{
				Range++;
				f_switch=TRUE;//�����л���־
			}
			if((Range>0)&&(f_upper==TRUE))//���̷�����ҹ�ѹ
			{
				Range--;
				f_switch=TRUE;//�����л���־
			}
		}else{
//			Range=0;
//			Range_Control(Range);//���̿���
		}
		if(f_switch==TRUE)//�����л���־
		{
			AdCount=0;//ADֵ�������
			for(key=0;key<(AD_BUF_LENGTH);key++)
			{
				Ibuf[key]=0;//AD���������
			}
			//Range=1;
			Range_Control(Range+ra_flag);//���̿���
			
			delay_ms(50);//Ӳ����ʱ
		}
		else
		{
			//��ֵ����ͼ������ֵ
			switch(Test_mid.set_item)//������
			{
				case W_SETUP://��ѹ
				//case ITEM_DCW:
					//��λ����
					if(Range==1)
						Test_value.Test_I/=10;
					//���ֵ�б�
					//dat=ACW_CURRENT_MAX;
					if(set_item==1)
						dat=DCW_CURRENT_MAX;
					else
						dat=ACW_CURRENT_MAX;
					if(Test_value.Test_I>dat)//���ֵ�б�
						Test_value.Test_I=TEST_VALUE_OVER;//�������
					else
					{
//						if(Current>set_zero)//��ֵ����
//							Current-=set_zero;
//						else
//							Current=0;
					}
//					if(f_switch==FALSE)
//					if(sortT>=Test_mid.set_ramp)//�б���ʱ
//						f_sort=TRUE;//��ѡ��־
					break;
	
				case I_SETUP://��Ե
					//��λ����
					if(Current)//����ֵ����
					{
						if(Resistance>IR_RESISTANCE_MAX)//���ֵ�б�
							Resistance=TEST_VALUE_OVER;//�������
					}
					else
					{
						Resistance=TEST_VALUE_OVER;//�������
					}
					if(f_switch==FALSE)
					if(Test_value.Test_Time>=SORT_TIME_MIN)//������Сʱ���ſ�ʼ��ѡ
					f_sort=TRUE;//��ѡ��־
					break;
		
				case I_WSETUP:
					if(run_stemp==0)
					{
						if(Current)//����ֵ����
						{
							//���ֵ�б�
							if(Resistance>IR_RESISTANCE_MAX)//���ֵ�б�
								Resistance=TEST_VALUE_OVER;//�������
						}
						else
						{
							Resistance=TEST_VALUE_OVER;//�������
						}
						if(f_switch==FALSE)
						if(Test_value.Test_Time>=SORT_TIME_MIN)//������Сʱ���ſ�ʼ��ѡ
							f_sort=TRUE;//��ѡ��־
						
					}
					else
					{
						if(Range==1)
						Test_value.Test_I/=10;
						//���ֵ�б�
						dat=ACW_CURRENT_MAX;
						if(set_item==1)
							dat=DCW_CURRENT_MAX;
						else
							dat=ACW_CURRENT_MAX;
						if(Test_value.Test_I>dat)//���ֵ�б�
							Test_value.Test_I=TEST_VALUE_OVER;//�������
						else
						{
	//						if(Current>set_zero)//��ֵ����
	//							Current-=set_zero;
	//						else
	//							Current=0;
						}
//						if(f_switch==FALSE)
//						if(sortT>=Test_mid.set_ramp)//�б���ʱ
//						f_sort=TRUE;//��ѡ��־
					}
					break;
				case W_ISETUP:
					if(run_stemp==0)
					{
						if(Range==1)
							Test_value.Test_I/=10;
						//���ֵ�б�
						dat=ACW_CURRENT_MAX;
						if(set_item==1)
							dat=DCW_CURRENT_MAX;
						else
							dat=ACW_CURRENT_MAX;
						if(Test_value.Test_I>dat)//���ֵ�б�
							Test_value.Test_I=TEST_VALUE_OVER;//�������
						else
						{
	//						if(Current>set_zero)//��ֵ����
	//							Current-=set_zero;
	//						else
	//							Current=0;
						}
//						if(f_switch==FALSE)
//						if(sortT>=Test_mid.set_ramp)//�б���ʱ
//						f_sort=TRUE;//��ѡ��־
					}
					else
					{
						if(Current)//����ֵ����
						{

							//���ֵ�б�
							if(Resistance>IR_RESISTANCE_MAX)//���ֵ�б�
								Resistance=TEST_VALUE_OVER;//�������
						}
						else
						{
							Resistance=TEST_VALUE_OVER;//�������
						}
						if(f_switch==FALSE)
						if(Test_value.Test_Time>=SORT_TIME_MIN)//������Сʱ���ſ�ʼ��ѡ
							f_sort=TRUE;//��ѡ��־
					
					}
					break;
				default:
					break;
			}
		}


 		//�������б�
		if(GetSystemMessage()==MSG_TEST)
		//if((f_sort==TRUE) )//�ǻ���
		if((f_sort==TRUE) && (f_switch==FALSE))//�ǻ���
		{
			switch(Test_mid.set_item)//������
			{
				case W_SETUP:
//					if(Test_value.Test_Time>=2)
//					{
						dat=Test_value.Test_I;
						if(dat>Test_mid.set_high)//������
						{
							if(SaveData.Setup.Item == 0)//AC
							{
								if(dat>1200)//������
								{
									SetSystemMessage(MSG_OFL);
								}else{
									SetSystemMessage(MSG_HIGH);
								}
							}
							
							if(SaveData.Setup.Item == 1)//DC
							{
								if(dat>5000)//������
								{
									SetSystemMessage(MSG_OFL);
								}else{
									SetSystemMessage(MSG_HIGH);
								}
							}
							
							
							sendbuff2[2] = W_F_HI;
						}
						if(dat<Test_mid.set_low)//������
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
						if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//������
						{
							SetSystemMessage(MSG_HIGH);
							sendbuff2[2] = I_HIGH;
						}
						if(dat<Test_mid.set_low)//������
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
							if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//������
							{
								SetSystemMessage(MSG_HIGH);
								sendbuff2[2] = I_HIGH;
							}else{
								sendbuff2[2] = I_PASS;
							}
							if(dat<Test_mid.set_low)//������
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
							if(dat>Test_mid.set_high)//������
							{
								if(SaveData.Setup.Item == 0)//AC
								{
									if(dat>1200)//������
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								
								if(SaveData.Setup.Item == 1)//DC
								{
									if(dat>5000)//������
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								sendbuff3[2] = W_F_HI;
							}
							if(dat<Test_mid.set_low)//������
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
							if(dat>Test_mid.set_high)//������
							{
								if(SaveData.Setup.Item == 0)//AC
								{
									if(dat>1200)//������
									{
										SetSystemMessage(MSG_OFL);
									}else{
										SetSystemMessage(MSG_HIGH);
									}
								}
								
								if(SaveData.Setup.Item == 1)//DC
								{
									if(dat>5000)//������
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
							if(dat<Test_mid.set_low)//������
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
							if((dat>Test_mid.set_high)&&(Test_mid.set_high!=0))//������
							{
								SetSystemMessage(MSG_HIGH);
								sendbuff3[2] = I_HIGH;
							}
							if(dat<Test_mid.set_low)//������
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
		
		//�����ޱ����͹�������
		if((GetSystemMessage()==MSG_HIGH)||(GetSystemMessage()==MSG_LOW)||
				(GetSystemMessage()==MSG_ARC)||(GetSystemMessage()==MSG_OVER)
			||(GetSystemMessage()==MSG_OFL))
		{
			F_Fail=TRUE;//����ʧ�ܱ�־
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-������ͣ
			f_disp=TRUE;//������ʾ���Խ��
			f_msgdisp=TRUE;//��Ϣ��ʾ��־
		}

		if(f_disp==TRUE)//��ʾ����
		{
//			memset(sendbuff,0,20);
			f_disp=FALSE;//��ʾ����
			LcdAddr.x=DATA_ADDR_X; LcdAddr.y=1;//DATA_ADDR_Y+HEIGHT_OF_STEP*TotalStep;
			
			switch(Test_mid.set_item)//��������Ŀ��ʾ
			{
				case W_SETUP:
					if(SaveData.Setup.Output>Voltage)
					{
						if(SaveData.Setup.Output-Voltage<=2)
						{
							Voltage=SaveData.Setup.Output;
							f_sort=TRUE;//��ѡ��־
						}
					
					}
					else
					{
						if(Voltage-SaveData.Setup.Output<=2)
						{
							Voltage=SaveData.Setup.Output;
							f_sort=TRUE;//��ѡ��־
						}
					}
					Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
					Disp_StrAt(DispBuf);//��ʾ����ֵ
					memset(sendbuff,0,20);
					sendflag = 1;
					memcpy(sendbuff,DispBuf,4);
					strcat(sendbuff,"kV;");
					
					sendbuff2[4] = (u8)(Voltage >> 8);
					sendbuff2[5] = (u8)(Voltage);
					
					
					LcdAddr.x=9;
					Hex_Format(Test_value.Test_I,2,4,FALSE);//���ݸ�ʽ����DispBuf
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
						Disp_StrAt(DispBuf);//��ʾ����ֵ
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
							//Disp_StrAt("-----");//��ʾ����ֵ
							Disp_StrAt(DispBuf);
							Disp_Str((u8*)"  ");
						}else if(GetSystemMessage()==MSG_OVER){
							memcpy(DispBuf,"BRK ",5);
							//Disp_StrAt("-----");//��ʾ����ֵ
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
						Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
						Disp_StrAt(DispBuf);//��ʾ����ֵ
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
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,TRUE);//���ݸ�ʽ����DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,TRUE);//���ݸ�ʽ����DispBuf
						}
						else
							Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//���ݸ�ʽ����DispBuf
						if(Resistance!=TEST_VALUE_OVER)
						{
							Disp_StrAt(DispBuf);//��ʾ����ֵ
							strcat(sendbuff1,(char*)DispBuf);
							USENDI.sendI = atof(DispBuf);					
							sendbuff2[6] = USENDI.s[0];
							sendbuff2[7] = USENDI.s[1];
							sendbuff2[8] = USENDI.s[2];
							sendbuff2[9] = USENDI.s[3];
						}
						else{
							Disp_StrAt(">9999");//��ʾ����ֵ
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
//						strcat(sendbuff,(char*)DispBuf);��
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
								f_sort=TRUE;//��ѡ��־
							}
						
						}
						else
						{
							if(Voltage-SaveData.Setup.Output<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//��ѡ��־
							}
						}
						Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
						Disp_StrAt(DispBuf);//��ʾ����ֵ
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
						Hex_Format(Test_value.Test_I,2,4,TRUE);//���ݸ�ʽ����DispBuf
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
							Disp_StrAt(DispBuf);//��ʾ����ֵ
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
								//Disp_StrAt("-----");//��ʾ����ֵ
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
								strcat(sendbuff,"mA;");
								sendflag = 0;
							}else if(GetSystemMessage()==MSG_OVER){
								memcpy(DispBuf,"BRK ",5);
								//Disp_StrAt("-----");//��ʾ����ֵ
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
//							Disp_StrAt(DispBuf);//��ʾ����ֵ
//							strcat(sendbuff1,(char*)DispBuf);
//							USENDI.sendI = atof(DispBuf);					
//							sendbuff3[6] = USENDI.s[0];
//							sendbuff3[7] = USENDI.s[1];
//							sendbuff3[8] = USENDI.s[2];
//							sendbuff3[9] = USENDI.s[3];
//						}
//						else
//						{
//							Disp_StrAt("-----");//��ʾ����ֵ
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
					Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
					Disp_StrAt(DispBuf);//��ʾ����ֵ
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
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,FALSE);//���ݸ�ʽ����DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,FALSE);//���ݸ�ʽ����DispBuf
						}
					else
						Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//���ݸ�ʽ����DispBuf
					if(Resistance!=TEST_VALUE_OVER)
					{
						Disp_StrAt(DispBuf);//��ʾ����ֵ
						strcat(sendbuff,(char*)DispBuf);
						USENDI.sendI = atof(DispBuf);					
						sendbuff2[6] = USENDI.s[0];
						sendbuff2[7] = USENDI.s[1];
						sendbuff2[8] = USENDI.s[2];
						sendbuff2[9] = USENDI.s[3];
					}
					else{
						Disp_StrAt(">9999");//��ʾ����ֵ
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
//					sendbuff2[9] = USENDI.s[3];��
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
								f_sort=TRUE;//��ѡ��־
							}
						
						}
						else
						{
							if(Voltage-SaveData.Setup.Output<=2)
							{
								Voltage=SaveData.Setup.Output;
								f_sort=TRUE;//��ѡ��־
							}
						}
						Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
						Disp_StrAt(DispBuf);//��ʾ����ֵ
						memset(sendbuff,0,20);
						sendflag = 1;
						memcpy(sendbuff,DispBuf,4);
						strcat(sendbuff,"kV;");
						sendbuff2[4] = (u8)(Voltage >> 8);
						sendbuff2[5] = (u8)(Voltage);
						
						LcdAddr.x=9;
						Hex_Format(Test_value.Test_I,2,4,TRUE);//���ݸ�ʽ����DispBuf
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
//							Disp_StrAt(DispBuf);//��ʾ����ֵ
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
//							//Disp_StrAt("-----");//��ʾ����ֵ
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
							Disp_StrAt(DispBuf);//��ʾ����ֵ
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
								//Disp_StrAt("-----");//��ʾ����ֵ
								Disp_StrAt(DispBuf);
								Disp_Str((u8*)"  ");
							}else if(GetSystemMessage()==MSG_OVER){
								memcpy(DispBuf,"BRK ",5);
								//Disp_StrAt("-----");//��ʾ����ֵ
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
						Hex_Format(Voltage,2,3,TRUE);//���ݸ�ʽ����DispBuf
						Disp_StrAt(DispBuf);//��ʾ����ֵ
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
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],5,FALSE);//���ݸ�ʽ����DispBuf
							else
								Hex_Format(Resistance/10,IR_Range_dot[Range+1],4,FALSE);//���ݸ�ʽ����DispBuf
							
						}
						else
							Hex_Format(Resistance,IR_Range_dot[Range],4,TRUE);//���ݸ�ʽ����DispBuf
						if(Resistance!=TEST_VALUE_OVER)
						{
							Disp_StrAt(DispBuf);//��ʾ����ֵ
							strcat(sendbuff1,(char*)DispBuf);
							USENDI.sendI = atof(DispBuf);
							sendbuff3[6] = USENDI.s[0];
							sendbuff3[7] = USENDI.s[1];
							sendbuff3[8] = USENDI.s[2];
							sendbuff3[9] = USENDI.s[3];
						}
						else{
							Disp_StrAt(">9999");//��ʾ����ֵ
//							Disp_StrAt("-----");//��ʾ����ֵ
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
//						strcat(sendbuff,(char*)"M��;");
						
//						strcat(sendbuff1,(char*)DispBuf);��
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
			
			//��ʾʱ��
			LcdAddr.x=10;LcdAddr.y=0;
			Hex_Format(Test_value.Test_Time,1,4,FALSE);//���ݸ�ʽ����DispBuf
			Disp_StrAt(DispBuf);//��ʾ����ֵ
//			sendbuff2[10] = (u8)(Test_value.Test_Time >> 8);
//			sendbuff2[11] = (u8)(Test_value.Test_Time);
			//��ʾ��Ϣ
			if(f_msgdisp==TRUE)//��Ϣ��ʾ��־
			{
//				f_msgdisp=FALSE;//��Ϣ��ʾ��־
//				LcdAddr.x=MSG_ADDR_X;
//				Disp_SysMessage();//��ʾ��Ϣ
			}
		}
		
//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//���ڴ���
//		}

		key=Key_Read();//��ȡ����
		switch(key)
		{
//			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				break;
	
			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
				break;
	
			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
				break;
	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
				break;

			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				break;

			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
//				break;

//			case KEY_START:		//������
//			case L_KEY_START:	//����������
//				break;

			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				SetSystemMessage(MSG_PAUSE);//ϵͳ��Ϣ-��ͣ����
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-��ͣ����
				//break;
			Plc_Start_Off();
			return;
			
			default:
				break;
		}
	}
	run_stemp++;//��һ��
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
//�������ƣ�TestPause_Process
//�������ܣ�������ͣ����
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.25 
//�޸����ڣ�2015.09.06 13:28
//��ע˵������
//==========================================================
void TestPause_Process(void)
{
//	u8 i;
	u8 key;
	u8 item;
	u16 time;//������ʱʱ��
	bool f_disp;//��ʾ��־

	f_disp=FALSE;//��ʾ��־
	item=SaveData.Setup.Group_Item;//��ǰ����

	//����رտ���
	Output_Off();//����ر�
	
	if(GetSystemMessage()!=MSG_PAUSE)
	{
		switch(item)//��Ŀ
		{
			case I_SETUP://��Ե�������
			case W_SETUP://��ѹ����
				SetSystemStatus(SYS_STATUS_TEST_FINISH);//ϵͳ״̬-���Խ���
				break;
			case I_WSETUP://��Ե��ѹ����
			case W_ISETUP://��ѹ��Ե����
				if(run_stemp==1)
				{
					if(GetSystemMessage()==MSG_PASS)
						SetSystemStatus(SYS_STATUS_TEST);
					else
						SetSystemStatus(SYS_STATUS_TEST_FINISH);//ϵͳ״̬-���Խ���
					
				}
				else
					SetSystemStatus(SYS_STATUS_TEST_FINISH);//ϵͳ״̬-���Խ���
				break;
			case ITEM_NONE://�޲�����Ŀ
				break;

			default:
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-��ͣ����
				return;
				
		}	
	}else{
		switch(item)//��Ŀ
		{
			case I_SETUP://��Ե�������
				
			break;
			case W_SETUP://��ѹ����
				
			break;
			case I_WSETUP://��Ե��ѹ����
				
			break;
			case W_ISETUP://��ѹ��Ե����
				if(run_stemp==1)
				{
					if(GetSystemMessage()==MSG_PASS)
						SetSystemStatus(SYS_STATUS_TEST);
					else
						SetSystemStatus(SYS_STATUS_TEST_FINISH);//ϵͳ״̬-���Խ���
					
				}
				else
					SetSystemStatus(SYS_STATUS_TEST_FINISH);//ϵͳ״̬-���Խ���
				break;
			case ITEM_NONE://�޲�����Ŀ
				break;

			default:
				SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-��ͣ����
				return;
				
		}
		if(respond == 1)
		{
			SendRes();
			respond = 0;
		}
	}		
		
 
	//��ʾ������Ϣ
	LcdAddr.x=MSG_ADDR_X; LcdAddr.y=0;
	Disp_SysMessage();//��ʾ��Ϣ

 	//Ѷ�����
//	if(SaveData.System.Beep)
//	{
		Beep_One();//��һ��
//	}

	//�����豣���������

	
	//������ʱ��������һ���������
	if(GetSystemMessage()==MSG_PAUSE)//��ͣ����
	{
		//��ʾ����
		LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//		Disp_Str("������ͣ",0);//��ʾ
		time=TEST_VALUE_OVER;//����ʱ���ʼ��
	}
	else
	{
		TotalStep++;//���Բ������
		if(StepIndex>=(STEP_MAX-1))//���������
		{
			SetSystemStatus(SYS_STATUS_TEST_FINISH);//���Խ���
			return;
		}

	}

	while(GetSystemStatus()==SYS_STATUS_TEST_PAUSE)
	{
		//��ʾ����ʱ�䣬����ʱ
		if(f_disp)//��ʾ��־
		{
			f_disp=FALSE;//��ʾ��־
			LcdAddr.x=TITLE_ADDR_X+6; LcdAddr.y=TITLE_ADDR_Y+2;
			Hex_Format(time,1,4,TRUE);//��ֵ��ʽ����4λ��ֵ
			Disp_Str(DispBuf);//��ʾ����ֵ
			Disp_Char('s');//��ʾs
		}

		if( GetSoftTimerOut(DISP_SOFTTIMER) && (GetSystemMessage()!=MSG_PAUSE) )//����ͣ���ԣ��ȴ���ʱ����
		{
			if(time!=TEST_VALUE_OVER)//��Ч������ʱ��
			{
				f_disp=TRUE;//��ʾ��־
				SetSoftTimer(DISP_SOFTTIMER,TICKS_PER_SEC_SOFTTIMER/10);//������ʱʱ�䣬1000/10=100mS
				time--;
			}
		}

		if(time<1)//������ʱ�����б�
		{
			SetSystemStatus(SYS_STATUS_TEST);//ϵͳ״̬-���Կ�ʼ��������һ������
		}

//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//���ڴ���
//		}
		
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/20);//�ȴ�����(100*10ms/20=50ms)
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
	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
				break;

			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				break;
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				if(GetSystemMessage()!=MSG_PAUSE)//��ͣ����
				{
					if(time==TEST_VALUE_OVER)//��Ч������ʱ��
					{
						SetSystemStatus(SYS_STATUS_IDLE);//ϵͳ״̬-����
					}
					else
					{
						SetSystemMessage(MSG_PAUSE);//ϵͳ��Ϣ-��ͣ����
//						LcdAddr.x=TITLE_ADDR_X;	LcdAddr.y=TITLE_ADDR_Y;
//						Disp_Str("��ͣ",0);//��ʾ����
					}
				}
				else
				{
					SetSystemStatus(SYS_STATUS_IDLE);//ϵͳ״̬-����
				}
			break;
			case KEY_START:		//������
//			case L_KEY_START:	//����������
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_TEST);//���Կ�ʼ
				break;
	
//			case KEY_ENTER:		//ȷ�ϼ�
//			case L_KEY_ENTER:	//����ȷ�ϼ�
//				break;
	
			
			
			default:
				break;
		}
	}

	//�������ʱ����ʾ��
//	LcdAddr.x=TITLE_ADDR_X+6; LcdAddr.y=TITLE_ADDR_Y+2;
//	Disp_Str("      ",0);//��ʾ
}

//==========================================================
//�������ƣ�TestFinish_Process
//�������ܣ����Խ�������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.26
//�޸����ڣ�2015.08.22 16:04
//��ע˵������
//ע�������
//==========================================================
void TestFinish_Process(void)
{
	u8 key;
	bool f_disp;//��ʾ��־

	f_disp=TRUE;//��ʾ��־

	Led_HV_Off();//�رո�ѹ��
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
//	Amp_Output_Off();//��������ر�
	while(GetSystemStatus()==SYS_STATUS_TEST_FINISH)
	{
		if(f_disp==TRUE)//��ʾ��־
		{
			f_disp=FALSE;//��ʾ��־

			//��ʾ���Խ���
//			LcdAddr.x=TITLE_ADDR_X; LcdAddr.y=TITLE_ADDR_Y;
//			Disp_Str("�������",0);//��ʾ

			//��ʾ��ѡ�����Ѷ�����
			LcdAddr.x=TITLE_ADDR_X+14;LcdAddr.y=TITLE_ADDR_Y;
			if(F_Fail)//����ʧ�ܱ�־
			{
//				Disp_Str("��ѡʧ��",1);//��ʾ
				Beep_On();//��������
				Led_Pass_Off();//�غϸ��
				Led_Fail_On();//��������
		//		if(SaveData.Setup.Beep==BEEP_FAIL)
		//			Beep_On();//��������
		//		else
		//			Beep_Off();//�ط�����
				
				//gtickon=10;
				//Beep_One();
			}
			else
			{
				Beep_Two();//������������
//				Disp_Str("��ѡ�ϸ�",1);//��ʾ
				if(GetSystemMessage()==MSG_PASS)
				{
					Led_Fail_Off();//�ر�����
					Led_Pass_On();//���ϸ��
				}
		//		if(SaveData.Setup.Beep==BEEP_PASS)
		//			Beep_On();//��������
		//		else
		//			Beep_Off();//�ط�����
				
			}
			
		}

//		if(ComBuf.rec.end == TRUE)
//		{
//			Uart_Process();//���ڴ���
//		}
		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/50);//�ȴ�����(100*10ms/50=20ms)
		switch(key)
		{
//			case KEY_SET:	//���ü�
//			case L_KEY_SET:	//�������ü�
//				SetSystemStatus(SYS_STATUS_SETUP);//����״̬
//				break;
//	
//			case KEY_UP:	//�ϼ�
//			case L_KEY_UP:	//�����ϼ�
//				break;
//	
//			case KEY_DOWN:		//�¼�
//			case L_KEY_DOWN:	//�����¼�
//				break;
	
			case KEY_LEFT:		//���
//			case L_KEY_LEFT:	//�������
				break;

			case KEY_RIGHT:		//�Ҽ�
//			case L_KEY_RIGHT:	//�����Ҽ�
				break;

			case KEY_START:		//������
//			case L_KEY_START:	//����������
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_START);//��������
				break;
	
			case KEY_ENTER:		//ȷ�ϼ�
			case L_KEY_ENTER:	//����ȷ�ϼ�
				break;
	
			case KEY_RESET:		//��λ��
			case L_KEY_RESET:	//������λ��
				SetSystemStatus(SYS_STATUS_IDLE);//����
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
//�������ƣ�Reset_Process
//�������ܣ�ϵͳ��λ����
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.25 
//�޸����ڣ�2015.01.25 10:29
//��ע˵������
//==========================================================
void Reset_Process(void)
{
	while(SystemStatus==SYS_STATUS_RESET)
	{
		Hardware_Init();//Ӳ����ʼ��
		ReadCalData();//��ȡ��������
		SetSystemStatus(SYS_STATUS_IDLE);//����״̬
	}
}

//==========================================================
//�������ƣ�Error_Process
//�������ܣ�ϵͳ������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.25 
//�޸����ڣ�2015.01.25 10:27
//��ע˵������
//==========================================================
void Error_Process(void)
{
	u8 i;

	while(GetSystemStatus()==SYS_STATUS_ERROR)
	{
		LcdAddr.x=10; LcdAddr.y=2;
//		Disp_Str("-Error-",0);//��ʾ����
//		Lcd_Draw_Line(0,20,LCD_ADDR_X_MAX);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�
		LcdAddr.x=4;LcdAddr.y=50;
//		Disp_Str("System Will Reboot!",0);//��ʾ����
	
		for(i=0;i<10;i++)
		{
			Beep_Two();//������
			delay_ms(3);//��ʱ300ms
		}
		SetSystemStatus(SYS_STATUS_RESET);//ϵͳ��λ
		ResetSys();//�����λ
	}
}

//Э��2����ͨ����������ֹ�����ʧ�ܷ���12�ֽ�����
void SendRes(void)
{
	u8 i;
	sendbuff2[0] = UART_SEND_BEGIN20;
	sendbuff2[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	sendbuff3[0] = UART_SEND_BEGIN20;
	sendbuff3[1] = UART_SEND_BEGIN21/*UART_SEND_BEGIN21*/;
	
	U2.BIT_FLAG.ACWF = SaveData.Setup.Freq;//w_ma:d4
	U2.BIT_FLAG.ARC = SaveData.Setup.Arc;//w_ma:d3d2d1d0,�绡
	sendbuff2[3] = U2.w_ma;
	sendbuff3[3] = U2.w_ma;
	
	if(!F_Fail)
	{
		if(Test_mid.set_item == W_SETUP/* || Test_mid.set_item == I_WSETUP*/)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_PAUSE://��ѹ������ֹ
				{
					sendbuff2[2] = W_STOP;
				}break;
			}
		}else if(Test_mid.set_item == I_SETUP/* || Test_mid.set_item == W_ISETUP*/){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
				{
					sendbuff2[2] = I_STOP;
				}break;
			}		
		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = I_PASS;
					sendbuff3[2] = W_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
					sendbuff3[2] = I_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_HIGH://��ѹ©�����
				{
					sendbuff2[2] = W_F_HI;
				}break;
				case MSG_LOW://��ѹ©���С
				{
					sendbuff2[2] = W_F_LO;
				}break;
				case MSG_PAUSE://��ѹ������ֹ
				{
					sendbuff2[2] = W_STOP;
				}break;
				case MSG_ARC://��ѹ�绡ʧ��
				{
					sendbuff2[2] = W_ARC;
				}break;
				case MSG_OVER://��ѹ���Ա���
				{
					sendbuff2[2] = W_OVER;
				}break;
			}

		}else if(Test_mid.set_item == I_SETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��Ե����ͨ��
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_HIGH://��Ե�������
				{
					sendbuff2[2] = I_HIGH;
				}break;
				case MSG_LOW://��Ե�����С
				{
					sendbuff2[2] = I_LO;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
	U2.BIT_FLAG.ARC = SaveData.Setup.Arc;//w_ma:d3d2d1d0,�绡
	sendbuff2[3] = U2.w_ma;
	sendbuff3[3] = U2.w_ma;
	
	if(!F_Fail)
	{
		if(Test_mid.set_item == W_SETUP/* || Test_mid.set_item == I_WSETUP*/)
		{
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_PAUSE://��ѹ������ֹ
				{
					sendbuff2[2] = W_STOP;
				}break;
			}
		}else if(Test_mid.set_item == I_SETUP/* || Test_mid.set_item == W_ISETUP*/){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
				{
					sendbuff2[2] = I_STOP;
				}break;
			}		
		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = I_PASS;
					sendbuff3[2] = W_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
					sendbuff3[2] = I_PASS;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
				case MSG_PASS://��ѹ����ͨ��
				{
					sendbuff2[2] = W_PASS;
				}break;
				case MSG_HIGH://��ѹ©�����
				{
					sendbuff2[2] = W_F_HI;
				}break;
				case MSG_LOW://��ѹ©���С
				{
					sendbuff2[2] = W_F_LO;
				}break;
				case MSG_PAUSE://��ѹ������ֹ
				{
					sendbuff2[2] = W_STOP;
				}break;
				case MSG_ARC://��ѹ�绡ʧ��
				{
					sendbuff2[2] = W_ARC;
				}break;
				case MSG_OVER://��ѹ���Ա���
				{
					sendbuff2[2] = W_OVER;
				}break;
			}

		}else if(Test_mid.set_item == I_WSETUP){
			switch(GetSystemMessage())
			{
				case MSG_PASS://��Ե����ͨ��
				{
					sendbuff2[2] = I_PASS;
				}break;
				case MSG_HIGH://��Ե�������
				{
					sendbuff2[2] = I_HIGH;
				}break;
				case MSG_LOW://��Ե�����С
				{
					sendbuff2[2] = I_LO;
				}break;
				case MSG_PAUSE://��Ե������ֹ
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
//�������ƣ�Uart_Process
//�������ܣ����ڴ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.02.02 
//�޸����ڣ�2015.02.10 10:15
//��ע˵������
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
	 u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//�շ����ݻ���
#else
	 u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//�շ����ݻ���
#endif
if(FacBuf.rec.end)//ͨѶЭ��ѡ��
{
	SaveData.pselect = FacBuf.rec.buf[2];
//	SaveData.devaddr = FacBuf.rec.buf[3];
	memset(FacBuf.rec.buf,'\0',30);//��ջ���
	FacBuf.rec.end=FALSE;//���ջ���ɶ���־��λ
	FacBuf.rec.ptr=0;//����ָ������
	
	SavePselect();
//	Saveaddr();
}
if(SaveData.pselect == 0)//ͨѶЭ��1
{
	//	if(SaveData.System.Uart)//������Ч
	//	{
			if (ComBuf.rec.end)//�������ݽ���
			{
				memset(str,'\0',(FRAME_LEN_MAX-FRAME_LEN_MIN+1));//��ջ���
				{
					memcpy(str,&ComBuf.rec.buf[PDATASTART],(FRAME_LEN_MAX-FRAME_LEN_MIN)+1);//ComBuf.send.len-FRAME_LEN_MIN);//���ݰ�
					kind=ComBuf.rec.buf[PFRAMEKIND];//������
					sec_king=ComBuf.rec.buf[PDATASTART];
				}
				//׼��������һ֡����
				ComBuf.rec.end=FALSE;//���ջ���ɶ���־��λ
				ComBuf.rec.ptr=0;//����ָ������
	//		}
	//	}

		switch(kind)
		{
			case FRAME_READ_RESULT://��ȡ���
				//���ڷ��Ͳ�������:��ѹ(5)+����(6)+ʱ��(4)+��ѡ(1)=16�ֽ�
				switch (GetSystemMessage())//ϵͳ��Ϣ
				{
					case MSG_IDLE:
						memcpy(strbuff,"----",5);
						break;
					case MSG_PAUSE:
						memcpy(strbuff,"----",5);
						//kind=0x9B;//������ֹ
						break;
					case MSG_PASS:
						//kind=0x91;//����ͨ��
						memcpy(strbuff,"PASS",5);
						break;
					case MSG_HIGH:
						//kind=0x92;//���ޱ���
						memcpy(strbuff,"HIGH",5);
						break;
					case MSG_LOW:
						//kind=0x92;//���ޱ���
						memcpy(strbuff,"LOW ",5);
						break;
					case MSG_OVER:
						memcpy(strbuff,"BRK ",5);
						break;
					case MSG_ARC:
						memcpy(strbuff,"ARC ",5);
						break;
					case MSG_OFL://��������
						memcpy(strbuff,"HIGH",5);
						break;
					default:
						//kind=0x90;//��������
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
						strcat((char*)ComBuf.send.buf,(char*)sendend);//β�����ӻس��ͻ��з�
						for(i=0;i<39;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
						ComBuf.rec.end=FALSE;//���ջ���ɶ���־��λ
	//					USART_SendData(USART1, 0xBB);
	//					while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	//					break;
					}else{
						for(i=0;i<39;i++)
						{
							USART_SendData(USART1, ComBuf.send.buf[i]);
							while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
						}
						ComBuf.rec.end=FALSE;//���ջ���ɶ���־��λ
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
						
						strcat((char*)ComBuf.send.buf,(char*)sendend);//β�����ӻس��ͻ��з�
						
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
			
			case FRAME_START://����
				run_stemp=0;
				SetSystemStatus(SYS_STATUS_START);//ϵͳ״̬-��������
				break;

			case FRAME_RESET://��λ
				if(GetSystemStatus() == SYS_STATUS_TEST){
					SetSystemMessage(MSG_PAUSE);//ϵͳ��Ϣ-��ͣ����
					SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-����
					Plc_Start_Off();
				}else{
					SetSystemStatus(SYS_STATUS_IDLE);//ϵͳ״̬-����
				}
				break;

			case FRAME_WRITE_SN://д���к�
				break;
			
			case FRAME_CLR_BOOT_NUM://�忪������
				break;
			case FRAME_ITEM://���ò�����Ŀ
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
				SaveGroup();//�������
				Store_set_flash();
				Disp_Idle_Menu();//��ʾ�������
				break;
			case FRAME_DATA://����֡
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
				SaveGroup();//�������
				Store_set_flash();
				Disp_Idle_Menu();//��ʾ�������
				break;
			case FRAME_SELECT_GROUP:
				SaveData.Group=sec_king-1;
				SaveGroup();
				SetSystemStatus(SYS_STATUS_IDLE);//����״̬
				ReadSetByGroup();
				Parameter_valuecomp();//�Ƚ����ò���
				Disp_Idle_Menu();//��ʾ�������
				break;		
			default:
				break;
			
		}
//	Disp_Idle_Menu();//��ʾ�������
	}
}else if(SaveData.pselect == 1){//ͨѶЭ��2
	if (ComBuf.rec.end)//�������ݽ���
	{
		memcpy(recbuf,&ComBuf.rec.buf[0],30);
		lenth=recbuf[2];//���ݳ���
		kind=recbuf[3];//������
		ComBuf.rec.end=FALSE;//���ջ���ɶ���־��λ
		ComBuf.rec.ptr=0;//����ָ������
	}
	
	switch(kind)
	{
		case TEST_RST://����/��λ����
		{
			if(lenth == 2)
			{
				if(recbuf[4] == 'T')//��������
				{
					run_stemp=0;
					SetSystemStatus(SYS_STATUS_START);//ϵͳ״̬-��������
					respond = 1;
				}else if(recbuf[4] == 'R'){//��λ����
					if(GetSystemStatus() == SYS_STATUS_TEST){
						SetSystemMessage(MSG_PAUSE);//ϵͳ��Ϣ-��ͣ����
						SetSystemStatus(SYS_STATUS_TEST_PAUSE);//ϵͳ״̬-����
						Plc_Start_Off();
						respond = 1;
					}else{
						SetSystemStatus(SYS_STATUS_IDLE);//ϵͳ״̬-����
					}
				}else if(recbuf[4] == 'S'){//����������
					SendRes();
				}
			}else if(lenth == 3){
				if(recbuf[4] == 't')//ѡ����𲢲�������
				{
					run_stemp=0;
					SaveData.Group=recbuf[5];
					SaveGroup();
					SetSystemStatus(SYS_STATUS_IDLE);//����״̬
					ReadSetByGroup();
					Parameter_valuecomp();//�Ƚ����ò���					
					SetSystemStatus(SYS_STATUS_START);//ϵͳ״̬-��������
				}
			}
		}break;
		case GROUPSET://�������
		{
			SaveData.Group=recbuf[4];
			SaveGroup();
			SetSystemStatus(SYS_STATUS_IDLE);//����״̬
			ReadSetByGroup();
			Parameter_valuecomp();//�Ƚ����ò���
			Disp_Idle_Menu();//��ʾ�������
		}break;
		case BASICSET:	//����������
		{
			U2.w_ma = recbuf[4];
			SaveData.Setup.Group_Item = U2.BIT_FLAG.item;//������Ŀ
			SaveData.Setup.Item = U2.BIT_FLAG.ACDC;//��ֱ��
			SaveData.Setup.Freq = U2.BIT_FLAG.ACWF;//Ƶ��
			SaveData.Setup.Arc = U2.BIT_FLAG.ARC;//�绡
			
			SaveData.Setup.I_Volt = recbuf[5];//��Ե���������ѹ
			SaveData.Setup.Output = (u16)(recbuf[6]<<8) + recbuf[7];//��ѹ���������ѹ
			SaveData.Setup.High=(u16)(recbuf[8]<<8) + recbuf[9];//��ѹ����©������
			SaveData.Setup.Low=(u16)(recbuf[10]<<8) + recbuf[11];//��ѹ����©������
			SaveData.Setup.RampDelay=(u16)(recbuf[12]<<8) + recbuf[13];//��ѹ����ʱ��
			SaveData.Setup.TestTime=(u16)(recbuf[14]<<8) + recbuf[15];//��ѹ����ʱ��
			SaveData.Setup.I_High=(u16)(recbuf[16]<<8) + recbuf[17];//��Ե����
			SaveData.Setup.I_Low=(u16)(recbuf[18]<<8) + recbuf[19];//��Ե����
			SaveData.Setup.I_Delay=(u16)(recbuf[20]<<8) + recbuf[21];//��ʱ�ж�
			
			SaveGroup();//�������
			Store_set_flash();
			Disp_Idle_Menu();//��ʾ�������
		}break;
	}
}
#endif
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
void Read_Ad(void)
{
	vu8 i;
	vu32 vol;
	vu32 cur;

	vol=0;
	cur=0;
	for(i=0;i<16;i++)
	{
		vol+=Read_Ad_Ch0();//��ȡͨ��0��A/Dֵ
		cur+=Read_Ad_Ch1();//��ȡͨ��1��A/Dֵ
	}
	Voltage=(u16)(vol>>4);//�ۼ�ƽ��
	Current=(u16)(cur>>4);//�ۼ�ƽ��
}

//==========================================================
//�������ƣ�Ad_Filter
//�������ܣ�A/Dֵ�˲�
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.08 
//�޸����ڣ�2015.08.26 10:35
//��ע˵����Voltage��Current��ADֵ�˲�����
//==========================================================
void Ad_Filter(void)
{
	vu8 i;
	vu32 sum;

	static vu16 LastVoltage;//�ϴ�ֵ
	static vu16 LastCurrent;//�ϴ�ֵ

	if(AdCount<AD_BUF_LENGTH)//��������б�
		AdCount++;//ADֵ����

	//���Ƹ��»��壬��һ����һ��
	for(i=(AD_BUF_LENGTH-1);i>0;i--)
	{
		Vbuf[i]=Vbuf[i-1];
	}
	Vbuf[0]=Voltage;//��������ֵ

	//ȡƽ��ֵ
	sum=0;
	i=AdCount;
	while(i--)
	{
		sum+=Vbuf[i];//�ۼ�
	}
	sum/=AdCount;//ƽ��
	Voltage=(u16)sum;
	
	//������Χ��ȡ�ϴ�ֵ��Ϊ����ֵ
//	if(abs(Voltage-LastVoltage)<2)//������Χ�б�
//		Voltage=LastVoltage;
//	else
//		LastVoltage=Voltage;

	//���Ƹ��»��壬��һ����һ��
	for(i=(AD_BUF_LENGTH-1);i>0;i--)
	{
		Ibuf[i]=Ibuf[i-1];
	}
	Ibuf[0]=Current;//��������ֵ

	//ȡƽ��ֵ
	sum=0;
	i=AdCount;
	while(i--)
	{
		sum+=Ibuf[i];//�ۼ�
	}
	sum/=AdCount;//ƽ��
	Current=(u16)sum;
	
	//������Χ��ȡ�ϴ�ֵ��Ϊ����ֵ
//	if(abs(Current-LastCurrent)<2)//������Χ�б�
//		Current=LastCurrent;
//	else
//		LastCurrent=Current;
}

//==========================================================
//�������ƣ�Get_Result
//�������ܣ��������ֵ���
//��ڲ�������
//���ڲ�������
//�������ڣ�2014.11.08 
//�޸����ڣ�2015.08.27 14:43
//��ע˵��������Voltage
//==========================================================
void Get_Result(void)
{
	u32 dat;

	//���ADֵ�б�
	if(Voltage>AD_MAX)//���ADֵ�б�
		Voltage=AD_MAX;


	//���ADֵ�б�
	if(Current>AD_MAX)//���ADֵ�б�
		Current=AD_MAX;
	switch(Test_mid.set_item)
	{
		case I_SETUP:
			//dat=Voltage*10;//�Ŵ�10��
			
			dat=jisuandianzu(Cal[7+Range].Num,Cal[7+Range].NumAd,Current,Voltage,Cal[2].NumAd);
			Resistance=/*(u16)*/dat;
		
			if(Resistance > 900)
			{
				dat=jisuandianzu(Cal[7+3].Num,Cal[7+3].NumAd,Current,Voltage,Cal[2].NumAd);
			}
			Resistance=/*(u16)*/dat;
			
			dat=Voltage*10;//�Ŵ�10��
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//��������
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			//У׼����
			break;
		case W_SETUP:
			dat=Current*10;//�Ŵ�10��	
			if(SaveData.Setup.Item==0)
			{
				dat*=Cal[3+Range].Num;
				dat/=Cal[Range+3].NumAd;
				if(dat%10>4)dat+=10;
					dat/=10;
				Test_value.Test_I=dat;
				
				
				dat=Voltage*10;//�Ŵ�10��
				dat*=Cal[0].Num;
				dat/=Cal[0].NumAd;

				//��������
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
				
				dat=Voltage*10;//�Ŵ�10��
				dat*=Cal[1].Num;
				dat/=Cal[1].NumAd;

				//��������
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			}

			//��������
			
			break;
		case W_ISETUP:
			if(run_stemp==0)
			{
				dat=Current*10;//�Ŵ�10��	
				if(SaveData.Setup.Item==0)
				{
					dat*=Cal[3+Range].Num;
					dat/=Cal[Range+3].NumAd;
					//��������
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//�Ŵ�10��
					
					dat*=Cal[0].Num;
					dat/=Cal[0].NumAd;

					//��������
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
					
				}
				else
				{
					dat*=Cal[5+Range].Num;
					dat/=Cal[Range+5].NumAd;
					//��������
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//�Ŵ�10��
					dat*=Cal[1].Num;
					dat/=Cal[1].NumAd;

					//��������
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
				dat=Voltage*10;//�Ŵ�10��
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//��������
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
				dat=Voltage*10;//�Ŵ�10��
				dat*=Cal[2].Num;
				dat/=Cal[2].NumAd;

				//��������
				if(dat%10>4)dat+=10;
				dat/=10;
				Voltage=(u16)dat/10;
			
			
			}else
			{
				dat=Current*10;//�Ŵ�10��	
				if(SaveData.Setup.Item==0)
				{
					dat*=Cal[3+Range].Num;
					dat/=Cal[Range+3].NumAd;
					//��������
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//�Ŵ�10��
					
					dat*=Cal[0].Num;
					dat/=Cal[0].NumAd;

					//��������
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
					
				}
				else
				{
					dat*=Cal[5+Range].Num;
					dat/=Cal[Range+5].NumAd;
					//��������
					if(dat%10>4)dat+=10;
						dat/=10;
					Test_value.Test_I=dat;
					dat=Voltage*10;//�Ŵ�10��
					dat*=Cal[1].Num;
					dat/=Cal[1].NumAd;

					//��������
					if(dat%10>4)dat+=10;
					dat/=10;
					Voltage=(u16)dat/10;
			
				
				}
			
			}
			break;
		default:
			break;
	
	
	}
	
	
		//У׼����
	
	
	//Resistance= jisuandianzu(u16 bzdzn,u16 bzdzadn,u16 I_ad,u16 dianya);
}



//==========================================================
//END
//==========================================================
