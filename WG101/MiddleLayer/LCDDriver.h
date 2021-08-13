
/***************************************************************************************
****************************************************************************************
* FILE		: LCDDriver.h
* Description	: 
*			  
* Copyright (c) 2019 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		XXX	2019/05/08	Initial Version
   
****************************************************************************************
****************************************************************************************/
#ifndef _LCDDRIVER_h
#define _LCDDRIVER_h

#include "includes.h"

#define TABLE_SIZE      26


#define GUI_MAIN         0x01
#define GUI_2ND          0x02
#define GUI_3RD          0x04

#define TOTAL_NUM_2ND    4





#define SET_LED1	Gpio_SetIO(LED1_PORT, LED1_PIN);
#define SET_LED2	Gpio_SetIO(LED2_PORT, LED2_PIN);
#define SET_LED3	Gpio_SetIO(LED3_PORT, LED3_PIN);
#define SET_LED4	Gpio_SetIO(LED4_PORT, LED4_PIN);

#define RESET_LED1	Gpio_ClrIO(LED1_PORT, LED1_PIN);
#define RESET_LED2	Gpio_ClrIO(LED2_PORT, LED2_PIN);
#define RESET_LED3	Gpio_ClrIO(LED3_PORT, LED3_PIN);
#define RESET_LED4	Gpio_ClrIO(LED4_PORT, LED4_PIN);
	
#define SET_SEG1	Gpio_SetIO(SEG1_PORT, SEG1_PIN);
#define SET_SEG2	Gpio_SetIO(SEG2_PORT, SEG2_PIN);
#define SET_SEG3	Gpio_SetIO(SEG3_PORT, SEG3_PIN);
#define SET_SEG4	Gpio_SetIO(SEG4_PORT, SEG4_PIN);

#define RESET_SEG1	Gpio_ClrIO(SEG1_PORT, SEG1_PIN);
#define RESET_SEG2	Gpio_ClrIO(SEG2_PORT, SEG2_PIN);
#define RESET_SEG3	Gpio_ClrIO(SEG3_PORT, SEG3_PIN);
#define RESET_SEG4	Gpio_ClrIO(SEG4_PORT, SEG4_PIN);


#define DISP_TIME        120*2  //显示退出时间，单位S。2分钟


extern void Screen(void);
#endif
//======================================================================================
