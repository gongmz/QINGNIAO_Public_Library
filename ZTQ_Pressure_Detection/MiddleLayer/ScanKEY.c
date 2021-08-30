/**********************************头文件**************************************/
#include "includes.h"
/**********************************宏定义声明**********************************/
#define TIME_CNT_LONG_PRESS         	2000
#define TIME_CNT_SHORT_PRESS         	20
//#define TIME_CYCLE_3000MS         	300
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
static uint16_t menukeycnt=0;
static uint16_t upkeycnt=0;
static uint16_t downkeycnt=0;
static uint16_t enterkeycnt=0;

uint16_t temp;
/**********************************函数声明************************************/
void TaskKey(void)//1ms调用一次
{
	//menu按键
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//按下
	{
		if(++menukeycnt>TIME_CNT_LONG_PRESS)menukeycnt=TIME_CNT_LONG_PRESS+1;
		if(menukeycnt == TIME_CNT_LONG_PRESS)//长按
        {
			MsgPost(LOGIC_PRIO, LOGIC_MENU_LONG_PRESS);
        }
	}
	else
	{
		if( menukeycnt>TIME_CNT_SHORT_PRESS && menukeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			MsgPost(LOGIC_PRIO, LOGIC_MENU_SHORT_PRESS);
		}
		menukeycnt=0;
	}
	
	
	//up按键
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//按下
	{
		if(++upkeycnt>TIME_CNT_LONG_PRESS)upkeycnt=TIME_CNT_LONG_PRESS+1;
		if(upkeycnt == TIME_CNT_LONG_PRESS)//长按
        {
			__NOP();
        }
	}
	else
	{
		if( upkeycnt > TIME_CNT_SHORT_PRESS && upkeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			MsgPost(LOGIC_PRIO, LOGIC_UP_SHORT_PRESS);
		}
		upkeycnt=0;
	}
	
	
	//down按键
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//按下
	{
		if(++downkeycnt>TIME_CNT_LONG_PRESS)downkeycnt=TIME_CNT_LONG_PRESS+1;
		if(downkeycnt == TIME_CNT_LONG_PRESS)//长按
        {
			__NOP();
        }

	}
	else
	{
		if( downkeycnt > TIME_CNT_SHORT_PRESS && downkeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			MsgPost(LOGIC_PRIO, LOGIC_DOWN_SHORT_PRESS);
		}
		downkeycnt=0;
	}
	
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(++enterkeycnt>TIME_CNT_LONG_PRESS)enterkeycnt=TIME_CNT_LONG_PRESS+1;
		if(enterkeycnt == TIME_CNT_LONG_PRESS)//长按
        {
			MsgPost(LOGIC_PRIO, LOGIC_ENTER_LONG_PRESS);
        }
        
	}
	else
	{
		if(enterkeycnt > TIME_CNT_SHORT_PRESS && enterkeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			MsgPost(LOGIC_PRIO, LOGIC_ENTER_SHORT_PRESS);
		}
		enterkeycnt=0;
	}
}
