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
//FIRE  
#define DIO1_PORT  GpioPortB
#define DIO1_PIN   GpioPin3

//按键
#define MENU_PORT   GpioPortB
#define MENU_PIN    GpioPin4
#define UP_PORT     GpioPortB
#define UP_PIN      GpioPin5
#define DOWN_PORT   GpioPortB
#define DOWN_PIN    GpioPin6
#define ENTER_PORT  GpioPortB
#define ENTER_PIN   GpioPin7
//LED引脚
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
/**********************************变量声明************************************/

extern uint16_t ErrorCode;
#endif
