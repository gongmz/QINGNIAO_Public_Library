/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
//#include "rtc_app.h"
//#include "time_app.h"
//#include "save.h"
//#include "global_variable.h"
//#include "CJT188.h"
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
	SysParameterInit();
	
	Init_LED();
#ifdef Printf_Enable
	LPuart1_Init();
	printf("System Start..................\r\n");
#endif
	delay1ms(2000);

//	  RTC_InitInterface();
//    parameter_init();
//    Wdt_Interface_Init();
//	Timer3Init();
     while(1)
	 {
		ThreadScheduler();
	 }

	
}

