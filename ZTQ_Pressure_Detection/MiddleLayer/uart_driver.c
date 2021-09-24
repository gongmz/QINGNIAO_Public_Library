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
struct _UsartRxData UsartRxData;//接收数据缓冲区
static void ClearRxBuffer(void);

/****************************************************************************** 
* 函数名称：TaskUart()
* 函数功能：串口任务
* 输入参数：无
* 输出参数：无
* 函数返回：无
* 使用说明：
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
							if(para1 == NET_MSG_EVENT)//发送事件
							{
								if(para == 2)//发送成功
									MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_OK);
								else if(para == 3)//发送错误
									MsgPost(LORAFUN_PRIO,LORA_MSG_SEND_ERROR);
							}
#ifdef	UPLOAD_ANALOG
							else if(para1 == NET_MSG_ALIVE)//发送confim包，需要携带模拟量，温感无上传模拟量需求，故屏蔽
							{
								temp_event.event = 0;
								temp_event.state = DeviceState;

								if(EnQueue(&FireQueue,temp_event))//将事件插入队列
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
* 函数名称：StartUartPackageTx
* 函数功能：开始串口发送数据（中断方式）
* 输入参数：
* 输出参数：无
* 函数返回：无
* 使用说明： 
******************************************************************************/
void StartUartPackageTx(void)
{
    M0P_UART1->SBUF = (1<<8)|SLAVEADDR;//发送地址触发中断
    Uart_EnableIrq(M0P_UART1,UartTxIrq);             ///<使能串口发送中断
}


/****************************************************************************** 
* 函数名称：ClearRxBuffer
* 函数功能：清空数据接收区
* 输入参数：无
* 输出参数：无
* 函数返回：无
* 使用说明： 
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
* 函数名称：UartBytePackageTx
* 函数功能：发送一个字节
* 输入参数：字节
* 输出参数：无
* 函数返回：无
* 使用说明： 
******************************************************************************/
void UartBytePackageTx(char str)
{
    Uart_SendDataPoll(M0P_UART1,str);
}

