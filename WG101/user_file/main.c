/**********************************头文件**************************************/
#include "stdint.h"
#include "init.h"
#include "RTCFun.h"
#include "FrameWork.h"
//#include "rtc_app.h"
//#include "time_app.h"
//#include "save.h"
//#include "global_variable.h"
//#include "CJT188.h"
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
#ifdef Printf_Enable
	LPuart1_Init();
	printf("System Start..................\r\n");
#endif
	delay1ms(2000);

	
			Spi_SetCS(M0P_SPI0, FALSE);
			Spi_SendData(M0P_SPI0, 0);
			Spi_SendData(M0P_SPI0, 0);
			Spi_SetCS(M0P_SPI0, TRUE);
//	  RTC_InitInterface();
//    parameter_init();
//    Wdt_Interface_Init();
//	Timer3Init();
     while(1)
	 {
		ThreadScheduler();
	 }

	
}

