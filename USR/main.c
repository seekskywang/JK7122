#include "pbdata.h"



int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{  	

	SetSystemStatus(SYS_STATUS_POWER);//开机上电状态

	
	while(1)
	{
		
		switch(GetSystemStatus())
		{
			case SYS_STATUS_POWER:
//				Disp_Clr( );//清屏
				Power_Process();//开机上电处理
				break;

			case SYS_STATUS_IDLE:
				Disp_Clr( );//清屏
				Idle_Process();//待测处理
				break;

			case SYS_STATUS_SETUP:
				Disp_Clr( );//清屏
				Setup_Process();//设置处理
				break;

			case SYS_STATUS_START:
				Disp_Clr( );//清屏
				F_Password=FALSE;//进入启动状态，密码验证无效
				Start_Process();//启动处理
				break;

			case SYS_STATUS_TEST:
//				Disp_Clr( );//清屏
				Test_Process();//测试处理
				break;

			case SYS_STATUS_TEST_PAUSE:
//				Disp_Clr( );//清屏
				TestPause_Process();//测试暂停处理
				break;

			case SYS_STATUS_TEST_FINISH:
//				Disp_Clr( );//清屏
				TestFinish_Process();//测试结束处理
				break;

			case SYS_STATUS_DEBUG:
				Disp_Clr( );//清屏
				Debug_Process();//调试处理
			
				break;

			case SYS_STATUS_RESET:
				Reset_Process();//软件复位处理
				break;

			default:
				Disp_Clr( );//清屏
				Error_Process();//错误处理
				break;
		}
 
	}	
}









