/*
       /_/_/_/_/   /_/_/_/     /_/_/_/_/
           /_/    /_/    _/   /_/
          /_/    /_/_/_/_    /_/_/_/_/
   /_/   /_/    /_/     _/  /_/
    /_/_/_/    /_/_/_/_/   /_/

    Copyright (c) 2020 Jade Bird Fire Co., Ltd, All right reserved.
*/
#ifndef _init_h
#define _init_h
#include "gpio.h"
#include "stdint.h"
#include "wdt.h"
#include "spi.h"
#include "flash.h"
#include "uart.h"
#include "global_variable.h"
#include "lptim.h"
#include "lpm.h"
#include "timer3.h"
#include "lpuart.h"
#include "Save.h"
extern void SysClockInit(void);
extern void GPIO_Init(void);
extern void Wdt_Interface_Init(void);
extern void parameter_init(void);
extern void Uart0_Init(void);
extern void LPTimerInit(void);
extern void SPI_Init(void);
extern void KEY_Init(void);
extern void Timer3Init(void );
extern void LPuart1_Init( void );
extern void Init_LED(void);
extern void SPI_Send_Data(uint8_t data);
extern void  ParaInit(void);


#endif
