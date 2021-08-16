
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

    if (Msg[LOGIC_PRIO - 1] & LOGIC_MENU_SHORT_PRESS) 
	{
        Msg[LOGIC_PRIO - 1] &= 0x7F;
        sig = LOGIC_MENU_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_MENU_LONG_PRESS) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xBF;
        sig = LOGIC_MENU_LONG_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_UP_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xDF;
        sig = LOGIC_UP_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_UP_LONG_PRESS) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xEF;
        sig = LOGIC_UP_LONG_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_DOWN_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xF7;
        sig = LOGIC_DOWN_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_DOWN_LONG_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xFB;
        sig = LOGIC_DOWN_LONG_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_ENTER_SHORT_PRESS) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xFD;
        sig = LOGIC_ENTER_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_ENTER_LONG_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xFE;
        sig = LOGIC_ENTER_LONG_PRESS;
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
					case LOGIC_MENU_SHORT_PRESS:
					{
						printf("short menu.....");
					}break;
                       
					case LOGIC_MENU_LONG_PRESS:
					{
						printf("long menu.....");
					}break;
                                               
					case LOGIC_UP_SHORT_PRESS:
					{
						printf("short up.....");
					}break;

					case LOGIC_UP_LONG_PRESS:
					{
						printf("long up.....");
					}break;
                       
					case LOGIC_DOWN_SHORT_PRESS:
					{
						printf("short down.....");
					}break;
                                               
					case LOGIC_DOWN_LONG_PRESS:
					{
						printf("long down.....");
					}break;
					
					case LOGIC_ENTER_SHORT_PRESS:
					{
						printf("short enter.....");
					}break;
                                               
					case LOGIC_ENTER_LONG_PRESS:
					{
						printf("long enter.....");
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
/*    MsgPost(LOGIC_PRIO, LOGIC_ENTRY_MSG);*/
}

