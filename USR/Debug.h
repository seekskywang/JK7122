//==========================================================
//文件名称：Debug.h
//功能描述：调试程序头文件
//文件版本：Ver1.0
//创建日期：2015.10.29
//修改日期：2015.10.29 10:49
//文件备注：无
//==========================================================
#ifndef __Debug_H__
#define __Debug_H__

extern const vu16 DefaultCalibrate[][2];
extern const u16 CalibrateLimit[][2];
extern const u8 Debug_Dot[11];
//==========================================================
//函数列表
void Debug_Process(void);//调试处理
void Default_Calibrate(void);//加载默认校准值
void Vol_Calibrate(void);//电压校准处理
void Res_Calibrate(u8 num);//电阻校准处理
void CalTest_Process(u8 num);//校准测试处理

//==========================================================

#endif

//==========================================================
//END
//==========================================================
