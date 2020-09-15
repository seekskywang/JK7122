//==========================================================
//文件名称：Lcd2002.c
//功能描述：通用2002字符液晶驱动子程序
//文件版本：Ver1.0
//创建日期：2014.09.28
//修改日期：2014.09.28 16:38
//文件作者：
//文件备注：液晶屏分上下两行,20x2
//	    	第一行地址:00-0FH；第二行地址:40-4FH
//注意事项：显示列溢出时跳下一行；行溢出时回第一行；最多显示40个字符
//==========================================================
//#include <absacc.h>
//#include <intrins.h>

//#include "TypeDefine.h"
//#include "GlobalValue.h"
//#include "Delay.h"
//#include "Hardware.h"
////#include "Beep.h"
////#include "Keyboard.h"
////#include "Interrupt.h"
//#include "Lcd2002.h"
#include "pbdata.h"
void Lcd2002_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_10
	|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	
}
//==========================================================
//全局变量
LcdAddr_TypeDef LcdAddr;//LCD坐标结构体

//==========================================================
//函数名称：Lcd_ReadStatus
//函数功能：读取液晶的状态
//入口参数：无
//出口参数：u8 状态
//创建日期：2014.09.28
//修改日期：2014.09.28 11:40
//备注说明：状态说明
//			D7:BF位，读写允许位，为0才可操作
//			D6-D0：AC值，当前数据指针的地址值
//==========================================================
//u8 Lcd_ReadStatus(void)
//{
//	u8 dat;
//
//	dat=LCD_CMD_RD_BUS;
//	return (dat);
//}

//==========================================================
//函数名称：Lcd_ReadBF
//函数功能：读取液晶的状态位直至BF标志有效
//入口参数：无
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 12:38
//备注说明：读满200次后自动退出
//			D7:BF位，读写允许位，为0才可操作
//==========================================================
void Lcd_ReadBF(void)
{
//	u8 i;
//	u8 dat;
//
//	i=200;
//	while(i>0)
//	{
//		dat=LCD_CMD_RD_BUS;
//		if((dat&((u8)SetD7))==0)	//D7=0,Lcd ready
//			break;
//		i--;
//	}
delay_ms(2);
}

//==========================================================
//函数名称：Lcd_WriteCmd
//函数功能：写一个字节的命令到LCD的状态寄存器中
//入口参数：u8 待写命令
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 12:44
//备注说明：无
//==========================================================
void Lcd_WriteCmd(u8 dat)
{
	Lcd_ReadBF();
	LCD_RS=0; 
	LCD_WR=0; 
	LCD_E=1; 
	
	GPIO_WriteHigh(GPIOE,dat);//写高8位  注意数据的高低位
	LCD_E=0;
}

//==========================================================
//函数名称：Lcd_WriteData
//函数功能：写一个字节的数据到LCD的显示缓冲RAM中
//入口参数：u8 待写数据
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 12:46
//备注说明：无
//==========================================================
void Lcd_WriteData(u8 dat)
{
	//u8 i,dat1,a;
	Lcd_ReadBF();
	LCD_RS=1; 
	//Delay_us(10);
	LCD_WR=0; 
	LCD_E=1;
	
	
	GPIO_WriteHigh(GPIOE,dat);//写高8位  注意数据的高低位
	LCD_E=0;
	Lcd_AddrUpdate();//坐标更新
}

//==========================================================
//函数名称：Lcd_ReadData
//函数功能：从LCD的显示缓冲RAM中读一个字节的数据
//入口参数：无
//出口参数：u8 读取数据
//创建日期：2014.09.27
//修改日期：2014.09.27 11:40
//备注说明：无
//==========================================================
//u8 Lcd_ReadData(void)
//{
//	u8 dat;
//	
//	Lcd_ReadBF();	//等待Lcd准备好
//	dat=LCD_DAT_RD_BUS;
//	return (dat);
//}

//==========================================================
//函数名称：Lcd_SetAddr
//函数功能：设定坐标
//入口参数：无
//出口参数：无
//创建日期：2014.09.28
//修改日期：2015.10.26 08:41
//备注说明：写坐标LcdAddr
//==========================================================
void Lcd_SetAddr()
{
	//列地址判别
	if(LcdAddr.x>LCDADDR_X_LIMIT)	//如果列越界换下一行
	{
		LcdAddr.x=0;	//列地址回第一列
		LcdAddr.y++;	//行地址加一
	}
	//行地址判别
	if(LcdAddr.y>LCDADDR_Y_LIMIT)//如果行越界返回首行
	{
		LcdAddr.y=0;	//行地址回第一行
	}

	if(LcdAddr.y==0)
		Lcd_WriteCmd(LCD_CMD_DYHDZ+LcdAddr.x);//写第一行地址
	else
		Lcd_WriteCmd(LCD_CMD_DEHDZ+LcdAddr.x);//写第二行地址
}

