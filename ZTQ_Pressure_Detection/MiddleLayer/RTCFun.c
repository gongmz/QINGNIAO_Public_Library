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



/**********************************ͷ�ļ�**************************************/
#include "RTCFun.h"
#include "LCDDriver.h"
/**********************************�궨������**********************************/
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
uint8_t TmrSecTab[TMR_SEC_MAX_TMR];
uint8_t TmrMinTab[TMR_MIN_MAX_TMR];

static void  RTCMinFunction(void);
/**********************************��������************************************/



/*
 *  0.5s per time
 */
void TimerFunction(void)
{
    uint8_t i;
    
    
    for (i = 0; i < TMR_SEC_MAX_TMR; i++) 
		{
			if (TmrSecTab[i] != 0) //�ж��Ƿ��ж�ʱ���������
			{
				if ((--TmrSecTab[i]) == 0) //��ʱ��������ʱʱ�䵽��ִ������ĳ���
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
								///< ��������ת������
								Adc_SQR_Start();   
						}break;
						
						case 2://2�����Զ���������
						{
							MsgPost(LOGIC_PRIO, LOGIC_ENTER_MAIN);
						}break;
						
						case 3:
						{
							;
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

