/*
------------------------------------------------------------------------------------------------------------------------
@
@       File Name   :       Logic.h
@
@       Brief       :
@
@       Date        :       2021/08/11
------------------------------------------------------------------------------------------------------------------------
*/
#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "stdint.h"
// ===== work state define =====
enum enumWorkState {
    MODE_POWER_ON_ST,       // power on ini state
    MODE_NORMAL_ST,         // normal state
    MODE_TIMER_ST,          // count down display state
    MODE_ALARM_ST,          // fault disp state
};

//当前处理数据
typedef struct 
{
	uint8_t uint;//个位
	uint8_t decade;
	uint8_t hundred;
	uint8_t thousand;			    
}EditData_t;

extern EditData_t  EditData;
// ===== message define =====
#define LOGIC_MENU_SHORT_PRESS   0x80        // 
#define LOGIC_MENU_LONG_PRESS    0x40        // 
#define LOGIC_UP_SHORT_PRESS     0x20        // 
#define LOGIC_NORMAL_MSG         0x10        // 
#define LOGIC_DOWN_SHORT_PRESS   0x08        // 
#define LOGIC_ALARM_MSG          0x04        //  
#define LOGIC_ENTER_SHORT_PRESS  0x02        // 
#define	LOGIC_ENTER_LONG_PRESS   0x01        // 





//======================================================================================

//======================================================================================
extern uint8_t WorkState;                 // 工作状态

extern uint16_t gErrorBuf;
//======================================================================================
extern void  Logic(void);
extern void  SetLogicPrio(void);
extern void  WorkStateTran(uint8_t state);
//======================================================================================
#endif /* __LOGIC_H__ */

