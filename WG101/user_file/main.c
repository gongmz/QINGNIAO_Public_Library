/**********************************ͷ�ļ�**************************************/
#include "stdint.h"
#include "init.h"
//#include "rtc_app.h"
//#include "time_app.h"
//#include "save.h"
//#include "global_variable.h"
//#include "CJT188.h"
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
	uint8_t flag;
/**********************************��������************************************/

int32_t main(void)
{


	  SysClockInit();
    delay1ms(2000);
    GPIO_Init();
		SPI_Init();
		LPTimerInit();
#ifdef Printf_Enable
     Uart0_Init();
	   printf("System Start..................\r\n");
#endif
//	RTC_InitInterface();
//    parameter_init();
//    Wdt_Interface_Init();
//	Timer3Init();
    while(1)
	{
		 if(flag)
		 {
			 flag=0;
			 printf("fuck..................\r\n");
		 }
	}

}

