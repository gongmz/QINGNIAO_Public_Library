/********************************************************************************************************
* Filename   : FrameWork.C
* Programmer : 
* ���������������ȼ��Ķ��߳�
*         ֻ�ܶ������16�����ȼ�������߳�ͬʱ����ʱ����ִ��������ȼ���
*********************************************************************************************************
*/
#define  FRAMEWORK_GLOBALS
#include "Includes.h"

#if OS_THREAD_MAX <= 8

/*���8���̣߳�������8λ����1~8���ȼ�1��ͣ�8���*/
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
			  {   //�ҳ������߳��е�������ȼ����߳�
							prionum = PRIORITY_TABLE[ready >> 4] + 4;
				} 
			  else 
			  {
							prionum = PRIORITY_TABLE[ready];
				}
					
					ready = READY_CLR_AND[prionum];
					OS_ENTER_CRITICAL();
					ThreadReadyList &= ready;//ִ����ɣ������λ
					OS_EXIT_CRITICAL();

					if(prionum) ResetWatchDog();
					
				switch (prionum) 
			  {
					case 8://������ȼ�
										//ִ���߳�
					      Screen();//LEDˢ�³���
						  TaskKey();
								break;
					case 7:
										//ִ���߳�
										TimerFunction();// RTC
								break;
					case 6:
										//ִ���߳�
		 //               JudgeKEY();

								break;
					case 5:
										//ִ���߳�  
								break;
					case 4:{

						}break;
					case 3:
			 
								break;
					case 2:
										//ִ���߳�
		//				RTCMinFunction();   // RTC minute
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

/*���16���̣߳�0~15���ȼ�0��ߣ�15��ͣ�
  ����uCOS-II������ȷ�����д*/
uint8_t const OSMapTbl[] = {0x01, 0x02, 0x04, 0x08};
uint8_t const OSUnMapTbl[] = {
    0u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u /* 0x00 to 0x0F */
};

/*�߳̾���������ʹ����ر��ж���Ӧ���������ٴ��ж�*/
void  ThreadSet(uint8_t prio)
{
    OSRdyGrp |=OSMapTbl[prio>>2];
    OSRdyTbl[prio>>2] |= OSMapTbl[prio&0x03];
}

void  ThreadScheduler(void)
{
    uint8_t prionum,y;

    if (OSRdyGrp != 0) {    // ���������
        y = OSUnMapTbl[OSRdyGrp];                                       // �ҳ������߳��е�������ȼ����߳�
        prionum = (uint8_t)((y << 2) + OSUnMapTbl[OSRdyTbl[y]]);

        OS_ENTER_CRITICAL();
        if ((OSRdyTbl[prionum>>2] &= ~OSMapTbl[prionum&0x03]) == 0) {   // ִ����ɣ������λ
            OSRdyGrp &= ~OSMapTbl[prionum >>2];
        }
        OS_EXIT_CRITICAL();

        switch (prionum) {
        case 0://������ȼ�
            //ִ���߳�
            Calculation_Volume();                   //��������
            break;
        case 1:
            //ִ���߳�
            Calculation_Volume_mini();             
            break;
        case 2:
            //ִ���߳�
            Scanif_Calibration();                         
            break;
        case 3:
            //ִ���߳�
            JudgeKEY();                   
            break;
        case 4:
            //ִ���߳�
            CommHandle();     
            break;
        case 5:
            //ִ���߳�
            Screen();        
            break;
        case 6:
            //ִ���߳�
            Fram();        
            break;
        case 7:
            //ִ���߳�
            TimerFunction();        // RTC
            break;
        case 8:
            //ִ���߳�
            FRAMStorage();          // Storage
            break;
        case 9:
            //ִ���߳�
            ICProtocol();           // IC Card Protocol
            break;
        case 10:
            //ִ���߳�
            StepFunction();
            break;
        case 11:
            //ִ���߳�
            Beep();
            break; 
        case 12:
            //ִ���߳�
            RTCMinFunction();
            break;
        case 13:
            //ִ���߳�
            break;
        case 14:
            //ִ���߳�
            break;
        case 15:
            //ִ���߳�
            break;
        default:break;
        }
    }
}

#endif

/***********************************************************************
����ԭ�ͣ�void MsgPost(uint8_t prio, uint8_t msg)
����˵������Ϣ���͵���ǰ��Ϣ����,�߳��е���
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
    ThreadSet(prio);            //�þ���λ
    OS_EXIT_CRITICAL();
}
/***********************************************************************
����ԭ�ͣ�void MsgPostISR(uint8_t prio, uint8_t sig)
����˵�����¼����͵���ǰ��Ϣ�������ж��е���
***********************************************************************
*/
void  MsgPostISR(uint8_t prio, uint8_t msg)
{
#if OS_THREAD_MAX <= 8
    Msg[prio-1] |= msg;
#else
    Msg[prio] |= msg;
#endif
    ThreadSet(prio);            //�þ���λ
}

