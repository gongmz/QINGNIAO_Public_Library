/********************************************************************************************************
* Filename   : FrameWork.h
* Programmer : 
* 描述：　基于优先级的多线程头文件。
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
// 优先级依次降低
#define LED_PRIO                8
#define RTC_PRIO                7
#define LOGIC_PRIO              6
#define LORAFUN_PRIO            5
#define UART_PRIO               4
#define STORAGE_PRIO            3
#define RTCMIN_PRIO             2
#define COMM_PRIO               1

FRAMEWORK_EXT uint8_t ThreadReadyList;                // 高位优先级高

#define ThreadSet(prio) (ThreadReadyList |= (1<<(prio-1)))  // 置就绪标志，使用需关闭中断响应，结束后再打开中断

#else

// ===== TASK PRIORITIES =====
// 优先级依次降低
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
FRAMEWORK_EXT uint8_t Msg[FW_THREAD_MAX];             // 队列中取出的当前用消息

FRAMEWORK_EXT void  ThreadScheduler(void);           // 调度,这个函数要循环执行
FRAMEWORK_EXT void  MsgPost(uint8_t prio, uint8_t msg);
FRAMEWORK_EXT void  MsgPostISR(uint8_t prio, uint8_t msg);
