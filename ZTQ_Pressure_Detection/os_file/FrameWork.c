/********************************************************************************************************
* Filename   : FrameWork.C
* Programmer : 
* 描述：　基于优先级的多线程
*         只能定义最多16个优先级，多个线程同时就绪时，先执行最高优先级。
*********************************************************************************************************
*/
#define  FRAMEWORK_GLOBALS
#include "Includes.h"

#if OS_THREAD_MAX <= 8

/*最多8个线程，适用于8位机，1~8优先级1最低，8最高*/
uint8_t const  PRIORITY_TABLE[]= {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
uint8_t const  READY_CLR_AND[] = {0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

void ThreadScheduler(void)
{
    uint8_t prionum,ready;

    prionum = 0;
    ready = ThreadReadyList;

    if (ready != 0) 
		{
				if ((ready & 0xF0) != 0U) 
			  {   //找出就绪线程中的最高优先级的线程
							prionum = PRIORITY_TABLE[ready >> 4] + 4;
				} 
			  else 
			  {
							prionum = PRIORITY_TABLE[ready];
				}
					
					ready = READY_CLR_AND[prionum];
					OS_ENTER_CRITICAL();
					ThreadReadyList &= ready;//执行完成，清就绪位
					OS_EXIT_CRITICAL();

					if(prionum) ResetWatchDog();
					
				switch (prionum) 
			  {
					case 8://最高优先级
										//执行线程
					      Screen();//LED刷新程序
						   TaskKey();
							if(UsartRxData.UartIntFlag)
							{
								if(++UsartRxData.UartRxCnt>20)
								{
									UsartRxData.UartRxCnt=0;
									UsartRxData.UartIntFlag=0;
									MsgPost(UART_PRIO, LORA_MSG_ENTRY);
								}
							}
								break;
					case 7:
										//执行线程
										TimerFunction();// RTC
								break;
					case 6:
										//执行线程
		                Logic();

								break;
					case 5:
							TaskLoRa();			//执行线程  
								break;
					case 4:{
						TaskUart();
						}break;
					case 3:
			 
								break;
					case 2:
										//执行线程
								break;
					case 1:
										{ 
		//			        CommHandle();
		//                    CommReset();
						}break;
					default:break;
				}
			}
}

#else

/*最多16个线程，0~15优先级0最高，15最低，
  基于uCOS-II任务调度方法编写*/
uint8_t const OSMapTbl[] = {0x01, 0x02, 0x04, 0x08};
uint8_t const OSUnMapTbl[] = {
    0u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u /* 0x00 to 0x0F */
};

/*线程就绪函数，使用需关闭中断响应，结束后再打开中断*/
void  ThreadSet(uint8_t prio)
{
    OSRdyGrp |=OSMapTbl[prio>>2];
    OSRdyTbl[prio>>2] |= OSMapTbl[prio&0x03];
}

void  ThreadScheduler(void)
{
    uint8_t prionum,y;

    if (OSRdyGrp != 0) {    // 有任务就绪
        y = OSUnMapTbl[OSRdyGrp];                                       // 找出就绪线程中的最高优先级的线程
        prionum = (uint8_t)((y << 2) + OSUnMapTbl[OSRdyTbl[y]]);

        OS_ENTER_CRITICAL();
        if ((OSRdyTbl[prionum>>2] &= ~OSMapTbl[prionum&0x03]) == 0) {   // 执行完成，清就绪位
            OSRdyGrp &= ~OSMapTbl[prionum >>2];
        }
        OS_EXIT_CRITICAL();

        switch (prionum) {
        case 0://最高优先级
            //执行线程
            Calculation_Volume();                   //计算流量
            break;
        case 1:
            //执行线程
            Calculation_Volume_mini();             
            break;
        case 2:
            //执行线程
            Scanif_Calibration();                         
            break;
        case 3:
            //执行线程
            JudgeKEY();                   
            break;
        case 4:
            //执行线程
            CommHandle();     
            break;
        case 5:
            //执行线程
            Screen();        
            break;
        case 6:
            //执行线程
            Fram();        
            break;
        case 7:
            //执行线程
            TimerFunction();        // RTC
            break;
        case 8:
            //执行线程
            FRAMStorage();          // Storage
            break;
        case 9:
            //执行线程
            ICProtocol();           // IC Card Protocol
            break;
        case 10:
            //执行线程
            StepFunction();
            break;
        case 11:
            //执行线程
            Beep();
            break; 
        case 12:
            //执行线程
            RTCMinFunction();
            break;
        case 13:
            //执行线程
            break;
        case 14:
            //执行线程
            break;
        case 15:
            //执行线程
            break;
        default:break;
        }
    }
}

#endif

/***********************************************************************
函数原型：void MsgPost(uint8_t prio, uint8_t msg)
功能说明：消息发送到当前消息变量,线程中调用
***********************************************************************
*/
void  MsgPost(uint8_t prio, uint8_t msg)
{
    OS_ENTER_CRITICAL();
#if OS_THREAD_MAX <= 8
    Msg[prio-1] |= msg;
#else
    Msg[prio] |= msg;
#endif
    ThreadSet(prio);            //置就绪位
    OS_EXIT_CRITICAL();
}
/***********************************************************************
函数原型：void MsgPostISR(uint8_t prio, uint8_t sig)
功能说明：事件发送到当前消息变量，中断中调用
***********************************************************************
*/
void  MsgPostISR(uint8_t prio, uint8_t msg)
{
#if OS_THREAD_MAX <= 8
    Msg[prio-1] |= msg;
#else
    Msg[prio] |= msg;
#endif
    ThreadSet(prio);            //置就绪位
}

