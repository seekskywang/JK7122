
#ifndef _flash_eer_H
#define _flash_eer_H

#define STORESETADDR   			0x08070000

void ReadCalData(void);
void Store_set_flash(void);
void ReadGroup(void);
void SaveGroup(void);
void ReadSetByGroup(void);
void StoreCalDate(void);
void SavePselect(void);
void ReadPselect(void);
#endif 
