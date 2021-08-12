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
#include "lpuart.h"
#include "timer3.h"

extern void SysClockInit(void);
extern void GPIO_Init(void);
extern void Wdt_Interface_Init(void);
extern void parameter_init(void);
extern void Uart0_Init(void);
extern void LPTimerInit(void);
extern void SPI_Init(void);
extern void LPuart1_Init( void );
#endif
