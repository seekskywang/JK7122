#include "pbdata.h"

u8 _4094_databuff[_4094NUM];

void Out_4094(u8 *buff) //写CD4094子函数;
{
	u8 i;       //定义子函数;
	u8 j;
	_4094_STBL;       //保持然来的状态不变;
	_SPI_SCLKH;
	for(j=0;j<_4094NUM;j++)
	{
		for(i=0;i<8;i++)     //写八位数据进CD4094;
		{
			if(*(buff+j)&0x80)     //判断并发串行数据;
			{
				_SPI_DINH;      //发高电平;
			}
			else
			{
				_SPI_DINL;      //发低电平;
			}
			
			_SPI_SCLKL;       //形成上升延脉冲;
			delay_us(5);
			_SPI_SCLKH;
			*(buff+j)<<=1;      //数据移位,送下一位数据;
			
		}
	}
	_4094_STBH;       //数据送完;更新显示;
	delay_us(5);
	_4094_STBL; 
}
