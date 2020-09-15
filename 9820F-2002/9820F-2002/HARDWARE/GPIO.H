#ifndef _gpio_H
#define _gpio_H
extern u8 IC19_574buff,IC42_574buff;
void PORT_Gpio_Init(void);
void BeepOn(void);
void BeepOff(void);
void Led_Pass_Off(void);//关合格灯;
void Led_Pass_On(void);//开合格灯
void Led_Test_Off(void);//关合格灯
void Led_Test_On(void);//开合格灯
void Led_Fail_Off(void);//关不合格
void Led_Fail_On(void);//开不合格
void Led_HV_On(void);//开高压灯
void Led_HV_Off(void);//关高压灯

#endif 
