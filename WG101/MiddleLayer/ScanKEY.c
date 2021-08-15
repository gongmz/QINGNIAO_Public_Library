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
	//menu����
	if(FALSE == Gpio_GetInputIO(MENU_PORT, MENU_PIN))//����
	{
		if(++menukeycnt>240)menukeycnt=240;
		if(menukeycnt == TIME_CYCLE_2000MS)//����
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long1 an..................\r\n");
        }
				PressureValue++;
	}
	else
	{
		if( menukeycnt>2 && menukeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
			printf("short1 an..................\r\n");
			PressureValue++;
			printf("PressureValue:%d\r\n",PressureValue);
		}
		menukeycnt=0;
	}
	
	
	//up����
	if(FALSE == Gpio_GetInputIO(UP_PORT, UP_PIN))//����
	{
		if(++upkeycnt>240)upkeycnt=240;
		if(upkeycnt == TIME_CYCLE_2000MS)//����
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long2 an..................\r\n");
        }
	}
	else
	{
		if( upkeycnt > 2 && upkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("short2 an..................\r\n");			
		}
		upkeycnt=0;
	}
	
	
	//down����
	if(FALSE == Gpio_GetInputIO(DOWN_PORT, DOWN_PIN))//����
	{
		if(++downkeycnt>240)downkeycnt=240;
		if(downkeycnt == TIME_CYCLE_2000MS)//����
        {
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
			printf("long3 an..................\r\n");
        }

	}
	else
	{
		if( downkeycnt > 2 && downkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);	
			printf("short3 an..................\r\n");			
		}
		downkeycnt=0;
	}
	
	
	//enter����
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//����
	{
		if(++enterkeycnt>240)enterkeycnt=240;
		if(enterkeycnt == TIME_CYCLE_2000MS)//����
        {
			printf("long4 an..................\r\n");
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);
        }
        
	}
	else
	{
		if(enterkeycnt > 2 && enterkeycnt<TIME_CYCLE_2000MS )//�̰�
		{
			printf("short4 an..................\r\n");
//			MsgPost(COMM_PRIO,COMM_ADDR_QUIT);		
		}
		enterkeycnt=0;
	}
}
