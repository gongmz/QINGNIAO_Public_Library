
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
/**********************************头文件**************************************/
#include "includes.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
EditData_t  EditData;
uint8_t WorkState; 
uint16_t gErrorBuf;
/**********************************函数声明************************************/
void  Logic(void);
void  SetLogicPrio(void);
void  WorkStateTran(uint8_t state);


void  Logic(void)
{
    uint8_t sig;

    if (Msg[LOGIC_PRIO - 1] & LOGIC_ENTRY_MSG) 
	{
        Msg[LOGIC_PRIO - 1] &= 0x7F;
        sig = LOGIC_ENTRY_MSG;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_RETURN_MAIN) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xBF;
        sig = LOGIC_RETURN_MAIN;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_UP_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xDF;
        sig = LOGIC_UP_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_NORMAL_MSG) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xEF;
        sig = LOGIC_NORMAL_MSG;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_DOWN_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xF7;
        sig = LOGIC_DOWN_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_ALARM_MSG)
	{
        Msg[LOGIC_PRIO - 1] &= 0xFB;
        sig = LOGIC_ALARM_MSG;
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
 					case LOGIC_ENTRY_MSG:
					{
						DeviceState &= ~DS_RELAY_OUTPUT;
						Gpio_ClrIO(FIRE4_PORT, FIRE4_PIN);//继电器输出
					}break;  

 					case LOGIC_ALARM_MSG:
					{
							WorkStateTran(MODE_ALARM_ST);
					}break;  					
					case LOGIC_RETURN_MAIN:
					{
						LcdReturnMain();
					}break;
                                               
					default:
					WorkStateTran(MODE_NORMAL_ST);break;
                }break;
			
			case MODE_ALARM_ST:
        switch (sig) 
				{
					case LOGIC_ENTRY_MSG:
					{
						DeviceState |= DS_RELAY_OUTPUT;
						Gpio_SetIO(FIRE4_PORT, FIRE4_PIN);//继电器输出
						MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_EVENT);//报警上传信息
					}break;
					
					case LOGIC_RETURN_MAIN:
					{
						LcdReturnMain();
					}break;
					
					case LOGIC_NORMAL_MSG:
					{
						MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_EVENT);//上传报警消除信息
						WorkStateTran(MODE_NORMAL_ST);
					}break;
					default:break;
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

