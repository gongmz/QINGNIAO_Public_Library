/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
#include  "ADCDriver.h"
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
/**********************************��������************************************/
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
	Start1_1Sec();//ADC���
     while(1)
	 {
		ThreadScheduler();
	 }
}

