/*
*********************************************************************************************************

* File : DATA_CPU.H
* By   : 
* �������������������ͣ������жϺ�
*********************************************************************************************************
*/

#ifndef _DATA_DEF_H
#define _DATA_DEF_H

#ifdef  DATA_DEF_GLOBALS
    #define DATA_DEF_EXT
#else
    #define DATA_DEF_EXT  extern
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/
//typedef  unsigned char 	uint8_t;
//typedef  unsigned int  	uint16_t;
//typedef  unsigned long 	uint32_t;
//typedef  signed char 		int8_t;
//typedef  signed int  		int16_t;
//typedef  signed long 		int32_t;
/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/

//#define  FALSE    0
//#define  TRUE     1
// enum {FALSE = 0, TRUE = !FALSE};

/*
* ͨ��ö�����Ͷ���
*/
//typedef enum
//{
//    false=0, true=!false
//} bool; //����ö������

/*
*********************************************************************************************************
*                              microchip  microcontroller
*********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    3

#if      OS_CRITICAL_METHOD == 1
    #define  OS_ENTER_CRITICAL()  asm SEI;          /* Disable interrupts                            */
    #define  OS_EXIT_CRITICAL()   asm CLI;          /* Enable  interrupts                            */
#endif


#if      OS_CRITICAL_METHOD == 2
    #define  OS_ENTER_CRITICAL()  (cpu_sr = _emi, _emi = 0) /* Disable interrupts                        */
    #define  OS_EXIT_CRITICAL()   ( _emi = cpu_sr)          /* Enable  interrupts                        */
#endif

#if      OS_CRITICAL_METHOD == 3
    #define  OS_ENTER_CRITICAL()   __disable_irq()     /* Disable interrupts                        */
    #define  OS_EXIT_CRITICAL()    __enable_irq()      /* Enable  interrupts                        */
#endif

#define ResetWatchDog() 	  Wdt_Feed()

#endif
