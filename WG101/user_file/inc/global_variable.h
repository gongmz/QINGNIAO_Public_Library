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
#define CJ188_START_CODE      0x68    //֡��ʼ��
#define CJ188_END_CODE        0x16    //��������
#define CJ188_SERIAL_NO       0x00    //���к�
#define CJ188_DEVICE_TYPE     0x10    //ˮ��
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
#define DIO1_PORT  GpioPortB
#define DIO1_PIN   GpioPin6
/**********************************��������************************************/

extern uint16_t ErrorCode;
#endif
