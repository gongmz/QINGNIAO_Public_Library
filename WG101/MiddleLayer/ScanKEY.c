/**********************************头文件**************************************/
#include "includes.h"
/**********************************宏定义声明**********************************/
#define TIME_CYCLE_1000MS         	100
#define TIME_CYCLE_2000MS         	200
//#define TIME_CYCLE_3000MS         	300
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
static uint8_t menukeycnt=0;
static uint8_t upkeycnt=0;
static uint8_t downkeycnt=0;
static uint8_t enterkeycnt=0;


/**********************************函数声明************************************/
void TaskKey(void)//10ms调用一次
{
	//menu按键
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//按下
	{
		if(++menukeycnt>240)menukeycnt=240;
		if(menukeycnt == TIME_CYCLE_2000MS)//长按
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long1 an..................\r\n");
			
												

        }
			
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
			printf("short1 an..................\r\n");
		}
		menukeycnt=0;
	}
	
	
	//up按键
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//按下
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CYCLE_2000MS)//长按
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long2 an..................\r\n");
        }
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("short2 an..................\r\n");			
		}
		upkeycnt=0;
	}
	
	
	//down按键
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//按下
	{
		if(++downkeycnt>240)downkeycnt=240;
		if(downkeycnt == TIME_CYCLE_2000MS)//长按
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long3 an..................\r\n");
        }

	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);	
			printf("short3 an..................\r\n");			
		}
		downkeycnt=0;
	}
	
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CYCLE_2000MS)//长按
        {
			printf("long4 an..................\r\n");
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//短按
		{
			printf("short4 an..................\r\n");
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		enterkeycnt=0;
	}
}
