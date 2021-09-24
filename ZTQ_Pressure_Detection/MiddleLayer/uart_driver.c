/***************************************************************************************
****************************************************************************************
* FILE		: uart_drive.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/
#include "Includes.h"

#define SLAVEADDR   0x30

char   DataTxBuff[TXDATA_BUF_MAX];
struct _UsartRxData UsartRxData;//�������ݻ�����
static void ClearRxBuffer(void);

/****************************************************************************** 
* �������ƣ�TaskUart()
* �������ܣ���������
* �����������
* �����������
* �������أ���
* ʹ��˵����
******************************************************************************/
void TaskUart(void)
{
	uint8_t i=0;
	uint8_t para;
	uint8_t para1;
	
	

	for(i=0;i<UsartRxData.RxLength;i++)
	{
		if(UsartRxData.RxBuffer[i]=='O'&&
			UsartRxData.RxBuffer[i+1]=='K')
						{
							MsgPost(LORAFUN_PRIO,LORA_MSG_RX_OK);
						}
	}


	for(i=0;i<UsartRxData.RxLength;i++)
	{
		if(UsartRxData.RxBuffer[i]=='+'&&
			UsartRxData.RxBuffer[i+1]=='N'&&
				UsartRxData.RxBuffer[i+2]=='S'&&
					UsartRxData.RxBuffer[i+3]=='S'&&
						UsartRxData.RxBuffer[i+4]=='T'&&
							UsartRxData.RxBuffer[i+5]=='A'&&
								UsartRxData.RxBuffer[i+6]=='T'&&
									UsartRxData.RxBuffer[i+7]=='E')
						{
							para = UsartRxData.RxBuffer[i+9]-0x30;
							para1 = UsartRxData.RxBuffer[i+11]-0x30;
							if(para1 == NET_MSG_EVENT)//�����¼�
							{
								if(para == 2)//���ͳɹ�
									MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_OK);
								else if(para == 3)//���ʹ���
									MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_ERROR);
							}
#ifdef	UPLOAD_ANALOG
							else if(para1 == NET_MSG_ALIVE)//����confim������ҪЯ��ģ�������¸����ϴ�ģ�������󣬹�����
							{
								temp_event.event = 0;
								temp_event.state = DeviceState;

								if(EnQueue(&FireQueue,temp_event))//���¼��������
								{
									LoRaStateTran(LORA_ST_DEQUEUE);
								}
								LORA_CONFIM_ACK_FLAG = 1;
							}
#endif	
						}
	}
	ClearRxBuffer();
}

/****************************************************************************** 
* �������ƣ�StartUartPackageTx
* �������ܣ���ʼ���ڷ������ݣ��жϷ�ʽ��
* ���������
* �����������
* �������أ���
* ʹ��˵���� 
******************************************************************************/
void StartUartPackageTx(void)
{
    M0P_UART1->SBUF = (1<<8)|SLAVEADDR;//���͵�ַ�����ж�
    Uart_EnableIrq(M0P_UART1,UartTxIrq);             ///<ʹ�ܴ��ڷ����ж�
}


/****************************************************************************** 
* �������ƣ�ClearRxBuffer
* �������ܣ�������ݽ�����
* �����������
* �����������
* �������أ���
* ʹ��˵���� 
******************************************************************************/
static void ClearRxBuffer(void)
{
	uint8_t i = 0;

	for(i=0;i<UsartRxData.RxLength;i++)
	{
		UsartRxData.RxBuffer[i]=0;
	}
	UsartRxData.RxLength = 0;

}

/****************************************************************************** 
* �������ƣ�UartBytePackageTx
* �������ܣ�����һ���ֽ�
* ����������ֽ�
* �����������
* �������أ���
* ʹ��˵���� 
******************************************************************************/
void UartBytePackageTx(char str)
{
    Uart_SendDataPoll(M0P_UART1,str);
}

