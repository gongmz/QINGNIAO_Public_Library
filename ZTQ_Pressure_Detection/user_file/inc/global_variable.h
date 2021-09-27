/*
       /_/_/_/_/   /_/_/_/     /_/_/_/_/
           /_/    /_/    _/   /_/
          /_/    /_/_/_/_    /_/_/_/_/
   /_/   /_/    /_/     _/  /_/
    /_/_/_/    /_/_/_/_/   /_/

    Copyright (c) 2020 Jade Bird Fire Co., Ltd, All right reserved.
*/
#ifndef _global_variable_h
#define _global_variable_h
/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "stdio.h"
#include "rtc.h"
/**********************************DEBUG����**********************************/
// Log ��ӡ
//#define Printf_Enable
/**********************************�궨������**********************************/
#define BUFFERSIZE  128

//�豸������Ϣ
#define DEVICE_CPSN		    0
#define DEVICE_CLASS        0x3C  //��������ѹ��������
#define DEVICE_TYPE	        0         
#define DEVICE_HV           0    //Ӳ���汾��
#define DEVICE_SV		    0    //����汾��
#define DEVICE_NET	    	1    //���ܴ������ͣ�CLASS A��0   CLASS C:1


/*ZTQ-D2001 �ϴ��豸״̬��DeviceState����־λ����*/
#define DS_FAULT                0x02 //����״̬
#define DS_OUTRANGE             0x04 //������
#define DS_SENSOR_ERROR         0x08 //����������
#define DS_UNDER_PRESSURE       0x10 //Ƿѹ����
#define DS_ONLINE		        0x20 //����״̬
#define DS_OVER_PRESSURE		0x40 //��ѹ����
#define DS_RELAY_OUTPUT         0x80 //�̵������
#define DS_TEMP_FAULT	        0x100 //�¶ȹ���
#define DS_DETECTION_MODE       0x200 //���ģʽ
#define DS_UNDER_PRESSURE_WARN  0x400 //ǷѹԤ��
#define DS_OVER_PRESSURE_WARN   0x800 //��ѹԤ��

/*�ϴ��¼���־λ����*/
#define FIREALARM_EVENT         0x03   //��
#define FIREALARMCANCLE_EVENT   0x39   //��ȡ��

#define SEPARATEERR_EVENT       0x58   //�������
#define SEPARATECANCLE_EVENT    0x6C   //�����������

#define LOWVOLTAGE_EVENT        0x55   //Ƿѹ����
#define NORMALVLITAGE_EVENT     0x69   //��ѹ����

#define SELFCHECK_EVENT         0x7B   //�Լ��¼�

/*ģ�鴫��������Ϣ����   +NSSTATE  MSG*/
#define NET_MSG_NULL            0  // ����Ϣ
#define NET_MSG_ALIVE_NAK       1  // Unconfirm ���� 
#define NET_MSG_ALIVE           2  // Confirm ���� 
#define NET_MSG_VERBOSE         3  // ������ 
#define NET_MSG_EVENT_RES_NAK   4  // ��Ӧ���¼�
#define NET_MSG_EVENT           5  // �¼�
#define NET_MSG_JOIN            6  // ����
#define NET_MSG_JOIN_ACCEPT_ACK 7  // ����ȷ�� 

/**********************************֡�̶��ַ�����******************************/
/**********************************�ṹ������**********************************/
typedef enum
{
    VoltageDetection,   //��ѹ���
    CurrentDetection    //�������
}Type_t;

//ϵͳ����
typedef struct 
{
	uint8_t  FrameHead;
    uint16_t Range;  					//����
    uint16_t OverPreaaureWarn;			//��ѹԤ��
    uint16_t OverPreaaureAlarm;         //��ѹ����
    uint16_t UnderPreaaureWarn;         //ǷѹԤ��
    uint16_t UnderPreaaureAlarm;        //Ƿѹ����
    Type_t  DetectionMode;				//��ѹ����������
	uint8_t  FrameEnd;				    
}SysParameter_t;

extern SysParameter_t  SysParameter;
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
//FIRE�ⲿ���
#define FIRE1_PORT   GpioPortA
#define FIRE1_PIN    GpioPin8
#define FIRE2_PORT   GpioPortA
#define FIRE2_PIN    GpioPin9
#define FIRE3_PORT   GpioPortA
#define FIRE3_PIN    GpioPin10
#define FIRE4_PORT   GpioPortA
#define FIRE4_PIN    GpioPin11
//���߿���
#define RF_EN_PORT   GpioPortA
#define RF_EN_PIN    GpioPin15
//��ѹ��������л�����
#define SETI_PORT   GpioPortD
#define SETI_PIN    GpioPin6
//24V��Դ����
#define SENSOR_EN_PORT   GpioPortD
#define SENSOR_EN_PIN    GpioPin7
//24V��Դ����
#define SETKEY_PORT   GpioPortB//���ƿ������ļ��
#define SETKEY_PIN    GpioPin2
/**********************************��������************************************/
extern uint16_t ErrorCode;
extern uint16_t PressureValue;
extern uint16_t DeviceState;
extern uint8_t DeviceEvent;
#endif
