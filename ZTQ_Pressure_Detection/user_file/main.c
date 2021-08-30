/**********************************头文件**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
#include "ADCDriver.h"
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
/**********************************函数声明************************************/
int32_t main(void)
{
	SysClockInit();
    GPIO_Init();
	KEY_Init();
	SPI_Init();
	LPTimerInit();
    Timer3Init();
	Uart1_Init();
	Init_LED();
	ParaInit();
	AdcInit();
#ifdef Printf_Enable
	LPuart1_Init();
	printf("System Start..................\r\n");
#endif
	delay1ms(500);
	
	Start1_1Sec();//ADC检测
	Start6_1Sec();//LoRa转到上电状态
	Start_min_timer();//
	Start0_60min();//周期发送模拟量
	
	while(1)
	{
		ThreadScheduler();
	}
}

