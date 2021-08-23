/**********************************头文件**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
#include  "ADCDriver.h"
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
	Init_LED();
	ParaInit();
	AdcInit();
#ifdef Printf_Enable
	LPuart1_Init();
	printf("System Start..................\r\n");
#endif
	delay1ms(1000);
	Start1_1Sec();//ADC检测
     while(1)
	 {
		ThreadScheduler();
	 }
}

