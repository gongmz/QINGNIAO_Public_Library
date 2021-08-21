/**********************************ͷ�ļ�**************************************/
#include "includes.h"
/**********************************�궨������**********************************/
#define TIME_CYCLE_1000MS         	100
#define TIME_CNT_SHORT_PRESS         	200
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
	//menu����
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//����
	{
		if(++menukeycnt>240)menukeycnt=240;
		if(menukeycnt == TIME_CNT_SHORT_PRESS)//����
        {
			MsgPost(LOGIC_PRIO, LOGIC_MENU_LONG_PRESS);
        }
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CNT_SHORT_PRESS )//�̰�
		{
			MsgPost(LOGIC_PRIO, LOGIC_MENU_SHORT_PRESS);
		}
		menukeycnt=0;
	}
	
	
	//up����
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//����
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CNT_SHORT_PRESS)//����
        {
			__NOP();
        }
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CNT_SHORT_PRESS )//�̰�
		{
			MsgPost(LOGIC_PRIO, LOGIC_UP_SHORT_PRESS);
		}
		upkeycnt=0;
	}
	
	
	//down����
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//����
	{
		if(++downkeycnt>240)downkeycnt=240;
		if(downkeycnt == TIME_CNT_SHORT_PRESS)//����
        {
			__NOP();
        }

	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CNT_SHORT_PRESS )//�̰�
		{
			MsgPost(LOGIC_PRIO, LOGIC_DOWN_SHORT_PRESS);
		}
		downkeycnt=0;
	}
	
	
	//enter����
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//����
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CNT_SHORT_PRESS)//����
        {
			__NOP();
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CNT_SHORT_PRESS )//�̰�
		{
			MsgPost(LOGIC_PRIO, LOGIC_ENTER_SHORT_PRESS);
		}
		enterkeycnt=0;
	}
}
