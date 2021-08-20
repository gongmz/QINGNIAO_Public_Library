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
#ifdef  LOGIC_GLOBALS
#define LOGIC_EXT
#else
#define LOGIC_EXT  extern
#endif
#include "stdint.h"
// ===== work state define =====
enum enumWorkState {
    MODE_POWER_ON_ST,       // power on ini state
    MODE_NORMAL_ST,         // normal state
    MODE_CARD_ST,           // card handle dispaly state
    MODE_VALVE_ST,          // valve action state
    MODE_TIMER_ST,          // count down display state
    MODE_FAULT_ST,          // fault disp state
    MODE_TEST_ST            // test state
};


// ===== message define =====
#define LOGIC_MENU_SHORT_PRESS   0x80        // 
#define LOGIC_MENU_LONG_PRESS    0x40        // 
#define LOGIC_UP_SHORT_PRESS     0x20        // 
#define LOGIC_UP_LONG_PRESS      0x10        // 
#define LOGIC_DOWN_SHORT_PRESS   0x08        // 
#define LOGIC_DOWN_LONG_PRESS    0x04        //  
#define LOGIC_ENTER_SHORT_PRESS  0x02        // 
#define	LOGIC_ENTER_LONG_PRESS   0x01        // 





//======================================================================================

//======================================================================================
LOGIC_EXT uint8_t WorkState;                 // ¹¤×÷×´Ì¬

LOGIC_EXT uint16_t gErrorBuf;




//======================================================================================
LOGIC_EXT void  Logic(void);
LOGIC_EXT void  SetLogicPrio(void);
LOGIC_EXT void  WorkStateTran(uint8_t state);
//======================================================================================

