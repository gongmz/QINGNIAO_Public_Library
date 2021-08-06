#ifndef _global_variable_h
#define _global_variable_h
/**********************************头文件**************************************/
#include "stdint.h"
#include "stdio.h"
#include "rtc.h"
/**********************************DEBUG开关**********************************/
// Log 打印
#define Printf_Enable
/**********************************宏定义声明**********************************/
#define BUFFERSIZE  128
/**********************************帧固定字符定义******************************/
#define CJ188_START_CODE      0x68    //帧起始符
#define CJ188_END_CODE        0x16    //幀结束符
#define CJ188_SERIAL_NO       0x00    //序列号
#define CJ188_DEVICE_TYPE     0x10    //水表
/**********************************结构体声明**********************************/
struct _uart
{
	uint8_t Buffer[BUFFERSIZE];
	uint16_t TimeCounter;//定时器定时时间*TimeCounter未收到数据判定为一帧
	uint16_t Length;//数据帧长度
	uint8_t RxFlag;	//主程序中是否进行数据处理的标志位
	uint8_t RxProcess;//表征此串口正在接收数据
};
/**********************************引脚宏定义**********************************/
#define DIO1_PORT  GpioPortB
#define DIO1_PIN   GpioPin6
/**********************************变量声明************************************/

extern uint16_t ErrorCode;
#endif
