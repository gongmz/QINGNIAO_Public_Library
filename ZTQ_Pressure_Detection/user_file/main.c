/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
#include "ADCDriver.h"
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
	Uart1_Init();
	Init_LED();
	ParaInit();
	AdcInit();
#ifdef Printf_Enable
	LPuart1_Init();
	printf("System Start..................\r\n");
#endif
	delay1ms(500);
	
	Start1_1Sec();//ADC���
	Start6_1Sec();//LoRaת���ϵ�״̬
	Start_min_timer();//
	Start0_60min();//���ڷ���ģ����
	
	while(1)
	{
		ThreadScheduler();
	}
}

