#include "pbdata.h"
/******根据写周期时序，向输入移位寄存器写入指令函数******/
void AD7705_write_Reg(u8 data_byte)
{
	u8 i;
	_7706_CSL;
	delay_us(50);
	_SPI_SCLKH;
	delay_us(50);
	for(i=0;i<8;i++)
		{
			_SPI_SCLKL;
			delay_us(50);
			if(data_byte&0x80)
				_SPI_DINH;
			else 
				_SPI_DINL;
			delay_us(50);
			_SPI_SCLKH;
			
			data_byte<<=1;
			delay_us(50);
			
		}
	_SPI_DINH;	
	delay_us(50);
	_7706_CSH;		
}

/******根据读周期时序,读输出移位寄存器中数据函数******/
u8 AD7705_read_Reg()
{
	u8 i;
	u8 data;
	u8 DATA_OUT;
	//while(DRDY);//等待完成数据的更新  增加读端口 查询
	//while((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)==GPIO_Pin_3));
	//_7706_CSH;
	//delay_us(20);
	//_SPI_SCLKH;
	//delay_us(20);
	_7706_CSL;
	delay_us(20);
	_SPI_SCLKH;
	delay_us(20);
	//P3=0xff;//读数据之前，对P3口进行写1操作
	/*读数据*/
	for(i=0;i<8;i++)
		{
			DATA_OUT<<=1;
			_SPI_SCLKL;
			delay_us(20);
			if(_SPI_DOUT==Bit_SET)
				data=1;
			else
				data=0;
			DATA_OUT=DATA_OUT|data;
			delay_us(20);
			_SPI_SCLKH;
			delay_us(20);
		}
	_7706_CSH;
	
	//DRDY=1;
		//GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	return (DATA_OUT);
}

/******读出结果函数******/
u16 AD7705_read_result(u8 data)
{
	u8 Data_MSB,Data_LSB;
//	u8 i=0;
	u16 AD_result;
	AD7705_write_Reg(0x38+data);//通信寄存器中，设置为读数据寄存器
	delay_us(100);
//	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
//	{
////		i++;
////		delay_ms(1);
////		if(i>25)
////			break;
//	}
	//delay_ms(25);
	/*数据寄存器为16位的只读寄存器，其包含了来自AD7705的最新转换结果*/
	//delay_ms(1);
	Data_MSB=AD7705_read_Reg();//读出高8位数据
	//delay_ms(1);
	Data_LSB=AD7705_read_Reg();//读出低8位数据
	AD_result=(u16)Data_MSB;
	AD_result<<=8;
	AD_result=AD_result | (u16)Data_LSB;//位转换为数
	/*转换为电压*/
	return AD_result;
	//T_voltage=AD_result*50000/65536;
}
/******配置AD7705函数******/
void AD7705_init(u8 data)//根据具体情况，初始化AD7705  15385742739
{
	u32 i;
//	_SPI_SCLKL;
	_SPI_DINH;
	for(i=0;i<36;i++)
	{
	
		
		_SPI_SCLKL;
		delay_us(50);
		
		_SPI_SCLKH;
		delay_us(50);
	
	}
	delay_us(1000);
	delay_ms(5);
	delay_us(1000);
	AD7705_write_Reg(0x21);//写入通信寄存器;设置为写时钟寄存器
	delay_us(10);
	
	/*时钟寄存器设置*/
	AD7705_write_Reg(0x06-2*data);//MCLKIN引脚处的时钟频率在被AD7705使用前，进行2分频;20HZ输出更新率，即每50ms输出一个新字
	delay_us(10);
//	/*设置寄存器设置*/
	AD7705_write_Reg(0x10+data);//写入通信寄存器，设置为写设置寄存器
	delay_us(10);
//	/*设置寄存器设置*/
	AD7705_write_Reg(0x44);//自校准、增益为1、单极性模拟输入、片内缓冲器，FSYNC清0
//	delay_us(100);
//	while((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)==Bit_SET))
//	{
//	}
//	AD7705_write_Reg(0x11);//写入通信寄存器，设置为写设置寄存器
//	/*设置寄存器设置*/
//	AD7705_write_Reg(0x44);//自校准、增益为1、单极性模拟输入、片内缓冲器，FSYNC清0

//	for(i=0;i<40;i++)
//	{
//	
//		_SPI_DINH;
//		delay_us(1);
//		
//		_SPI_SCLKH;
//		delay_us(1);
//	
//	}
delay_us(100);
}
//读通道值  0  通道0  1  通道1
u16 Read_Channel(u8 data )
{
	u16 ad_data;
	u32 i;
	ad_data=AD7705_read_result(data);
	return ad_data;

}

