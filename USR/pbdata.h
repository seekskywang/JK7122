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

#define AD_BUF_LENGTH		(8)//A/Dֵ����������
#define HW_UART_SUPPORT 1
extern vu16 Vbuf[AD_BUF_LENGTH];//��ѹA/Dֵ����
extern vu16 Ibuf[AD_BUF_LENGTH];//����A/Dֵ����
//�������

extern u8 dt;
extern vu8 SystemStatus;//ϵͳ״̬
extern vu8 SystemMessage;//ϵͳ��Ϣ
extern vu8 MenuIndex;//�����˵���
extern vu8 Range;//��ǰ����
extern vu8 ffit_data1;
extern vu16	count_ffit;
extern u8 fft_flag;

extern vu8 StepIndex;//������
extern vu8 TotalStep;//�����ܲ���
extern vu16 Current;//����
extern vu16 TestTime;//ʱ��
extern vu8 AdCount;//A/Dֵ��������
extern vu16 RampStepYs;//������������
extern vu16 RampStepFd;//������������
extern vu8 RampStepTime;//��������ʱ��
extern  vu16 TestOut;//�������ֵ
extern  vu16 FullOut;//�������ֵ
extern  u8 run_stemp;//���в���   ���ӵ�ʱ����
//���庯��

void RCC_HSE_Configuration(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);
void SetSoftTimer(u8 id, u8 ticks);
bool GetSoftTimerOut(u8 id);

void Lcd2002_Gpio_Init(void);

extern const vu16 DefaultCalDaOut[];
//16bit���ݵ�λ��������
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
#define HW_FD_TEST			((u8)(SetD7))//����
#define HW_FD_NOTEST		((u8)(~SetD7))//�ŵ�

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

#define HW_GYB_0R			((u8)(SetD4|SetD5))//����
#define HW_GYB_10KR			((u8)(ClrD4&ClrD5))//����
#define HW_GYB_100KR		((u8)(SetD4))//����

//==========================================================

#define FIT_INUM    12  //�˲�����
#define STEP_MAX			(4)//�����(0-3)

#define GROUP_MAX			(8)//������

#define IDLE_MENU_MAX  		(4)//�������˵�
#define IDLE_MENU_PAGE 		(4)//ÿҳ�����˵�

#define PARAMETER_MENU_MAX	(13)//�������˵�
#define PARAMETER_MENU_PAGE	(4)//ÿҳ�����˵�

#define PARAMETER_ACW_MAX	(8)//ACW������(0-7)
#define PARAMETER_DCW_MAX	(8)//DCW������(0-7)
#define PARAMETER_IR_MAX	(6)//IR������(0-5)
#define PARAMETER_GND_MAX	(7)//ACW������(0-6)

#define SYSTEM_MENU_MAX		(10)//���ϵͳ�˵�(0-5)
#define SYSTEM_MENU_PAGE	(4)//ÿҳϵͳ�˵�

#define CONFIG_MENU_MAX		(3)//���������(0-2)

#define PW_LENGTH 			(4)//�������λ��

#define AD_BUF_LENGTH		(8)//A/Dֵ����������


#define MAXTSOFTTIMER (2)		//��ʱ����Ŀ


//==========================================================
//����汾��10
#define SOFTWARE_VERSION		(0x10)

//==========================================================
//Ĭ�ϳ������(0)
#define DEFAULT_MACHINE_ID 		(0)

//Ĭ�ϳ�������(0)
#define DEFAULT_PASSWORD 		(0)

//Ĭ�Ͽ�������(0)
#define SET_BOOT_DEFAULT		(0)





//ADֵ�˲����ã����������ȶ���
#define AD_FILTER_SUPPORT		(_DEBUG_CONFIG_TRUE)

//==========================================================
#define SETUP_MENU_MAX  	(2)//������ò˵�

//#define PARAMETER_MENU_MAX	(5)//�������˵�

//#define SYSTEM_MENU_MAX		(2)//���ϵͳ�˵�

#define CONFIG_MENU_MAX		(3)//���������(0-2)

#define PW_LENGTH 			(4)//�������λ��

#define RANGE_MAX 			(5-1)//�������

#define AD_BUF_LENGTH		(8)//A/Dֵ����������

//==========================================================
#define OHM 				(0xF4)	//CGROM���Ц��ַ�������Ϊ0xF4

//==========================================================
//��ʾ������X����
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

//��������������
#define RANGR_LIMIT_HIGH (3800)
#define RANGR_LIMIT_LOW  (360)
//==========================================================
//��׼��ѹDA   50V   500V
//==========================================================
#define  CAL_50V		(3000)
#define  CAL_500V		(3000)

