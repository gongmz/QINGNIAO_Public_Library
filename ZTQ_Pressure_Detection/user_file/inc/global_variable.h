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
/**********************************头文件**************************************/
#include "stdint.h"
#include "stdio.h"
#include "rtc.h"
/**********************************DEBUG开关**********************************/
// Log 打印
//#define Printf_Enable
/**********************************宏定义声明**********************************/
#define BUFFERSIZE  128

//设备基本信息
#define DEVICE_CPSN		    0
#define DEVICE_CLASS        0x3C  //无线气体压力传感器
#define DEVICE_TYPE	        0         
#define DEVICE_HV           0    //硬件版本号
#define DEVICE_SV		    0    //软件版本号
#define DEVICE_NET	    	1    //接受窗口类型，CLASS A：0   CLASS C:1


/*ZTQ-D2001 上传设备状态（DeviceState）标志位代码*/
#define DS_FAULT                0x02//故障状态
#define DS_OUTRANGE             0x04//超量程
#define DS_SENSOR_ERROR         0x08//传感器故障
#define DS_UNDER_PRESSURE       0x10//欠压报警
#define DS_ONLINE		        0x20//在线状态
#define DS_OVER_PRESSURE		0x40//过压报警
#define DS_RELAY_OUTPUT         0x80//继电器输出
#define DS_DETECTION_MODE       0x200//检测模式

/*上传事件标志位代码*/
#define FIREALARM_EVENT         0x03   //火警
#define FIREALARMCANCLE_EVENT   0x39   //火警取消

#define SEPARATEERR_EVENT       0x58   //分离故障
#define SEPARATECANCLE_EVENT    0x6C   //撤销分离故障

#define LOWVOLTAGE_EVENT        0x55   //欠压故障
#define NORMALVLITAGE_EVENT     0x69   //电压正常

#define SELFCHECK_EVENT         0x7B   //自检事件

/*模组传过来的消息类型   +NSSTATE  MSG*/
#define NET_MSG_NULL            0  // 空消息
#define NET_MSG_ALIVE_NAK       1  // Unconfirm 心跳 
#define NET_MSG_ALIVE           2  // Confirm 心跳 
#define NET_MSG_VERBOSE         3  // 长心跳 
#define NET_MSG_EVENT_RES_NAK   4  // 非应答事件
#define NET_MSG_EVENT           5  // 事件
#define NET_MSG_JOIN            6  // 入网
#define NET_MSG_JOIN_ACCEPT_ACK 7  // 入网确认 

/**********************************帧固定字符定义******************************/
/**********************************结构体声明**********************************/
typedef enum
{
    VoltageDetection,   //电压检测
    CurrentDetection    //电流检测
}Type_t;

//系统参数
typedef struct 
{
	uint8_t  FrameHead;
    uint16_t Range;  					//量程
    uint16_t OverPreaaureWarn;			//超压预警
    uint16_t OverPreaaureAlarm;         //超压报警
    uint16_t UnderPreaaureWarn;         //欠压预警
    uint16_t UnderPreaaureAlarm;        //欠压报警
    Type_t  DetectionMode;				//电压检测或电流检测
	uint8_t  FrameEnd;				    
}SysParameter_t;

extern SysParameter_t  SysParameter;
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
//无线开关
#define RF_EN_PORT   GpioPortA
#define RF_EN_PIN    GpioPin15
//电压电流检测切换开关
#define SETI_PORT   GpioPortD
#define SETI_PIN    GpioPin6
//24V电源供电
#define SENSOR_EN_PORT   GpioPortD
#define SENSOR_EN_PIN    GpioPin7
//24V电源供电
#define SETKEY_PORT   GpioPortB//控制开关量的检测
#define SETKEY_PIN    GpioPin2
/**********************************变量声明************************************/
extern uint16_t ErrorCode;
extern uint16_t PressureValue;
extern uint16_t DeviceState;
extern uint8_t DeviceEvent;
#endif
