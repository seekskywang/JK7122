#include "pbdata.h"


bool F_Fail;//����ʧ�ܱ�־
bool F_100ms;//100ms��ʱ��־
bool F_Password;//������Ч��־
 vu8 SystemStatus;//ϵͳ״̬
 vu8 SystemMessage;//ϵͳ��Ϣ
vu8 MenuIndex;//�����˵���
vu8 Range;//��ǰ����
vu8 ffit_data1;
vu16 count_ffit;
//NumBox_TypeDef NumBox;//��ֵ��
vu32 Voltage;//��ѹ
vu32 Test_Time;//ʱ��
vu32 Resistance;//����
NumBox_TypeDef NumBox;
Test_TypeDef Test_value;
Float_TypeDef Float;
Save_TypeDef SaveData;//����ֵ
Calibrate_TypeDef Calibrate;
Res_countTypeDef Res_count;
u8 dt=0;
//u8 fft_flag;
u8 SoftTimer[MAXTSOFTTIMER];//��ʱ��
float i_buff[FIT_INUM];		   //�˲�ֵ
vu16 Vbuf[AD_BUF_LENGTH];//��ѹA/Dֵ����
vu16 Ibuf[AD_BUF_LENGTH];//����A/Dֵ����
vu8 StepIndex;//������
vu8 TotalStep;//�����ܲ���
vu16 Current;//����
vu16 TestTime;//ʱ��
vu8 AdCount;//A/Dֵ��������
vu16 RampStepYs;//������������
vu16 RampStepFd;//������������
vu8 RampStepTime;//��������ʱ��
vu16 TestOut;//�������ֵ
vu16 FullOut;//�������ֵ
u8 ra_flag;
u8 run_stemp;
Test_mid_Typedef Test_mid;
u16 rangelomit_low,rangr_limit_high;
Cal_TypeDef Cal[11];//У׼ֵ
vu8 groupflag;

//==========================================================
//Ĭ��У׼���ֵ
const vu16 DefaultCalDaOut[]=
{
	 2430, //Acw-4kV
	 2800, //Dcw-4kV
	  610, //Ir -1kV
	 3000, //Gnd-25A
};

//==========================================================
//������(5��)
//typedef struct 
//{
//	vu8 Range;//����ģʽ(0-4��Ĭ��0�Զ�)
//	vu8 ClrOn;//���㿪��(0-1��Ĭ�Ϲ�0)
//	vu8 Beep;//Ѷ��ģʽ(0-2��Ĭ�Ͽ�1-PassOn)
//	vu8 ExTrig;//�ⲿ��������(0-1��Ĭ�Ϲ�0)
//	vu8 UartOn;//���ڿ���(0-1��Ĭ�Ϲ�0)
////	vu8 FastOn;//���ٲ���(0-1��Ĭ�Ϲ�0)
//}Parameter_TypeDef;
//==========================================================
//������(3��)
//typedef struct 
//{
//	vu16 Password;//��������(0-9999��Ĭ��0)
//	vu16 BootNum;//��������(0-9999��Ĭ��0)
//	vu16 ProductId;//�������(0-9999��Ĭ��0)
//}Config_TypeDef;


//==========================================================
//������Ϣ
//typedef struct 
//{
//	Parameter_TypeDef Parameter;//������
//	System_TypeDef System;//ϵͳ��
//	Config_TypeDef Config;//������
//	Calibrate_TypeDef Calibrate;//У׼��
//	vu16 Crc16;//У����
//}Save_TypeDef;

void RCC_HSE_Configuration(void) //HSE��ΪPLLʱ�ӣ�PLL��ΪSYSCLK 
{ 
   RCC_DeInit(); /*������RCC�Ĵ�������Ϊȱʡֵ */ 
   RCC_HSEConfig(RCC_HSE_ON); 	 /*�����ⲿ���پ���HSE�� HSE�����(ON)*/ 

   if(RCC_WaitForHSEStartUp() == SUCCESS) {  /*�ȴ�HSE����,  SUCCESS��HSE�����ȶ��Ҿ���*/  

   RCC_HCLKConfig(RCC_SYSCLK_Div1);/*����AHBʱ��(HCLK)RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
   RCC_PCLK2Config(RCC_HCLK_Div1); /*���ø���AHBʱ��(PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*���õ���AHBʱ��(PCLK1)RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/      

   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/*����PLLʱ��Դ����Ƶϵ��*/    
   RCC_PLLCmd(ENABLE); 	 /*ʹ��PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/ 
    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*����ϵͳʱ�ӣ�SYSCLK�� */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08��PLL��Ϊϵͳʱ�� */	    
 } 
} 

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);
}

/****************************************************************************
* ��    �ƣ�delay_us(u32 nus)
* ��    �ܣ�΢����ʱ����
* ��ڲ�����u32  nus
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

/****************************************************************************
* ��    �ƣ�delay_ms(u16 nms)
* ��    �ܣ�������ʱ����
* ��ڲ�����u16 nms
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_ms(u16 nms)
{
     //ע�� delay_ms�������뷶Χ��1-1864
	 //���������ʱΪ1.8��

	 u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

//==========================================================
//�������ƣ�SetSoftTimer
//�������ܣ���ʱ������
//��ڲ�������ʱ��id,��ʱ����
//���ڲ�������
//�������ڣ�2014.09.29
//�޸����ڣ�2014.10.21 15:08
//��ע˵������
//==========================================================
void SetSoftTimer(u8 id, u8 ticks)
{
	SoftTimer[id]=ticks;
}
//==========================================================
//�������ƣ�GetSoftTimerOut
//�������ܣ���ʱ�����
//��ڲ�������ʱ��id
//���ڲ�����True(��ʱ��)/False
//�������ڣ�2014.09.29
//�޸����ڣ�2014.09.29 11:18
//��ע˵������
//==========================================================
bool GetSoftTimerOut(u8 id)
{
	return (SoftTimer[id]?FALSE:TRUE);
}
//==========================================================
//�������ƣ�Beep_On
//�������ܣ���������
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.01.12
//�޸����ڣ�2015.09.04 14:34
//��ע˵������
//==========================================================

