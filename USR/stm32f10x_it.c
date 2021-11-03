/**
  ******************************************************************************
  * @file GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"	 
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "pbdata.h"

extern u8 calitem;
void NMI_Handler(void)
{
}

void USART1_IRQHandler(void)
{
	u8 dat;
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
	   USART_ClearFlag(USART1, USART_FLAG_RXNE);
	   if(SaveData.pselect == 0)//原始协议
	   {
			if (!ComBuf.rec.end)//接收没结束
			{
				SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
				dat=USART_ReceiveData(USART1);
				if (/*dat==(u8)(UART_REC_BEGIN)*/ComBuf.rec.ptr==0)//帧头
				{
					if(dat!=(u8)(UART_REC_BEGIN)) //首字节
					{
						ComBuf.rec.ptr=0;//重新接收 
					}
					else
					{
						ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
					}
				}
				else if (dat==(u8)(UART_REC_END))//帧尾
				{
					ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
					ComBuf.rec.end=TRUE;//接收结束
					ComBuf.rec.len=ComBuf.rec.ptr;//存接收数据长度
					ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
					ComBuf.rec.TimeOut=0;//接收超时清零
				}
				else
				{
					if (ComBuf.rec.ptr>=REC_LEN_MAX)//最大接收帧长度
					{
						ComBuf.rec.ptr=0;//重新接收
					}
					else
					{
						ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
					}
				}
			}
		}else if(SaveData.pselect == 1){//新协议
			if (!ComBuf.rec.end)//接收没结束
			{
				SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
				dat=USART_ReceiveData(USART1);
				if (/*dat==(u8)(UART_REC_BEGIN20) && */ComBuf.rec.ptr == 0)//帧头1
				{
					if(dat!=(u8)(UART_REC_BEGIN20)) //首字节
					{
						ComBuf.rec.ptr=0;//重新接收 
					}
					else
					{
						ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
					}
				}
				else if (/*dat==SaveData.devaddr(u8)(UART_REC_BEGIN21) && */ComBuf.rec.ptr == 1)//帧头2
				{
					if(dat!=UART_REC_BEGIN21) //第二字节
					{
						ComBuf.rec.ptr=0;//重新接收 
					}
					else
					{
						ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
					}
				}else{
					if (ComBuf.rec.ptr>=REC_LEN_MAX)//最大接收帧长度
					{
						ComBuf.rec.ptr=0;//重新接收
					}
					else
					{
						ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
						if(ComBuf.rec.ptr > 2 && (ComBuf.rec.ptr == ComBuf.rec.buf[2]+3))
						{
//							ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
							ComBuf.rec.end=TRUE;//接收结束
							ComBuf.rec.len=ComBuf.rec.ptr;//存接收数据长度
							ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
							ComBuf.rec.TimeOut=0;//接收超时清零
						}
					}
				}
			}
		}
		if(ComBuf.rec.end == TRUE)
		{
			Uart_Process();//串口处理
		}
		//出厂协议设置命令
		if(!FacBuf.rec.end)
		{
			SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
			dat=USART_ReceiveData(USART1);
			if (/*dat==0XFF*/FacBuf.rec.ptr==0)//帧头1
			{
				if(dat!=0XFF) //首字节
				{
					FacBuf.rec.ptr=0;//重新接收 
				}
				else
				{
					FacBuf.rec.buf[FacBuf.rec.ptr++]=dat;
				}
			}
			else if (/*dat==0XEE*/FacBuf.rec.ptr==1)//帧头2
			{
				if(dat!=0XEE) //第二字节
				{
					FacBuf.rec.ptr=0;//重新接收 
				}
				else
				{
					FacBuf.rec.buf[FacBuf.rec.ptr++]=dat;
				}
			}else if (/*dat==0XDD*/FacBuf.rec.ptr==4)//帧尾
			{
				if(dat!=0XDD) //第五字节
				{
					FacBuf.rec.ptr=0;//重新接收 
				}else{
					FacBuf.rec.buf[FacBuf.rec.ptr++]=dat;
					FacBuf.rec.end=TRUE;//接收结束
					FacBuf.rec.len=FacBuf.rec.ptr;//存接收数据长度
					FacBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
					FacBuf.rec.TimeOut=0;//接收超时清零	
				}					
				
			}
			else
			{
				if (FacBuf.rec.ptr>=REC_LEN_MAX)//最大接收帧长度
				{
					FacBuf.rec.ptr=0;//重新接收
				}
				else
				{
					FacBuf.rec.buf[FacBuf.rec.ptr++]=dat;
				}
			}
		}
			
	   }
   if(USART_GetITStatus(USART1,USART_IT_ORE)!=RESET)
   {
	   USART_ClearFlag(USART1, USART_FLAG_ORE);
	   dat=USART_ReceiveData(USART1);
   
   }
}


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}

