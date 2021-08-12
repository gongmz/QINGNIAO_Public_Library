/**********************************ͷ�ļ�**************************************/
#include "includes.h"
/**********************************�궨������**********************************/
#define TIME_CYCLE_1000MS         	32
#define TIME_CYCLE_2000MS         	64
#define TIME_CYCLE_3000MS         	96
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
static uint8_t menukeycnt=0;
static uint8_t upkeycnt=0;
static uint8_t downkeycnt=0;
static uint8_t enterkeycnt=0;

/**********************************��������************************************/
void TaskKey(void)//10ms����һ��
{
	//menu����
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//����
	{
		if(menukeycnt > TIME_CYCLE_3000MS)//����
        {
			menukeycnt =0;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
		else
			menukeycnt ++;
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		menukeycnt=0;
	}
	
	//up����
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//����
	{
		if(upkeycnt > TIME_CYCLE_3000MS)//����
        {
            upkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        upkeycnt ++;
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		upkeycnt=0;
	}
	
	//down����
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//����
	{
		if(downkeycnt > TIME_CYCLE_3000MS)//����
        {
            downkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        downkeycnt ++;
	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		downkeycnt=0;
	}
	
	//enter����
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//����
	{
		if(enterkeycnt > TIME_CYCLE_3000MS)//����
        {
            enterkeycnt = TIME_CYCLE_3000MS;
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        enterkeycnt ++;
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		enterkeycnt=0;
	}
}
