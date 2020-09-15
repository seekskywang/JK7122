//==========================================================
//文件名称：Beep.h
//文件描述：蜂鸣器控制头文件
//文件版本：Ver1.0
//创建日期：2014.09.28 
//修改日期：2014.09.28 11:01
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
#ifndef __Beep_h__
#define __Beep_h__

//==========================================================
//蜂鸣器属性结构体
typedef struct
{
	u8 tick_on;		//蜂鸣器开周期
	u8 tick_off;	//蜂鸣器关周期
	u8 tick_work;	//工作周期
}Beep_TypeDef;

//==========================================================
//函数声明
void Beep_Init(void);//初始化蜂鸣器
void Beep_Work(void);//蜂鸣器工作
void Beep_One(void);//蜂鸣器响一声
void Beep_Two(void);//蜂鸣器响两声
void Beep_Long(void);//蜂鸣器长响一声


#endif 
