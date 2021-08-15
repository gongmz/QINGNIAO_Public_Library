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
#define LOGIC_ENTRY_MSG         0x80        // 
#define LOGIC_CARDHANDEL_MSG    0x40        // 
#define LOGIC_VALVEHANDEL_MSG   0x20        // 
#define LOGIC_ERRORHANDEL_MSG   0x10        // 
#define LOGIC_TIMERHANDEL_MSG   0x08        // 
#define LOGIC_LOWVOLTAGE_MSG    0x04        //  
#define LOGIC_SWITCHERROR_MSG   0x02        // 
#define	LOGIC_UPDATEAMOUNT_MSG  0x01        // 





//======================================================================================

//======================================================================================
LOGIC_EXT uint8_t WorkState;                 // ¹¤×÷×´Ì¬

LOGIC_EXT uint16_t gErrorBuf;




//======================================================================================
LOGIC_EXT void  Logic(void);
LOGIC_EXT void  SetLogicPrio(void);
LOGIC_EXT void  WorkStateTran(uint8_t state);
//======================================================================================

