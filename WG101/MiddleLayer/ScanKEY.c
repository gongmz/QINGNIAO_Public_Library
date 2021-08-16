/**********************************ͷ�ļ�**************************************/
#include "includes.h"
/**********************************�궨������**********************************/
#define TIME_CYCLE_1000MS         	100
#define TIME_CYCLE_2000MS         	200
//#define TIME_CYCLE_3000MS         	300
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
static uint8_t menukeycnt=0;
static uint8_t upkeycnt=0;
static uint8_t downkeycnt=0;
static uint8_t enterkeycnt=0;

uint16_t temp;
/**********************************��������************************************/
void TaskKey(void)//10ms����һ��
{
	static uint8_t temp_2ND_NUM;
	//menu����
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//����
	{
		if(++menukeycnt>240)menukeycnt=240;
		if(menukeycnt == TIME_CYCLE_2000MS)//����
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
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//�̰�
		{
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
					gGui_2nd_Num++;
				    if(gGui_2nd_Num>6)gGui_2nd_Num=1;
				
				case GUI_3RD:  
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
		}
		menukeycnt=0;
	}
	
	
	//up����
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//����
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CYCLE_2000MS)//����
        {
			
        }
		PressureValue++;
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
			
		}
		upkeycnt=0;
	}
	
	
	//down����
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//����
	{
		if(++downkeycnt>240)downkeycnt=240;
		if(downkeycnt == TIME_CYCLE_2000MS)//����
        {
			PressureValue=0;
        }

	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
			
		}
		downkeycnt=0;
	}
	
	
	//enter����
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//����
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CYCLE_2000MS)//����
        {
			__NOP();
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
					gGui_State=GUI_3RD;
					temp_2ND_NUM=gGui_2nd_Num;
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
