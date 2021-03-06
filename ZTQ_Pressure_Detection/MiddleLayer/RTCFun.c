/***************************************************************************************
****************************************************************************************
* FILE		: RTCFun.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/



/**********************************头文件**************************************/
#include "RTCFun.h"
#include "LCDDriver.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
uint8_t TmrSecTab[TMR_SEC_MAX_TMR];
uint8_t TmrMinTab[TMR_MIN_MAX_TMR];

static void  RTCMinFunction(void);
/**********************************函数声明************************************/



/*
 *  0.5s per time
 */
void TimerFunction(void)
{
    uint8_t i;
    
    
    for (i = 0; i < TMR_SEC_MAX_TMR; i++) 
		{
			if (TmrSecTab[i] != 0) //判断是否有定时的任务进来
			{
				if ((--TmrSecTab[i]) == 0) //定时的任务延时时间到则执行下面的程序
				{
					switch (i) 
					{
						case 0:
						{
							;
						}break;
						
						case 1:
						{
							Start1_1Sec();
							///< 启动单次转换采样
							Adc_SQR_Start();  
						}break;
						
						case 2://2分钟自动回主窗口
						{
							MsgPost(LOGIC_PRIO, LOGIC_RETURN_MAIN);
						}break;
						
						case 3:
						{
							;
						}break;
						
						case 4:
						{
							MsgPost(LORAFUN_PRIO,LORA_MSG_TMOUT1);
						}break;
						
						case 5:
						{

						}break;
						
						case 6:
						{
							 LoRaWorkStateTran(LORA_ST_POWERON);
							 WorkStateTran(MODE_NORMAL_ST);
						}break;
						
						case 7:
						{
							if(EnterShortKeyNum>=3) MsgPost(LORAFUN_PRIO,LORA_MSG_NSJOIN);
							EnterShortKeyNum = 0;
						}break;
						
						case 8:
						{
							
						}break;
						
						case 9:
						{
							;
						}break;
						
						case 10:
						{
							TmrSecStart(10,120);
							RTCMinFunction();
						}break;

						default:break;
					}
				}
			}
		}
}

/*
 *  60s per time
 */
static void  RTCMinFunction(void)
{

    uint8_t i;
    for (i = 0; i < TMR_MIN_MAX_TMR; i++)
	{
        if (TmrMinTab[i] != 0) {
            if ((--TmrMinTab[i]) == 0) {
                switch (i) {
								case 0:
								{
									Start0_60min();
									MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_EVENT);
								}break;

								case 1:
								{
									MsgPost(LORAFUN_PRIO,LORA_MSG_TMOUT2);
								}break;

								case 2:
								{

								}break;
								
								case 3:
								{

								}break;

								case 4:
								{

								}break;
                
                default:break;
                }
            }
        }
    }
}