//��ʱ������
#define KEYBOARD_SOFTTIMER	(0) //������ʱ��ʱ��
#define DISP_SOFTTIMER 		(1) //��ʾ��ʱ��ʱ��

//==========================================================
//���ⳤ��
#define LIST_TITLE_LEN		(8)
#define TITLE_LEN_MAX		(8)
#define SetSystemStatus(status) (SystemStatus=status)
#define GetSystemStatus() (SystemStatus)
#define GetSystemMessage() (SystemMessage)
#define SetSystemMessage(msg) (SystemMessage=msg)

#define SET_GROUP_MAX GROUP_MAX
//==========================================================
//ϵͳ״̬
enum SysStatusEnum
{	
	SYS_STATUS_ERROR ,			//�쳣
	SYS_STATUS_RESET ,			//��λ
	SYS_STATUS_POWER ,			//����
	SYS_STATUS_IDLE ,			//����
	SYS_STATUS_SETUP ,			//����
	SYS_STATUS_START ,			//����
	SYS_STATUS_TEST ,			//����
	SYS_STATUS_TEST_PAUSE ,		//��ͣ
	SYS_STATUS_TEST_FINISH ,	//����
	SYS_STATUS_DEBUG ,			//����
};
enum Setup_Group_Item
{
	I_SETUP=1,
	W_SETUP=0,
	I_WSETUP=3,
	W_ISETUP=2,

};
//==========================================================
//ϵͳ��Ϣ
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

//��λ������״̬��Ϣ
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
//��ֵ�����Զ���
typedef struct
{
	vu8 *Title;//����
	vu16 Num;//��ֵ
	vu8  Dot;//С����(0-3: xxxx xxx.x xx.xx x.xxx)
	//vu8  Unit;//��λ(0-2: M��  G��  T��)
	vu16 Max;//���ֵ
	vu16 Min;//��Сֵ
	vu16 Len;//��ʾ�����ݳ���
}NumBox_TypeDef;
extern NumBox_TypeDef NumBox;//��ֵ��

//��Ŀֵ																					   
enum ItemEnum
{	
	ITEM_ACW ,
	ITEM_DCW ,
	ITEM_IR ,
	ITEM_GND ,
	ITEM_NONE ,
};
//==========================================================
//������ת��  
typedef struct
{
	u8 Sign;//������
	u32 Digit;//β��
	s8 Exponent;//����

}Float_TypeDef;
extern Float_TypeDef Float;
//==========================================================
//У��ֵ
typedef struct 
{
	vu16 Num;  //���ֵ
	vu16 NumAd;//���A/Dֵ
}Cal_TypeDef;
extern Cal_TypeDef Cal[11];//У׼ֵ
//У����
typedef struct 
{
//	Cal_TypeDef IRVol[2];//��Ե��ѹ��  0  50V  1  500V
//	Cal_TypeDef IRCur[8];// 0 1K�������赵 1  10K  2  100K  3  1000K   4 10M   5  80M 6 64M   7  128M
    Cal_TypeDef AcwVol[1];//������ѹ��ѹֵ-1��
	
	Cal_TypeDef DcwVol[1];//ֻ����ѹ��ѹֵ-1��
	Cal_TypeDef IrVol[1];//��Ե�����ѹֵ-1��
	Cal_TypeDef AcwCur[2];//������ѹ����ֵ-2��
	
	Cal_TypeDef DcwCur[2];//ֱ����ѹ����ֵ-2��
	
	Cal_TypeDef IrCur[4];//��Ե�������ֵ-4��
//	Cal_TypeDef GndVol[1];//�ӵص����ѹֵ-1��
//	Cal_TypeDef GndCur[1];//�ӵص������ֵ-1��
	
}Calibrate_TypeDef;
extern Calibrate_TypeDef Calibrate;
typedef struct
{
	vu16 set_item;//������Ŀ
	vu16 set_time;//���õĲ���ʱ��
	vu16 set_ramp;//���õĻ�������ʱʱ��
	vu16 set_high;//���õ�����
	vu16 set_low;//���õ�����

}Test_mid_Typedef;
extern Test_mid_Typedef Test_mid;
//==========================================================
//������(3��)
typedef struct 
{
	vu16 BootNum;//��������(0-9999��Ĭ��0)
	vu16 ProductId;//�������(0-9999��Ĭ��0)
	vu16 Password;//��������(0-9999��Ĭ��0)
}Factory_TypeDef;
//==========================================================
//ϵͳ��(2��)
typedef struct 
{ 
	vu16 value;	//��ֵ
	vu8 dot;	//С���� 0 1 2 3    xxxx   xxx.x  xx.xx x.xxx
	vu8 unit;	//��λ 0 1 2 3   M��    G��   T��  
	

}SystemRes_TypeDef;
//==========================================================
//ϵͳ��(4��)
//typedef struct 
//{
//	vu16 Vol_Out;	//�����ѹ(10-1000 V)
//	vu16 Set_Time;	//����ʱ��(0-999.9s)
//	vu16 Res_Hi;	//����(xxxx M��)
//	vu16 Res_Lo;	//����(xxxx M��)

