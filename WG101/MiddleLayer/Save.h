#ifndef _save_h
#define _save_h
/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "flash.h"
/**********************************�궨������**********************************/
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
extern uint32_t flashInformationAddress;
/**********************************��������************************************/
void Flash_Write(uint32_t Address, uint8_t *data, uint16_t length) __attribute__((section(".ARM.__at_0x00000100")));
void Flash_Read(uint32_t Address, uint8_t *data, uint16_t length) __attribute__((section(".ARM.__at_0x00000200")));
#endif
