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
			switch(gGui_State)
			{
				case GUI_MAIN:
				{
					Start2_120Sec();
					gGui_State = GUI_2ND;
					gGui_2nd_Num = 1;
					
					EditData.uint=SysParameter.Range%10;
					EditData.decade=(SysParameter.Range/10)%10;
					EditData.hundred=(SysParameter.Range/100)%10;
					EditData.thousand=(SysParameter.Range/1000)%10;
				}break;
				
				case GUI_2ND:
				case GUI_3RD:  
				default:
				{
					LcdReturnMain();
				}break;
			}
        }
	}
	else
	{
		if( menukeycnt>TIME_CNT_SHORT_PRESS && menukeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
					Start2_120Sec();
					gGui_2nd_Num++;
					if(gGui_2nd_Num>6)gGui_2nd_Num=1;
					switch(gGui_2nd_Num)
					{
						case 1:
							EditData.uint=SysParameter.Range%10;
							EditData.decade=(SysParameter.Range/10)%10;
							EditData.hundred=(SysParameter.Range/100)%10;
							EditData.thousand=(SysParameter.Range/1000)%10;
						
						break;	
						case 2:
							EditData.uint=SysParameter.OverPreaaureWarn%10;
							EditData.decade=(SysParameter.OverPreaaureWarn/10)%10;
							EditData.hundred=(SysParameter.OverPreaaureWarn/100)%10;
							EditData.thousand=(SysParameter.OverPreaaureWarn/1000)%10;
						break;	
						case 3:
							EditData.uint=SysParameter.OverPreaaureAlarm%10;
							EditData.decade=(SysParameter.OverPreaaureAlarm/10)%10;
							EditData.hundred=(SysParameter.OverPreaaureAlarm/100)%10;
							EditData.thousand=(SysParameter.OverPreaaureAlarm/1000)%10;
						break;	
						case 4:
							EditData.uint=SysParameter.UnderPreaaureWarn%10;
							EditData.decade=(SysParameter.UnderPreaaureWarn/10)%10;
							EditData.hundred=(SysParameter.UnderPreaaureWarn/100)%10;
							EditData.thousand=(SysParameter.UnderPreaaureWarn/1000)%10;
						break;	
						case 5:
							EditData.uint=SysParameter.UnderPreaaureAlarm%10;
							EditData.decade=(SysParameter.UnderPreaaureAlarm/10)%10;
							EditData.hundred=(SysParameter.UnderPreaaureAlarm/100)%10;
							EditData.thousand=(SysParameter.UnderPreaaureAlarm/1000)%10;
						break;		
						default:break;	
					}
				case GUI_3RD: 
					Start2_120Sec();
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
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
				break;
				
				case GUI_3RD: 
					Start2_120Sec();
					if(gGui_2nd_Num==6)
					{
						 if(SysParameter.DetectionMode == VoltageDetection)
							 SysParameter.DetectionMode = CurrentDetection;
						 else
							 SysParameter.DetectionMode = VoltageDetection;
					}
					else
					{
						switch(g_edit_area)
						{
							case 0:
								if(++EditData.uint>9)
									EditData.uint=0;
							break;
								
							case 1:
								if(++EditData.decade>9)
									EditData.decade=0;
							break;
								
							case 2:
								if(++EditData.hundred>9)
									EditData.hundred=0;
							break;
								
							case 3:
								if(++EditData.thousand>9)
									EditData.thousand=0;
							break;									
						}
					}
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
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
			switch(gGui_State)
			{
				case GUI_MAIN:
				break;
				
				case GUI_2ND:
				break;
				
				case GUI_3RD: 
					Start2_120Sec();
					if(gGui_2nd_Num==6)
					{
						 if(SysParameter.DetectionMode == VoltageDetection)
							 SysParameter.DetectionMode = CurrentDetection;
						 else
							 SysParameter.DetectionMode = VoltageDetection;
					}
					else
					{
						switch(g_edit_area)
						{
							case 0:
								if(EditData.uint)
									EditData.uint--;
								else
									EditData.uint=9;
							break;
								
							case 1:
								if(EditData.decade)
									EditData.decade--;
								else
									EditData.decade=9;
							break;
								
							case 2:
								if(EditData.hundred)
									EditData.hundred--;
								else
									EditData.hundred=9;
							break;
								
							case 3:
								if(EditData.thousand)
									EditData.thousand--;
								else
									EditData.thousand=9;
							break;									
						}
					}
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}
		}
		downkeycnt=0;
	}
	
	
	//enter按键
	if(FALSE == Gpio_GetInputIO(ENTER_PORT, ENTER_PIN))//按下
	{
		if(++enterkeycnt>TIME_CNT_LONG_PRESS)enterkeycnt=TIME_CNT_LONG_PRESS+1;
		if(enterkeycnt == TIME_CNT_LONG_PRESS)//长按
        {
			switch(gGui_State)
			{
				case GUI_MAIN:
					LoRaWorkStateTran(LORA_ST_SELFCHECK);
				break;
				
				case GUI_2ND:
				break;
				
				case GUI_3RD:  
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}	
        }
        
	}
	else
	{
		if(enterkeycnt > TIME_CNT_SHORT_PRESS && enterkeycnt<TIME_CNT_LONG_PRESS )//短按
		{
			switch(gGui_State)
			{
				case GUI_MAIN:
					EnterShortKeyNum++;
					Start7_2Sec();//2秒之内按3次，那么发送注册指令
				break;
				
				case GUI_2ND:
					Start2_120Sec();
					gGui_State=GUI_3RD;
					g_edit_area=0;	
				break;
				
				case GUI_3RD:  
					Start2_120Sec();
					gGui_State=GUI_2ND;
					switch(gGui_2nd_Num)
					{
						case 1:
							SysParameter.Range=1000*EditData.thousand+100*EditData.hundred+10*EditData.decade+EditData.uint;
						break;	
						case 2:
							SysParameter.OverPreaaureWarn=1000*EditData.thousand+100*EditData.hundred+10*EditData.decade+EditData.uint;
						break;	
						case 3:
							SysParameter.OverPreaaureAlarm=1000*EditData.thousand+100*EditData.hundred+10*EditData.decade+EditData.uint;
						break;	
						case 4:
							SysParameter.UnderPreaaureWarn=1000*EditData.thousand+100*EditData.hundred+10*EditData.decade+EditData.uint;
						break;	
						case 5:
							SysParameter.UnderPreaaureAlarm=1000*EditData.thousand+100*EditData.hundred+10*EditData.decade+EditData.uint;
						break;		
						default:break;	
					}
				break;
				
				default:{gGui_State = GUI_MAIN;}break;
			}	
		}
		enterkeycnt=0;
	}
}
