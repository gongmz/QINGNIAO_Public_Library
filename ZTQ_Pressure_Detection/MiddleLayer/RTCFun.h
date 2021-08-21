/*
       /_/_/_/_/   /_/_/_/     /_/_/_/_/
           /_/    /_/    _/   /_/
          /_/    /_/_/_/_    /_/_/_/_/
   /_/   /_/    /_/     _/  /_/
    /_/_/_/    /_/_/_/_/   /_/

    Copyright (c) 2020 Jade Bird Fire Co., Ltd, All right reserved.
*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef	RTCFUN_H
#define RTCFUN_H

#include "stdint.h"
#include "init.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#define TMR_SEC_MAX_TMR             11  //0.5S计时器数量
#define TMR_MIN_MAX_TMR             5   //1min计时器数量


extern uint8_t TmrSecTab[TMR_SEC_MAX_TMR];
extern uint8_t TmrMinTab[TMR_MIN_MAX_TMR];
//====================================================================================================
//====================================================================================================
#define TmrSecStart(n, tenths) (TmrSecTab[n] = tenths)
#define TmrSecStop(n) (TmrSecTab[n] = 0)
#define TmrSecGet(n) (TmrSecTab[n])

#define TmrMinStart(n, minute) (TmrMinTab[n] = minute)
#define TmrMinStop(n) (TmrMinTab[n] = 0)

//====================================================================================================
#define Start0_1Sec()                 TmrSecStart(0,2)
#define Stop0_Sec_Timer()             TmrSecStop(0)

#define Start1_1Sec()                 TmrSecStart(1,2) 

#define Start2_120Sec()               TmrSecStart(2,240) 
#define Stop2_Sec_Timer()             TmrSecStop(2)

#define Start3_3Sec()                 TmrSecStart(3,3) 
 
#define Start4_1Sec()                 TmrSecStart(4,1) 
#define Start4_3Sec()                 TmrSecStart(4,3) 
#define Stop4_Sec_Timer()             TmrSecStop(4)

#define Start5_1Sec()                 TmrSecStart(5,1) 
#define Stop5_Sec_Timer()             TmrSecStop(5)

#define Start6_1Sec()                 TmrSecStart(6,1) 
#define Stop6_Sec_Timer()             TmrSecStop(6)

#define Start7_10Sec()                TmrSecStart(7,10) 
#define Start7_8Sec()                 TmrSecStart(7,8) 

#define Start8_1Sec()                 TmrSecStart(8,1)

#define Start9_3Sec()                 TmrSecStart(9,3)

#define Start_min_timer()             TmrSecStart(10,60) 


//====================================================================================================
#define Start0_60min()                TmrMinStart(0,60) 
#define Start0_240min()               TmrMinStart(0,240) 
#define Stop0_min_timer()             TmrMinStop(0)

#define Start1_6min()                 TmrMinStart(1,6) 
#define Stop1_min_timer()             TmrMinStop(1)

//====================================================================================================
extern void TimerFunction(void);

//====================================================================================================
#endif