//==========================================================
//函数名称：Lcd_WriteDataAt
//函数功能：在指定地址写一个字节的数据到LCD的显示缓冲RAM中
//入口参数：u8：dat 待写数据 
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 13:19
//备注说明：无
//==========================================================
//void Lcd_WriteDataAt(u8 dat)
//{
//	Lcd_SetAddr(LcdAddr);	//设置地址
//	Lcd_WriteData(dat);//写数据
//}

//==========================================================
//函数名称：Lcd_ReadDataAt
//函数功能：从地址LcdAdr的LCD显示缓冲RAM中读一个字节的数据
//入口参数：无
//出口参数：u8 读取数据
//创建日期：2014.09.28
//修改日期：2014.09.28 13:17
//备注说明：无
//==========================================================
//u8 Lcd_ReadDataAt(void)
//{
//	Lcd_SetAddr();	//设置地址LcdAdr
//	return (Lcd_ReadData());	//读取数据
//}

//==========================================================
//函数名称：Lcd_Clr
//函数功能：液晶屏清屏
//入口参数：无
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 12:57
//备注说明：清屏后地址为0
//==========================================================
void Lcd_Clr( void )
{
	Lcd_WriteCmd(LCD_CMD_XSQP);	//清屏命令
}

//==========================================================
//函数名称：Lcd_Init
//函数功能：液晶屏初始化
//入口参数：无
//出口参数：无
//创建日期：2014.09.28
//修改日期：2014.09.28 12:56
//备注说明：存在首次显示地址不对现象，原因不明
//==========================================================
const u8 LCD_INIT_PARAMETER[5]=
{
	(LCD_CMD_XSQP),	//清屏(含数据地址指针(AC)清零功能)
	(LCD_CMD_GZFS),	//工作方式设置(8bit,5X7点阵)
	(LCD_CMD_DZQL),
	(LCD_CMD_SRFS),	//输入方式设置(AC数据地址指针自动加1,禁止光标移动)
	(LCD_CMD_XSZT),	//显示状态设置(显示开)
	
	
};
//==========================================================
void Lcd_Init(void)
{
	u8 i;
	Lcd2002_Gpio_Init();
//	Lcd_WriteCmd(0x38);
//	delay_ms(10);
//	Lcd_WriteCmd(0x38);
//	delay_ms(10);
//	Lcd_WriteCmd(0x38);
//	delay_ms(10);
	//初始化命令操作
	for(i=0;i<5;i++)
	{
		Lcd_WriteCmd(LCD_INIT_PARAMETER[i]);
		//Delay_1ms(5);	//延时5ms
	}
	
	//更新坐标
	LcdAddr.x=0;LcdAddr.y=0;
	//Disp_PowerOn_Menu();
}

//==========================================================
//函数名称：Lcd_AddrUpdate
//函数功能：坐标值更新
//入口参数：无
//出口参数：无
//创建日期：2014.09.28
//修改日期：2015.10.26 08:45
//备注说明：LcdAddr.x列地址加一，在写操作后调用
//==========================================================
void Lcd_AddrUpdate(void)
{
	bool rt;
	
	rt=FALSE;	//地址修改标志(TRUE有效)

	LcdAddr.x++;//列地址加一
	
	//列地址判别
	if(LcdAddr.x>LCDADDR_X_LIMIT)//如果列越界换下一行
	{
		LcdAddr.x=0;//列地址回第一列
		LcdAddr.y++;//行地址加一
		rt=TRUE;//地址修改标志(TRUE有效)
	}

	//行地址判别
	if(LcdAddr.y>LCDADDR_Y_LIMIT)//如果行越界返回首行
	{
		LcdAddr.y=0;//列地址回第一行
		rt=TRUE;//地址修改标志(TRUE有效)
	}

	if(rt==TRUE)//地址修改标志(TRUE有效)
		Lcd_SetAddr();//写地址LcdAddr到LCD
}

//==========================================================
//END
//==========================================================