void TIM3_IRQHandler(void)
{
	static u8 num=0;
	u8 i;
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	//if(disp_time<99999)
	
	
//	else
//		disp_time=0;
	Key_Scan();
	//时基处理
	if(SystemStatus==SYS_STATUS_TEST)
	{
		num++;
		if(num>9)//10mS时基
		{
			num=0;
			F_100ms=TRUE;//100ms定时标志
			Test_value.Test_Time++;
			disp_time++;
			Test_Time++;
			//Voltage++;
		}
	}
	else
	{
		if(num!=0)
			num=0;
	}	
	for (i=0;i<MAXTSOFTTIMER;i++)
	{
		if (SoftTimer[i])
			SoftTimer[i]--;
		
	}
	if(F_Fail==0)
		Beep_Work();
	

}
/****************************************************************************
* 名    称：void EXTI9_5_IRQHandler(void)
* 功    能：EXTI9-5中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/****************************************************************************
* 名    称：void EXTI1_IRQHandler(void)
* 功    能：EXTI2中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI0_IRQHandler(void)
{
	//delay_ms(1);//消抖
	 	 //电弧
	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)==0  && SaveData.Setup.Arc != 0 &&  GetSystemStatus()==SYS_STATUS_TEST)
	{
		SetSystemMessage(MSG_ARC);
	
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 
//外部中断2服务程序
void EXTI1_IRQHandler(void)
{
	delay_ms(1);//消抖
	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)==0 && GetSystemStatus()==SYS_STATUS_TEST)//过流中断
	{
		if(Test_mid.set_item == W_ISETUP && run_stemp == 1)
		{
			SetSystemMessage(MSG_LOW);
		}else if(Test_mid.set_item == I_WSETUP && run_stemp == 0){
			SetSystemMessage(MSG_LOW);
		}else{
			SetSystemMessage(MSG_OVER);
		}
	}
		 
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE2上的中断标志位  
}


/**************************************************************************
* 名    称：void EXTI2_IRQHandler(void)
* 功    能：EXTI2中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI2_IRQHandler(void)//启动按键
{
	delay_ms(5);
	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)==0)
	{
		if((GetSystemStatus()==SYS_STATUS_IDLE)||(GetSystemStatus()==SYS_STATUS_TEST_PAUSE)||(GetSystemStatus()==SYS_STATUS_TEST_FINISH))
		{
			SetSystemStatus(SYS_STATUS_START);//启动测试状态
			run_stemp=0;//从第一步开始
		
		}else if(GetSystemStatus()==SYS_STATUS_IDLE){
//			CalTest_Process(calitem);//校准测试处理
//			Disp_Clr( );//清屏
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

/****************************************************************************
* 名    称：void EXTI3_IRQHandler(void)
* 功    能：EXTI3中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI3_IRQHandler(void)//复位按键
{
	delay_ms(1);
	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0)
	{
		if(GetSystemStatus()==SYS_STATUS_TEST)//增加暂停功能
		{
			SetSystemStatus(SYS_STATUS_TEST_PAUSE);
		
		}
		else
	   SetSystemStatus(SYS_STATUS_IDLE);
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

