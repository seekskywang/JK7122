#include "pbdata.h"

void SaveGroup(void)//�������
{
//	AT24CXX_Write(1,&SaveData.Group,1);
	AT24CXX_Write(0,&SaveData.Group,1);
}
void ReadGroup(void)
{
//	AT24CXX_Read(1,&SaveData.Group,1);
	AT24CXX_Read(0,&SaveData.Group,1);
}

void SavePselect(void)
{
	AT24CXX_Write(1+sizeof(Calibrate_TypeDef)+9*sizeof(Setup_TypeDef),&SaveData.pselect,1);
}

void ReadPselect(void)
{
//	AT24CXX_Read(1,&SaveData.Group,1);
	AT24CXX_Read(1+sizeof(Calibrate_TypeDef)+9*sizeof(Setup_TypeDef),&SaveData.pselect,1);
}


void Saveaddr(void)
{
	AT24CXX_Write(2+sizeof(Calibrate_TypeDef)+9*sizeof(Setup_TypeDef),&SaveData.devaddr,1);
}

void Readaddr(void)
{
//	AT24CXX_Read(1,&SaveData.Group,1);
	AT24CXX_Read(2+sizeof(Calibrate_TypeDef)+9*sizeof(Setup_TypeDef),&SaveData.devaddr,1);
}


void Store_set_flash(void)
{
//	u16 i;
//	u32 addr;
	Setup_TypeDef *ptt;
	//u8 buff[512];
	//u32 *flash_ram;
	//Save_TypeDef  *pt;
	ptt=&SaveData.Setup;
	AT24CXX_Write(1+sizeof(Calibrate_TypeDef)+SaveData.Group*sizeof(Setup_TypeDef),(u8 *)ptt,sizeof(Setup_TypeDef));
//	 //����
//	FLASH_Unlock();
//	//�����־λ
//	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
//					FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//	addr=STORESETADDR;
//	FLASH_ErasePage(STORESETADDR);

//	for(i=0;i<sizeof(SaveData)/4;i++)
//	FLASH_ProgramWord(addr+i*4,*((u32*)ptt+i));//buff[i/4]);//(u32)buff[i/4]);
//	FLASH_Lock();
}
void ReadSetByGroup(void)
{
	Setup_TypeDef *ptt;
	ptt=&SaveData.Setup;
    AT24CXX_Read(1+sizeof(Calibrate_TypeDef)+SaveData.Group*sizeof(Setup_TypeDef),(u8 *)ptt,sizeof(Setup_TypeDef));

}
void ReadCalData(void)
{
//	u16 i;
//	u32 addr;
	//u8 buff[512];
	//Save_TypeDef *pt;
	
	Calibrate_TypeDef *pt;
	//AT24CXX_Read(0,&SaveData.Group,1);
	pt=&SaveData.Calibrate;
	AT24CXX_Read(1,(u8 *)pt,sizeof(Calibrate_TypeDef));
	

}
void StoreCalDate(void)
{
	Calibrate_TypeDef *pt;
	//AT24CXX_Read(0,&SaveData.Group,1);
	pt=&SaveData.Calibrate;
	AT24CXX_Write(1,(u8 *)pt,sizeof(Calibrate_TypeDef));

}
