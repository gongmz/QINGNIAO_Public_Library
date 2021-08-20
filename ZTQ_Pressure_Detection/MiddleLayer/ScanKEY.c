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
			switch(gGui_State)
			{
				case GUI_MAIN:
				{
					gGui_State = GUI_2ND;
					gGui_2nd_Num = 1;
				}break;
				
				case GUI_2ND:
				case GUI_3RD:  
				gGui_State = GUI_MAIN;
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
        }
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//短按
		{
			Start2_120Sec();
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
					gGui_2nd_Num++;
				    if(gGui_2nd_Num>6)gGui_2nd_Num=1;
				
				case GUI_3RD: 
					g_edit_area++;
				    if(g_edit_area>3)g_edit_area=0;	
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
		}
		menukeycnt=0;
	}
	
	
	//up按键
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//按下
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CYCLE_2000MS)//长按
        {
			;
        }
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//短按
		{
			Start2_120Sec();

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
			Start2_120Sec();
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
				break;
				
				case GUI_3RD: 
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
		}
		downkeycnt=0;
	}
	
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CYCLE_2000MS)//长按
        {
			;
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//短按
		{
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
					gGui_State=GUI_3RD;
					temp_2ND_NUM=gGui_2nd_Num;
					g_edit_area=0;	
				break;
				
				case GUI_3RD:  
					gGui_State=GUI_2ND;
					gGui_2nd_Num=temp_2ND_NUM;
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}	
		}
		enterkeycnt=0;
	}
}
