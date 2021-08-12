/**********************************头文件**************************************/
#include "includes.h"
/**********************************宏定义声明**********************************/
#define TIME_CYCLE_1000MS         	32
#define TIME_CYCLE_2000MS         	64
#define TIME_CYCLE_3000MS         	96
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
		if(menukeycnt > TIME_CYCLE_3000MS)//长按
        {
			menukeycnt =0;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
		else
			menukeycnt ++;
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		menukeycnt=0;
	}
	
	//up按键
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//按下
	{
		if(upkeycnt > TIME_CYCLE_3000MS)//长按
        {
            upkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        upkeycnt ++;
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		upkeycnt=0;
	}
	
	//down按键
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//按下
	{
		if(downkeycnt > TIME_CYCLE_3000MS)//长按
        {
            downkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        downkeycnt ++;
	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		downkeycnt=0;
	}
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(enterkeycnt > TIME_CYCLE_3000MS)//长按
        {
            enterkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        enterkeycnt ++;
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//短按
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		enterkeycnt=0;
	}
}
