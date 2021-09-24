/********************************************************************************************************
* Filename   : FrameWork.h
* Programmer : 
* ���������������ȼ��Ķ��߳�ͷ�ļ���
*********************************************************************************************************
*/
#ifdef  FRAMEWORK_GLOBALS
#define FRAMEWORK_EXT
#else
#define FRAMEWORK_EXT  extern
#endif

#include "stdint.h"

#define OS_THREAD_MAX           8
#define FW_THREAD_MAX           8

#if OS_THREAD_MAX <= 8

// ===== TASK PRIORITIES =====
// ���ȼ����ν���
#define LED_PRIO                8
#define RTC_PRIO                7
#define LOGIC_PRIO              6
#define LORAFUN_PRIO            5
#define ADC_PRIO                4
#define UART_PRIO               3
#define RTCMIN_PRIO             2
#define COMM_PRIO               1

FRAMEWORK_EXT uint8_t ThreadReadyList;                // ��λ���ȼ���

#define ThreadSet(prio) (ThreadReadyList |= (1<<(prio-1)))  // �þ�����־��ʹ����ر��ж���Ӧ���������ٴ��ж�

#else

// ===== TASK PRIORITIES =====
// ���ȼ����ν���
#define LOGIC_PRIO              0
#define TICK_PRIO               1
#define KEY_PRIO                2
#define WIRECOM_PRIO            3
#define ICPROTOCOL_PRIO           4
#define SAMPLE_PRIO             5
#define IR_PRIO                 6
#define RTC_PRIO                7
#define STORAGE_PRIO            8
#define SCREEN_PRIO             9


FRAMEWORK_EXT uint8_t OSRdyGrp;                       /* Ready list group                         */
FRAMEWORK_EXT uint8_t OSRdyTbl[4];                    /* Table of tasks which are ready to run    */

FRAMEWORK_EXT void  ThreadSet(uint8_t prio);

#endif
FRAMEWORK_EXT uint8_t Msg[FW_THREAD_MAX];             // ������ȡ���ĵ�ǰ����Ϣ

FRAMEWORK_EXT void  ThreadScheduler(void);           // ����,�������Ҫѭ��ִ��
FRAMEWORK_EXT void  MsgPost(uint8_t prio, uint8_t msg);
FRAMEWORK_EXT void  MsgPostISR(uint8_t prio, uint8_t msg);
