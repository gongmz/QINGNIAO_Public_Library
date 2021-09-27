
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

#define TOTAL_NUM_2ND    6//
//字母代码
#define 	CHAR_A   0x77  //A
#define 	CHAR_b   0x7C  //b
#define 	CHAR_C   0x39  //C
#define 	CHAR_c   0x58  //c
#define 	CHAR_d   0x5E  //d
#define 	CHAR_E   0x79  //E
#define 	CHAR_F   0x71  //F
#define 	CHAR_H   0x76  //H
#define 	CHAR_h   0x74  //h
#define 	CHAR_L   0x38  //L
#define 	CHAR_n   0x54  //n
#define 	CHAR_N   0x37  //N
#define 	CHAR_o   0x5C  //o
#define 	CHAR_P   0x73  //P
#define 	CHAR_r   0x50  //r
#define 	CHAR_t   0x78  //t
#define 	CHAR_U   0x3E  //U




#define SET_LED1	Gpio_SetIO(LED1_PORT, LED1_PIN)
#define SET_LED2	Gpio_SetIO(LED2_PORT, LED2_PIN)
#define SET_LED3	Gpio_SetIO(LED3_PORT, LED3_PIN)
#define SET_LED4	Gpio_SetIO(LED4_PORT, LED4_PIN)

#define RESET_LED1	Gpio_ClrIO(LED1_PORT, LED1_PIN)
#define RESET_LED2	Gpio_ClrIO(LED2_PORT, LED2_PIN)
#define RESET_LED3	Gpio_ClrIO(LED3_PORT, LED3_PIN)
#define RESET_LED4	Gpio_ClrIO(LED4_PORT, LED4_PIN)

#define SET_SEG1	Gpio_SetIO(SEG1_PORT, SEG1_PIN)
#define SET_SEG2	Gpio_SetIO(SEG2_PORT, SEG2_PIN)
#define SET_SEG3	Gpio_SetIO(SEG3_PORT, SEG3_PIN)
#define SET_SEG4	Gpio_SetIO(SEG4_PORT, SEG4_PIN)

#define RESET_SEG1	Gpio_ClrIO(SEG1_PORT, SEG1_PIN)
#define RESET_SEG2	Gpio_ClrIO(SEG2_PORT, SEG2_PIN)
#define RESET_SEG3	Gpio_ClrIO(SEG3_PORT, SEG3_PIN)
#define RESET_SEG4	Gpio_ClrIO(SEG4_PORT, SEG4_PIN)


extern volatile uint8_t gGui_State;     
extern volatile uint8_t gGui_2nd_Num;
extern volatile uint8_t gGui_3rd_Num;	
extern uint8_t g_edit_area;//数码管当前编辑区域   1：个位
extern uint8_t g_bar_tube_num;
extern void Screen(void);
extern uint16_t HEX2BCD(uint16_t hex_data);// HEX转BCD子程序 
extern uint16_t BCD2HEX(uint16_t bcd_data);//BCD转为HEX子程序 
extern uint16_t  HexsTochars(uint8_t *ascs,uint8_t *hexs,uint16_t length);
extern uint8_t charsToHex(uint8_t *asc);
extern uint8_t DigitalCalculate(const uint16_t *data);
extern void  LcdReturnMain(void);
#endif
//======================================================================================
