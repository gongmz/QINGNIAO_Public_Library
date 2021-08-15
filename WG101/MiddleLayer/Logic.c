
/***************************************************************************************
****************************************************************************************
* FILE		: Logic.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/


#define  LOGIC_GLOBALS
#include "Includes.h"


static uint8_t gDispState = 1;


void  Logic(void)
{
    uint8_t sig;

    if (Msg[LOGIC_PRIO - 1] & LOGIC_ENTRY_MSG) 
	{
        Msg[LOGIC_PRIO - 1] &= 0x7F;
        sig = LOGIC_ENTRY_MSG;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_VALVEHANDEL_MSG) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xDF;
        sig = LOGIC_VALVEHANDEL_MSG;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	)
	{
        Msg[LOGIC_PRIO - 1] &= 0xEF;
        sig = LOGIC_ERRORHANDEL_MSG;
    } 
	else
    {
        sig = Msg[LOGIC_PRIO - 1];
        Msg[LOGIC_PRIO - 1] = 0;
    }

    switch (WorkState) 
		{
			case MODE_NORMAL_ST:
                switch (sig) 
				{
					case LOGIC_ENTRY_MSG:
					{
						
					}break;
                       
					case LOGIC_ERRORHANDEL_MSG:{
                        WorkStateTran(MODE_FAULT_ST);
					}break;
                                               
					case LOGIC_VALVEHANDEL_MSG:{
                        WorkStateTran(MODE_VALVE_ST);
                    }break;
                        
					default:
                        WorkStateTran(MODE_NORMAL_ST);break;
                }break;

            //--------------------------------------------------------------------------------------------------------------------

            //----------------------------------------------------------------------------------

            //----------------------------------------------------------------------------------
            default:
                WorkStateTran(MODE_NORMAL_ST);break;
        }

        SetLogicPrio();
}

void  SetLogicPrio(void)
{
    if (Msg[LOGIC_PRIO - 1] != 0)
		{
        OS_ENTER_CRITICAL();
        ThreadSet(LOGIC_PRIO);
        OS_EXIT_CRITICAL();
    }
}

void  WorkStateTran(uint8_t state)
{
    WorkState = state;
    MsgPost(LOGIC_PRIO, LOGIC_ENTRY_MSG);
}

