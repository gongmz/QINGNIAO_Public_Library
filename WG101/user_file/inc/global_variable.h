#ifndef _global_variable_h
#define _global_variable_h
/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "stdio.h"
#include "rtc.h"
/**********************************DEBUG����**********************************/
// Log ��ӡ
#define Printf_Enable
/**********************************�궨������**********************************/
#define BUFFERSIZE  128
/**********************************֡�̶��ַ�����******************************/
/**********************************�ṹ������**********************************/
struct _uart
{
	uint8_t Buffer[BUFFERSIZE];
	uint16_t TimeCounter;//��ʱ����ʱʱ��*TimeCounterδ�յ������ж�Ϊһ֡
	uint16_t Length;//����֡����
	uint8_t RxFlag;	//���������Ƿ�������ݴ���ı�־λ
	uint8_t RxProcess;//�����˴������ڽ�������
};
/**********************************���ź궨��**********************************/
//FIRE  
#define DIO1_PORT  GpioPortB
#define DIO1_PIN   GpioPin3

//����
#define MENU_PORT   GpioPortB
#define MENU_PIN    GpioPin4
#define UP_PORT     GpioPortB
#define UP_PIN      GpioPin5
#define DOWN_PORT   GpioPortB
#define DOWN_PIN    GpioPin6
#define ENTER_PORT  GpioPortB
#define ENTER_PIN   GpioPin7
//LED����
#define LED1_PORT   GpioPortB
#define LED1_PIN    GpioPin8
#define LED2_PORT   GpioPortB
#define LED2_PIN    GpioPin9
#define LED3_PORT   GpioPortB
#define LED3_PIN    GpioPin10
#define LED4_PORT   GpioPortB
#define LED4_PIN    GpioPin11

#define SEG1_PORT   GpioPortB
#define SEG1_PIN    GpioPin12
#define SEG2_PORT   GpioPortB
#define SEG2_PIN    GpioPin13
#define SEG3_PORT   GpioPortB
#define SEG3_PIN    GpioPin14
#define SEG4_PORT   GpioPortB
#define SEG4_PIN    GpioPin15
/**********************************��������************************************/

extern uint16_t ErrorCode;
extern uint16_t PressureValue;
#endif
