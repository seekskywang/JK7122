#include "pbdata.h"



int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{  	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000);
	__enable_irq();
	SetSystemStatus(SYS_STATUS_POWER);//�����ϵ�״̬

	
	while(1)
	{
		
		switch(GetSystemStatus())
		{
			case SYS_STATUS_POWER:
//				Disp_Clr( );//����
				Power_Process();//�����ϵ紦��
				break;

			case SYS_STATUS_IDLE:
				Disp_Clr( );//����
				Idle_Process();//���⴦��
				break;

			case SYS_STATUS_SETUP:
				Disp_Clr( );//����
				Setup_Process();//���ô���
				break;

			case SYS_STATUS_START:
				Disp_Clr( );//����
				F_Password=FALSE;//��������״̬��������֤��Ч
				Start_Process();//��������
				break;

			case SYS_STATUS_TEST:
//				Disp_Clr( );//����
				Test_Process();//���Դ���
				break;

			case SYS_STATUS_TEST_PAUSE:
//				Disp_Clr( );//����
				TestPause_Process();//������ͣ����
				break;

			case SYS_STATUS_TEST_FINISH:
//				Disp_Clr( );//����
				TestFinish_Process();//���Խ�������
				break;

			case SYS_STATUS_DEBUG:
				Disp_Clr( );//����
				Debug_Process();//���Դ���
			
				break;

			case SYS_STATUS_RESET:
				Reset_Process();//�����λ����
				break;

			default:
				Disp_Clr( );//����
				Error_Process();//������
				break;
		}
 
	}	
}









