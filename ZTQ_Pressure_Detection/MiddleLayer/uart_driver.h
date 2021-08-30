/*
@--------------------------------------------------------------------------------------------------
@
@   File Name  :    uart_driver.h
@
@   Description:
@
@   Date       :
@--------------------------------------------------------------------------------------------------
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef	UART_DRIVE_H
#define UART_DRIVE_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stdint.h"

#define RXDATA_BUF_MAX		    100
#define TXDATA_BUF_MAX          50
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct _UsartRxData
{
	uint8_t RxBuffer[RXDATA_BUF_MAX];
	uint8_t RxLength;
	uint8_t UartRxCnt;
	uint8_t UartIntFlag;//串口中断标志位
};

extern struct _UsartRxData UsartRxData;

extern uint8_t    DataTxBuff[TXDATA_BUF_MAX];

extern void FUN_USART_SENDPACKET(uint8_t *RF_TRAN_P,uint8_t LEN);
extern void UartPackageTx(char *ptr);
extern void UartBytePackageTx(char str);
extern void TaskUart(void);
extern uint8_t CheckRevData(void);
//====================================================================================================
#endif
