//==========================================================
//�ļ����ƣ�Test.h
//�ļ���������������ͷ�ļ�
//�ļ��汾��Ver1.0
//�������ڣ�2014.10.03
//�޸����ڣ�2015.08.28 13:28
//�ļ����ߣ�
//��ע˵������
//ע�������
//==========================================================
#ifndef __Test_H__
#define __Test_H__

//==========================================================
//��������ʾλ�ö���
#define TITLE_ADDR_X		(8)
#define TITLE_ADDR_Y		(2)

//��������ʾλ�ö���
#define STEP_ADDR_X			(0)
#define STEP_ADDR_Y			(32)

#define HEIGHT_OF_STEP		(24)
#define WIDTH_OF_DATA		(5)
#define WIDTH_OF_UNIT		(2)
#define WIDTH_OF_VALUE		(WIDTH_OF_DATA+WIDTH_OF_UNIT)

#define DATA_ADDR_X			(0)
#define DATA_ADDR_Y			(STEP_ADDR_Y)

//#define MSG_ADDR_X			(DATA_ADDR_X+WIDTH_OF_VALUE*3+1)

//����ֵ���
#define TEST_VALUE_OVER		(0xffff)

//����ֵ���ֵ
#define ACW_CURRENT_MAX		(1200)
#define DCW_CURRENT_MAX		(550)
#define IR_RESISTANCE_MAX	(99999)
#define GND_RESISTANCE_MAX	(310)

//��С��ѡʱ��--0.2s
#define SORT_TIME_MIN		(6)
extern char sendbuff[20];
extern char sendbuff1[20];
extern char sendbuff2[20];
extern char sendbuff3[20];
//==========================================================
//�����б�
void Power_Process(void);//�ϵ紦��
void Reset_Process(void);//��λ����
void Error_Process(void);//������
void Idle_Process(void);//��������
void Setup_Process(void);//���ô���
void Start_Process(void);//��������
void Test_Process(void);//���Դ���
void TestPause_Process(void);//������ͣ����
void TestFinish_Process(void);//���Խ�������

void Output_Off(void);//����ر�
void Test_Init(void);//���Գ�ʼ��
void Uart_Process(void);//���ڴ���
void Clear_Process(void);//���㴦��
void Disp_Current(void);//��ʾ����ֵ

void Read_Ad(void);//��ȡA/Dֵ
void Ad_Filter(void);//A/Dֵ�˲�
void Get_Result(void);//�������ֵ

#endif

//==========================================================
//END
//==========================================================
