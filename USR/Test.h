//==========================================================
//文件名称：Test.h
//文件描述：测试流程头文件
//文件版本：Ver1.0
//创建日期：2014.10.03
//修改日期：2015.08.28 13:28
//文件作者：
//备注说明：无
//注意事项：无
//==========================================================
#ifndef __Test_H__
#define __Test_H__

//==========================================================
//标题项显示位置定义
#define TITLE_ADDR_X		(8)
#define TITLE_ADDR_Y		(2)

//测试区显示位置定义
#define STEP_ADDR_X			(0)
#define STEP_ADDR_Y			(32)

#define HEIGHT_OF_STEP		(24)
#define WIDTH_OF_DATA		(5)
#define WIDTH_OF_UNIT		(2)
#define WIDTH_OF_VALUE		(WIDTH_OF_DATA+WIDTH_OF_UNIT)

#define DATA_ADDR_X			(0)
#define DATA_ADDR_Y			(STEP_ADDR_Y)

//#define MSG_ADDR_X			(DATA_ADDR_X+WIDTH_OF_VALUE*3+1)

//测试值溢出
#define TEST_VALUE_OVER		(0xffff)

//测试值最大值
#define ACW_CURRENT_MAX		(1200)
#define DCW_CURRENT_MAX		(550)
#define IR_RESISTANCE_MAX	(99999)
#define GND_RESISTANCE_MAX	(310)

//最小分选时间--0.2s
#define SORT_TIME_MIN		(2)
extern char sendbuff[20];
//==========================================================
//函数列表
void Power_Process(void);//上电处理
void Reset_Process(void);//复位处理
void Error_Process(void);//出错处理
void Idle_Process(void);//待机处理
void Setup_Process(void);//设置处理
void Start_Process(void);//启动处理
void Test_Process(void);//测试处理
void TestPause_Process(void);//测试暂停处理
void TestFinish_Process(void);//测试结束处理

void Output_Off(void);//输出关闭
void Test_Init(void);//测试初始化
void Uart_Process(void);//串口处理
void Clear_Process(void);//清零处理
void Disp_Current(void);//显示电流值

void Read_Ad(void);//读取A/D值
void Ad_Filter(void);//A/D值滤波
void Get_Result(void);//计算测试值

#endif

//==========================================================
//END
//==========================================================