//}System_TypeDef;
typedef struct 
{
	vu32 Test_v;	//���Ե�ѹ(10-1000 V)
	vu8 dot;	//С����λ

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
	vu16 Test_Res;	//���Ե�ѹ(10-1000 V)
	vu8 dot;	//С����λ
	vu8 unit;

}Test_RESTypeDef;
//==========================================================
//ϵͳ��(2��)
typedef struct 
{
	Test_VTypeDef Test_v;	//���Ե�ѹ(10-1000 V)
	vu16 Test_Time;	//����ʱ��(0-999.9s)
	Test_RESTypeDef Test_Res;	//���Ե���(xxxx M��)
	vu16 Test_I;

}Test_TypeDef;
extern Test_TypeDef Test_value;
//==========================================================
//
//==========================================================
//������(3��)
typedef struct 
{
	vu16 Password;//��������(0-9999��Ĭ��0)
	vu16 BootNum;//��������(0-9999��Ĭ��0)
	vu16 ProductId;//�������(0-9999��Ĭ��0)
}Config_TypeDef;
//==========================================================
//������(5��)
typedef struct 
{
	vu8 Range;//����ģʽ(0-7��Ĭ��0�Զ�)
	vu8 Beep;//Ѷ��ģʽ(0-2��Ĭ�Ͽ�1-PassOn)
	vu8 ClrOn;//���㿪��(0-1��Ĭ�Ϲ�0)
	
	vu8 ExTrig;//�ⲿ��������(0-1��Ĭ�Ϲ�0)
	vu8 UartOn;//���ڿ���(0-1��Ĭ�Ϲ�0)
//	vu8 FastOn;//���ٲ���(0-1��Ĭ�Ϲ�0)
}Parameter_TypeDef;

//��ֵ�����Զ���
//ϵͳ��(6��)
typedef struct 
{
	vu8 Uart;//���ڿ���(0-1��Ĭ�Ϲ�0)
	vu8 Freq60;//����Ƶ��(0-1��Ĭ��0-50Hz)
	vu8 Connect;//���ӿ���(0-1��Ĭ�Ͽ�1)
	vu8 ConnectTime;//����ʱ��(xxx.x S)

	vu8 Beep;//Ѷ�쿪��(0-1��Ĭ�Ͽ�1)
	vu8 FailPause;//ʧ����ͣ����(0-1��Ĭ�Ϲ�0)
//	vu8 BarScan;//����ɨ�迪��(0-1��Ĭ�Ϲ�0)

}System_TypeDef;
//ͨ�ò�����(8��)
typedef struct 
{
	vu16 Group_Item;//ѡ�������Ŀ��������
	vu16 Item;//��Ŀ ѡ��AD/DC
	vu16 Output;//��ѹ���
	vu16 High;//����
	vu16 Low;//����
	vu16 RampDelay;//����ʱ��/�б���ʱ(xxx.x S)
	vu16 TestTime;//����ʱ��(xxx.x S)
	vu16 Freq;//Ƶ��ѡ��
	//vu16 Connect=1;
	//vu16 Zero;//��ֵ
	vu16 Arc;//�绡�ȼ�(0-9��Ĭ��0-�ر�)
	vu16 I_Volt;
	vu16 I_High;
	vu16 I_Low;
	vu16 I_Delay;

}Setup_TypeDef;
//==========================================================
//������Ϣ
typedef struct 
{
    u8 Group;//���
    Setup_TypeDef Setup; //�������������
    //System_TypeDef System;//ϵͳ��
    //Factory_TypeDef Factory;//������
	//Parameter_TypeDef Parameter;//������
	//Config_TypeDef Config;//������
	Calibrate_TypeDef Calibrate;//У׼��
	//vu16 Crc16;//У����
	u8 pselect;
	u8 devaddr;
	
}Save_TypeDef;
extern bool F_Fail;//����ʧ�ܱ�־
extern bool F_100ms;//100ms��ʱ��־
extern bool F_Password;//������Ч��־
extern Save_TypeDef SaveData;//����ֵ
extern vu32 Voltage;//��ѹ
extern vu32 Test_Time;//����
extern vu32 Resistance;//����
extern u8 SoftTimer[MAXTSOFTTIMER];
extern u8 ra_flag;
extern float i_buff[FIT_INUM];		   //�˲�ֵ
#endif
