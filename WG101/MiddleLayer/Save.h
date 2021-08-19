/*
       /_/_/_/_/   /_/_/_/     /_/_/_/_/
           /_/    /_/    _/   /_/
          /_/    /_/_/_/_    /_/_/_/_/
   /_/   /_/    /_/     _/  /_/
    /_/_/_/    /_/_/_/_/   /_/

    Copyright (c) 2020 Jade Bird Fire Co., Ltd, All right reserved.
*/

#ifndef _save_h
#define _save_h
/**********************************头文件**************************************/
#include "stdint.h"
#include "flash.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
extern uint32_t flashInformationAddress;
/**********************************函数声明************************************/
void Flash_Write(uint32_t Address, uint8_t *data, uint16_t length) __attribute__((section(".ARM.__at_0x00000100")));
void Flash_Read(uint32_t Address, uint8_t *data, uint16_t length) __attribute__((section(".ARM.__at_0x00000200")));
#endif
