#include "pbdata.h"
#include "keyboard.h"
//==========================================================
//全局变量
Key_TypeDef Keyboard;//键码结构体

static u8 LastKeyVal;//上次键值
static u8 LastKeyTicks;//按键节拍
static u8 ContinueKeyTicks;//持续按键节拍



void Keyboard_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);
//	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	Keyboard.value=KEY_NONE;//键值为空
	Keyboard.state=FALSE;	//按键无效
	Keyboard.continuance=FALSE;//持续按键无效
	
	LastKeyVal=KEY_NONE ;//上次键值
	LastKeyTicks=0;//按键节拍
	ContinueKeyTicks=0;//持续按键节拍
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

//==========================================================
//函数名称：Key_Identiry
//函数功能：按键识别
//入口参数：无
//出口参数：U8 键值
//创建日期：2014.09.25 
//修改日期：2014.09.29 14:45
//备注说明：按键输入信号，0有效
//==========================================================
u8 Key_Identiry(void)
{
	
	u8 key;
//	if((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0)&&(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)==0))
//	{
//		key=KEY_RESET;
//	}
//	else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0)
//	{
//		key=KEY_RESET;
//	}
//	else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)==0)
//	{
//		key=KEY_START;
//	}
//	
//	else
	if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)||(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0))
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
		{
			key=KEY_LEFT;
		}else
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
		{
			key=KEY_UP;
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
		{
		
			key=KEY_SET;
//			if()
//				key=KEY_LEFT;
			
		}
		else
		{
		
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
			{
				key=KEY_ENTER;
			}
			else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
			{
			
				key=KEY_DOWN;
			}
			else
			{
			
				key=KEY_NONE;
			}
		
		}
	
	}
	else 
		key=KEY_NONE;

	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	return (key);
}
//==========================================================
//函数名称：Key_Init
//函数功能：按键结构体初始化
//入口参数：无
//出口参数：无
//创建日期：2014.09.29
//修改日期：2014.09.29 10:49
//备注说明：无
//==========================================================
void Key_Init(void)
{
	Keyboard.value=KEY_NONE;//键值为空
	Keyboard.state=FALSE;	//按键无效
	Keyboard.continuance=FALSE;//持续按键无效
	
	LastKeyVal=KEY_NONE;//上次键值
	LastKeyTicks=0;//按键节拍
	ContinueKeyTicks=0;//持续按键节拍
}

//==========================================================
//函数名称：Key_Read
//函数功能：读取按键
//入口参数：无
//出口参数：无
//创建日期：2014.09.29
//修改日期：2014.09.29 10:50
//备注说明：无
//==========================================================
u8 Key_Read(void)
{
	if (Keyboard.state)	//有键按下
	{
		Keyboard.state=FALSE;
		//Beep_One();	//蜂鸣器响一声
		return (Keyboard.value);
	}
	//可直接处理电源等通用按键
	return (KEY_NONE);	
}

//==========================================================
//函数名称：Key_Read_WithTimeOut
//函数功能：阻塞式读取按键
//入口参数：ticks:等待节拍数(50ms周期)
//出口参数：按键值
//创建日期：2014.09.29
//修改日期：2014.09.29 10:56
//备注说明：直到按键响应或限时到
//==========================================================
u8 Key_Read_WithTimeOut(u8 ticks)
{
//	if (ticks)//定时等待按键
//		{
			SetSoftTimer(KEYBOARD_SOFTTIMER,ticks);//设置按键延时周期(即软定时器设置,50ms周期)
				
			while ((!GetSoftTimerOut(KEYBOARD_SOFTTIMER))&&(!Keyboard.state)) //计时未到并且无按键按下
				{
//					RunOnKeyFree();//在按键等待过程中处理其他业务
				}
//		}
//	else//无限等待按键
//		{
//			while (!Keyboard.state) 
//				{
//					RunOnKeyFree();//在按键等待过程中处理其他业务
//				}			
//		}
	return Key_Read();//按键更新
}
//==========================================================
//函数名称：Key_Scan
//函数功能：按键扫描
//入口参数：无
//出口参数：无
//创建日期：2014.09.28 
//修改日期：2014.09.28 11:01
//备注说明：由10mS中断调用
//==========================================================
void Key_Scan(void)
{
	u8 keyval;
	
	keyval = Key_Identiry();//按键识别，返回键值

	//按键长短识别
	if (keyval==KEY_NONE)//无键
	{
		if (LastKeyVal)	//上次有键，短按键判别
		{
			if ( (LastKeyTicks>SHORTKEYCOUNT) && (LastKeyTicks<LONGKEYCOUNT) )
			{
				Keyboard.value=LastKeyVal;	//键值
				Keyboard.state=TRUE;		//有按键
			}
		}
		LastKeyVal=KEY_NONE;
		LastKeyTicks=0;
		Keyboard.continuance=FALSE; //持续按键	
	}
	else	//有键
	{
		if (LastKeyVal==keyval)//上次按键和本次按键相同
		{
			if (LastKeyTicks<LONGKEYCOUNT+1)//长按键节拍数100x10mS
				LastKeyTicks++;
			
			if (LastKeyTicks==LONGKEYCOUNT)//等于长按键节拍数
			{
				ContinueKeyTicks=0;//持续按键节拍
				keyval|=LONG_PRESS;	//长按键
				Keyboard.value=keyval;	//键值
				Keyboard.state=TRUE;	//有按键
//				Keyboard.continuance=FALSE; //持续按键
				Keyboard.continuance=TRUE; //持续按键
			}
			else if (LastKeyTicks>LONGKEYCOUNT)//大于长按键节拍数
			{
				if(HW_KEYBOARD_CONTINUE_SUPPORT)//持续按键有效判别
				{
					keyval|=LONG_PRESS;	//长按键
					Keyboard.value=keyval;//键值
//					Keyboard.state=TRUE;//有按键
					Keyboard.continuance=TRUE; //持续按键
					ContinueKeyTicks++;
					if(ContinueKeyTicks>CONTINUEKEYCOUNT)//持续按键节拍数
					{
						ContinueKeyTicks=0;//持续按键节拍
						if(Keyboard.state==FALSE)//按键已读取
							Keyboard.state=TRUE;//有按键
					}
				}
			}					
		}
		else//上次按键和本次按键不同
		{
			if(LastKeyVal == 0x68 && keyval == 0x67)
			{
				SetSystemStatus(SYS_STATUS_IDLE);//待机
				Beep_Off();
			}
			LastKeyVal=keyval;
			LastKeyTicks=0;
			
		}
	}
}

