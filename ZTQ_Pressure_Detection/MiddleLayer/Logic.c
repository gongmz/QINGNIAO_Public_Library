
/***************************************************************************************
****************************************************************************************
* FILE		: Logic.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/
#define  LOGIC_GLOBALS
/**********************************头文件**************************************/
#include "includes.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
EditData_t  EditData;
uint8_t WorkState; 
uint16_t gErrorBuf;
/**********************************函数声明************************************/
void  Logic(void);
void  SetLogicPrio(void);
void  WorkStateTran(uint8_t state);


void  Logic(void)
{
    uint8_t sig;

    if (Msg[LOGIC_PRIO - 1] & LOGIC_MENU_SHORT_PRESS) 
	{
        Msg[LOGIC_PRIO - 1] &= 0x7F;
        sig = LOGIC_MENU_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_MENU_LONG_PRESS) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xBF;
        sig = LOGIC_MENU_LONG_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_UP_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xDF;
        sig = LOGIC_UP_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_ENTER_MAIN) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xEF;
        sig = LOGIC_ENTER_MAIN;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_DOWN_SHORT_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xF7;
        sig = LOGIC_DOWN_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_CALCULATE_ADC)
	{
        Msg[LOGIC_PRIO - 1] &= 0xFB;
        sig = LOGIC_CALCULATE_ADC;
    } 
	else if (Msg[LOGIC_PRIO - 1] & LOGIC_ENTER_SHORT_PRESS) 
    {
        Msg[LOGIC_PRIO - 1] &= 0xFD;
        sig = LOGIC_ENTER_SHORT_PRESS;
    } 
	else if (Msg[LOGIC_PRIO - 1] & 	LOGIC_ENTER_LONG_PRESS)
	{
        Msg[LOGIC_PRIO - 1] &= 0xFE;
        sig = LOGIC_ENTER_LONG_PRESS;
    } 	
	else
    {
        sig = Msg[LOGIC_PRIO - 1];
        Msg[LOGIC_PRIO - 1] = 0;
    }

    switch (WorkState) 
		{
			case MODE_NORMAL_ST:
                switch (sig) 
				{
					case LOGIC_MENU_SHORT_PRESS:
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
					}break;
                       
					case LOGIC_MENU_LONG_PRESS:
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
								MsgPost(LOGIC_PRIO, LOGIC_ENTER_MAIN);
							}break;
						}
					}break;
                                               
					case LOGIC_UP_SHORT_PRESS:
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
					}break;
                       
					case LOGIC_DOWN_SHORT_PRESS:
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
					}break;
                                               
					
					case LOGIC_ENTER_SHORT_PRESS:
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
					}break;  

					case LOGIC_ENTER_LONG_PRESS:
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
					}break;  
 					case LOGIC_ENTER_MAIN:
					{
							Stop2_Sec_Timer();
							if(gGui_State!=GUI_MAIN)
							{
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
								gGui_State = GUI_MAIN;
								g_edit_area = 0;
								gGui_2nd_Num =1;
								Flash_Write(flashInformationAddress,(uint8_t *)&SysParameter,sizeof(SysParameter));
							}
					}break;  
					
					
 					case LOGIC_CALCULATE_ADC:
					{
						 AdcCalculate(&PressureValue);
						 g_bar_tube_num=DigitalCalculate(&PressureValue);
					}break;  
					default:
                        WorkStateTran(MODE_NORMAL_ST);break;
                }break;

            //--------------------------------------------------------------------------------------------------------------------

            //----------------------------------------------------------------------------------

            //----------------------------------------------------------------------------------
            default:
                WorkStateTran(MODE_NORMAL_ST);break;
        }

        SetLogicPrio();
}

void  SetLogicPrio(void)
{
    if (Msg[LOGIC_PRIO - 1] != 0)
		{
        OS_ENTER_CRITICAL();
        ThreadSet(LOGIC_PRIO);
        OS_EXIT_CRITICAL();
    }
}

void  WorkStateTran(uint8_t state)
{
    WorkState = state;
/*    MsgPost(LOGIC_PRIO, LOGIC_ENTRY_MSG);*/
}

