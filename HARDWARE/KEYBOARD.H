#ifndef _KEYBOARD_H
#define _KEYBOARD_H
//==========================================================
//调试配置
#define _HW_CONFIG_FALSE	(0)
#define _HW_CONFIG_TRUE		(1)

#define TICKS_PER_SEC 100	//系统时钟每秒节拍数，100x10mS(T0)=1S
#define TICKS_PER_SEC_SOFTTIMER 100	//软定时器时钟每秒节拍数，100x10mS=1S
//Lcd是否支持持续按键
#define HW_KEYBOARD_CONTINUE_SUPPORT	(_HW_CONFIG_TRUE)

//==========================================================
//按键常数定义
#define LONGKEYCOUNT 	(TICKS_PER_SEC)	//长按键节拍数(1s)
//#define SHORTKEYCOUNT 	(TICKS_PER_SEC/20)	//短按键节拍数(50ms)
#define SHORTKEYCOUNT 	(TICKS_PER_SEC/30)	//短按键节拍数(33ms)
#define CONTINUEKEYCOUNT (TICKS_PER_SEC/7)	//持续按键节拍数(100ms)
//键值定义
#define HW_KEY_SET			((u16)(ClrD10))
#define HW_KEY_UP			((u16)(ClrD11))
#define HW_KEY_DOWN			((u16)(ClrD12))
#define HW_KEY_LEFT			((u16)(ClrD4))
#define HW_KEY_RIGHT		((u16)(ClrD5))
#define HW_KEY_ENTER		((u16)(ClrD13))
#define HW_KEY_RESET		((u16)(ClrD15))//pc4
#define HW_KEY_START		((u16)(ClrD14))

//按键编码
#define LONG_PRESS		((u8)0x80)
#define KEY_NONE		((u8)0x00)
#define KEY_SET			((u8)('a'))
#define KEY_UP			((u8)('b'))
#define KEY_DOWN		((u8)('c'))
#define KEY_LEFT		((u8)('d'))
#define KEY_RIGHT		((u8)('e'))
#define KEY_ENTER		((u8)('f'))
#define KEY_RESET		((u8)('g'))
#define KEY_START		((u8)('h'))

#define L_KEY_SET		(LONG_PRESS | KEY_SET)		//设置
#define L_KEY_UP		(LONG_PRESS | KEY_UP)		//上
#define L_KEY_DOWN		(LONG_PRESS | KEY_DOWN)		//下
#define L_KEY_LEFT		(LONG_PRESS | KEY_LEFT)		//左
#define L_KEY_RIGHT		(LONG_PRESS | KEY_RIGHT)	//右
#define L_KEY_ENTER		(LONG_PRESS | KEY_ENTER)	//确认
#define L_KEY_RESET		(LONG_PRESS | KEY_RESET)	//复位
#define L_KEY_START		(LONG_PRESS | KEY_START)	//启动
//==========================================================
//按键结构体声明
typedef struct 
{
	u8 value;	//键值
	bool state;	//键有按下=TRUE
	bool continuance;//持续按键有效=TRUE
}Key_TypeDef;

//==========================================================
//全局变量
extern Key_TypeDef Keyboard;//键码结构体

//==========================================================
//函数声明
extern u8 Key_Identiry(void);//按键识别，返回键值
extern void Keyboard_Init(void);//按键结构体初始化
extern void Key_Scan(void);//按键扫描
extern u8 Key_Read(void);//读取按键，返回键值
extern u8 Key_Read_WithTimeOut(u8 timeticks);//阻塞式读取按键，返回键值
extern void Key_Init(void);

#endif 
