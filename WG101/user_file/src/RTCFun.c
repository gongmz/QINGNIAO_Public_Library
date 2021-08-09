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


#include "RTCFun.h"


uint8_t TmrSecTab[TMR_SEC_MAX_TMR];
uint8_t TmrMinTab[TMR_MIN_MAX_TMR];


static void  RTCMinFunction(void);

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
											}break;
						case 1:
											{
												Start1_1Sec();
												printf("Rtcfun..................\r\n");
											}break;
						case 2:
											{
											}break;
						case 3:
											{
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
										
								}break;

								case 1:
								{
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

