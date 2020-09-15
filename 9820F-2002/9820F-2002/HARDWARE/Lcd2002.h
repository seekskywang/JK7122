//==========================================================
//文件名称：Lcd2002.h
//功能描述：通用2002字符液晶驱动头文件
//文件版本：Ver1.0
//创建日期：2014.09.28
//修改日期：2014.09.28 16:38
//文件作者：
//文件备注：无
//注意事项：无
//==========================================================
#ifndef __Lcd2002_h__
#define __Lcd2002_h__

//==========================================================
//LCD2002地址定义
////9820A
#define LCD_RS PEout(2)  //RS
#define LCD_WR PEout(3)  //RW
#define LCD_E PEout(4)  //E
#define GPIO_WriteHigh(GPIOx,a) GPIOx->BSRR=(((uint8_t)(uint8_t)~(a))<<24)|(((uint32_t)(uint8_t)(a))<<8)
#define GPIO_WriteLow(GPIOx,a) GPIOx->BSRR=(((uint32_t)(uint8_t)~(a))<<16)|((uint32_t)(uint8_t)(a))
////sbit	LCD_DI = P2^7;//液晶数据命令控制
////sbit	LCD_RW = P2^6;//液晶读写控制
////sbit	LCD_EN = P2^5;//液晶EN控制(上升沿，1有效)
//#define LCD_CMD_WR_BUS  XBYTE[0x3FFF]
//#define LCD_CMD_RD_BUS  XBYTE[0x7FFF]
//#define LCD_DAT_WR_BUS  XBYTE[0xBFFF]
//#define LCD_DAT_RD_BUS  XBYTE[0xFFFF]

//9850
//#define LCD_CMD_WR_BUS  XBYTE[0xC0FF]
//#define LCD_CMD_RD_BUS  XBYTE[0xC8FF]
//#define LCD_DAT_WR_BUS  XBYTE[0xE000]
//#define LCD_DAT_RD_BUS  XBYTE[0xE8FF]
#define Bank1_LCD_C        ((u32)0x6C000000)
#define Bank1_LCD_D        ((u32)0x6C000002)

#define LCD_RAM           *(__IO uint8_t *)(Bank1_LCD_D)
#define LCD_REG           *(__IO uint8_t *)(Bank1_LCD_C)

//==========================================================
//LCD操作命令
#define LCD_CMD_XSFW	(u8)(0x30)	//显示复位命令
#define LCD_CMD_DYHDZ	(u8)(0x80)	//第一行显示地址
#define LCD_CMD_DEHDZ	(u8)(0xC0)	//第二行显示地址
#define LCD_CMD_DDDZ	(u8)(0x80)	//DDRAM地址设置(D7=1):[D6-D0为地址,将7位地址写入AC中,随后的操作对显存]
#define LCD_CMD_GGDZ	(u8)(0x40)	//GGRAM地址设置(D6=1):[D5-D0为地址,用户自定义字符的字符地址]
#define LCD_CMD_GZFS	(u8)(0x38)	//工作方式设置(D5=1):[DL=D4=1:8位总线宽度(0为4位);N=D3=2:两行显示(0为一行);F=D2=0:5X7点阵(0为5X11)]
#define LCD_CMD_HMGD	(u8)(0x18)	//光标或画面滚动设置(D4=1):[S/C=D3=1:画面滚动(0为光标滚动);R/L=D2=1:右滚动(0左滚动)]
#define LCD_CMD_XSZT	(u8)(0x0C)	//显示状态设置(D3=1):[D=D2=1:显示开(0为关);C=D1=0:光标不显示(1显示),B=D0=0:闪烁关闭(1启动)]
#define LCD_CMD_SRFS	(u8)(0x06)	//输入方式设置(D2=1):[I/D=D1=1:AC数据地址指针自动加1(0为不加),S=D0=1:允许画面滚动/光标移动(0为禁止)]
#define LCD_CMD_DZQL	(u8)(0x02)	//数据地址指针清零设置(D1=1)
#define LCD_CMD_XSQP	(u8)(0x01)	//显示清屏命令(D0=1)

//==========================================================
//常数定义
#define LCDADDR_X_LIMIT ((u8)(16-1))//列地址限值(20列)
#define LCDADDR_Y_LIMIT ((u8)(2-1))//行地址限值(2行)
#define LCDADDR_MAX 	((u8)(16*2))//最多一次显示的字符个数(40个)

//LCD坐标结构体定义
typedef struct 
{
	u8 x;	//行坐标
	u8 y;	//列坐标
}LcdAddr_TypeDef;

//==========================================================
//全局变量
extern LcdAddr_TypeDef LcdAddr;//LCD地址结构体

//==========================================================
//函数列表
//u8 Lcd_ReadStatus(void);//读LCD状态字
void Lcd_ReadBF(void);//读取液晶的状态位直至BF标志有效(读200次后自动退出)
void Lcd_WriteCmd(u8);//写命令
void Lcd_WriteData(u8);//写数据
//u8 Lcd_ReadData(void);//读当前地址的数据
void Lcd_SetAddr(void);//LCD坐标LcdAdr设置
// void Lcd_WriteDataAt(u8 dat);//地址LcdAdr写数据
//u8 Lcd_ReadDataAt(void);//地址LcdAdr读数据
void Lcd_Clr(void);//全屏清零
void Lcd_Init(void);//液晶初始化
void Lcd_AddrUpdate(void);//LCD坐标LcdAdr更新


#endif
