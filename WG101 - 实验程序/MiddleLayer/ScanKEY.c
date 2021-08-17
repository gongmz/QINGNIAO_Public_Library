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

uint16_t temp;
/**********************************函数声明************************************/
void TaskKey(void)//10ms调用一次
{
	static uint8_t temp_2ND_NUM;
	//menu按键
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//按下
	{
		if(++menukeycnt>240)menukeycnt=240;
		if(menukeycnt == TIME_CYCLE_2000MS)//长按
        {

        }
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//短按
		{
				if(!flag2)
					flag2=1;
				else
					flag2=0;
				
		}
		menukeycnt=0;
	}
	
	
	//up按键
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//按下
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CYCLE_2000MS)//长按
        {
			
        }
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//短按
		{
				if(!flag)
					flag=1;
				else
					flag=0;
		}
		upkeycnt=0;
	}
	
	
	//down按键
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//按下
	{
		if(++downkeycnt>240)downkeycnt=240;
		if(downkeycnt == TIME_CYCLE_2000MS)//长按
        {
			PressureValue=0;
        }

	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//短按
		{
				if(!flag)
					flag=1;
				else
					flag=0;
		}
		downkeycnt=0;
	}
	
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CYCLE_2000MS)//长按
        {
				if(!flag)
					flag=1;
				else
					flag=0;
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//短按
		{
				if(!flag)
					flag=1;
				else
					flag=0;
		}
		enterkeycnt=0;
	}
}
