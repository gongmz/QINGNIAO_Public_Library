/**********************************头文件**************************************/
#include   "LCDDriver.h"
/**********************************宏定义声明**********************************/
#define LEDFLASHPERIOD  10   
#define DIGITALFLASHPERIOD   40
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/

volatile uint8_t gGui_State=GUI_MAIN;     
volatile uint8_t gGui_2nd_Num = 1;
volatile uint8_t gGui_3rd_Num = 1;

static uint8_t SegSelect;//数码管刷新区域
uint8_t g_edit_area;//数码管当前编辑区域   1：个位

static uint8_t table[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
static uint8_t table2[9] ={0x00,0x01,0x03,0x07,0xF,0x1F,0x3F,0x7F,0xFF};
/**********************************函数声明************************************/
void ClrAllLcd(void);
void DisplayMainInterface(void);
void Display2NDInterface(void);
void Display3NDInterface(void);
void Display_SubpageOfH1(void);
void Display_SubpageOfH2(void);
void Display_SubpageOfH3(void);
void Display_SubpageOfH4(void);
void Display_SubpageOfH5(void);
void Display_SubpageOfH6(void);
uint16_t HEX2BCD(uint16_t hex_data);// HEX转BCD子程序 
uint16_t BCD2HEX(uint16_t bcd_data); //BCD转为HEX子程序 


void Screen(void)
{
	ClrAllLcd();

    switch (gGui_State) 
	{
		case GUI_MAIN://主界面
			DisplayMainInterface();
		break;
		
		case GUI_2ND://二级界面
			Display2NDInterface();

		break;
		
		case GUI_3RD://三级界面
            switch(gGui_2nd_Num)
            {
                case 1:
                {
                    Display_SubpageOfH1();   
                }break;
                case 2:
                {
                    Display_SubpageOfH2();
                }break;
                case 3:
                {
                    Display_SubpageOfH3();
                }break;
 
                case 4:
                {
                    Display_SubpageOfH4();
                }break;
                case 5:
                {
                    Display_SubpageOfH5();   
                }break;
                case 6:
                {
                    Display_SubpageOfH6();
                }break;
				      
                default: break;
			}
		break;
		
		default:break;
	}
}
//******************************************************************************
//主界面显示
//******************************************************************************
void DisplayMainInterface(void)
{
	static uint16_t LEDFlashCnt;
	if(PressureValue>9999)PressureValue=9999;
    switch (SegSelect) 
	{
		case 0://
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			if(PressureValue>=SysParameter.OverPreaaureAlarm) //超压报警
			{
				SET_LED3;
			}
			else 
			{
				RESET_LED3;
			}
		
			if(PressureValue<=SysParameter.UnderPreaaureAlarm ) //欠压报警
			{
				SET_LED4;
			}
			else
			{
				RESET_LED4;
			}
			
	
			SPI_Send_Data(0);//条形码
			
			if( PressureValue > 999)
				SPI_Send_Data(table[PressureValue/1000]);
			else
				SPI_Send_Data(0);//不显示
			
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			if(PressureValue>=SysParameter.OverPreaaureWarn&&PressureValue<SysParameter.OverPreaaureAlarm) //超压预警
			{
				SET_LED3;
			}
			else
			{
				RESET_LED3;
			}
			
			if(PressureValue>SysParameter.UnderPreaaureAlarm&&PressureValue<=SysParameter.UnderPreaaureWarn) //欠压预警
			{
				SET_LED4;
			}
			else
			{
				RESET_LED4;
			}
		

			SPI_Send_Data(table2[0]);

			
		
			if( PressureValue > 99 )
				SPI_Send_Data(table[(PressureValue/100)%10]|0x80);
			else
				SPI_Send_Data(table[0]|0x80);//显示0
				
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			LEDFlashCnt++;
		    if(LEDFlashCnt>=LEDFLASHPERIOD*2)LEDFlashCnt=0;
			if(LEDFlashCnt<LEDFLASHPERIOD)
			{
				SET_LED4;
			}
			else
			{
				RESET_LED4;
			}
			//条形数码管
		    if(PressureValue<144)
				SPI_Send_Data(table2[PressureValue/16]);
			else if(PressureValue>=144&&PressureValue<160)
			{
				SPI_Send_Data(table2[8]);
			    SET_LED1;
			}
			else
			{
				SPI_Send_Data(table2[8]);
			    SET_LED1;
				SET_LED2;
			}
			//数字数码管
			if( PressureValue >9 )
				SPI_Send_Data(table[(PressureValue/10)%10]);
			else
				SPI_Send_Data(table[0]);//显示0
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[PressureValue%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//二级界面
//******************************************************************************
void Display2NDInterface(void)
{
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			
			SPI_Send_Data(0);
		

		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			SPI_Send_Data(0);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(CHAR_H);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[gGui_2nd_Num]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//清屏
//******************************************************************************
void   ClrAllLcd(void)
{
    SPI_Send_Data(0);
	SPI_Send_Data(0);
	RESET_LED1;
	RESET_LED2;
	RESET_LED3;
	RESET_LED4;
}
//******************************************************************************
//H1界面
//******************************************************************************
void Display_SubpageOfH1(void)
{ 
	static uint8_t DigitalFlashCnt;
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			if(g_edit_area == 3)
			{
				DigitalFlashCnt++;
				if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
				if(DigitalFlashCnt<DIGITALFLASHPERIOD)
				{
					SPI_Send_Data(table[EditData.thousand]);
				}
				else
				{
					SPI_Send_Data(0);
				}
		    }else
			{
				if( SysParameter.Range > 999)
					SPI_Send_Data(table[SysParameter.Range/1000]);
				else
					SPI_Send_Data(table[0]);//不显示
			}
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			if(g_edit_area == 2)
			{
				DigitalFlashCnt++;
				if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
				if(DigitalFlashCnt<DIGITALFLASHPERIOD)
				{
					SPI_Send_Data(table[EditData.hundred]);
				}
				else
				{
					SPI_Send_Data(0x80);
				}
		    }else
			{
				if( SysParameter.Range > 99 )
					SPI_Send_Data(table[(SysParameter.Range/100)%10]|0x80);
				else
					SPI_Send_Data(table[0]|0x80);//显示0
			}
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			if(g_edit_area == 1)
			{
				DigitalFlashCnt++;
				if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
				if(DigitalFlashCnt<DIGITALFLASHPERIOD)
				{
					SPI_Send_Data(table[EditData.decade]);
				}
				else
				{
					SPI_Send_Data(0);
				}
		    }else
			{
				if( SysParameter.Range >9 )
					SPI_Send_Data(table[(SysParameter.Range/10)%10]);
				else
					SPI_Send_Data(table[0]);//显示0
			}
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
		
			if(g_edit_area == 0)
			{
				DigitalFlashCnt++;
				if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
				if(DigitalFlashCnt<DIGITALFLASHPERIOD)
				{
					SPI_Send_Data(table[EditData.uint]);
				}
				else
				{
					SPI_Send_Data(0);
				}
			}
			else
				SPI_Send_Data(table[SysParameter.Range%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
    
}
//******************************************************************************
//H2界面
//******************************************************************************
void Display_SubpageOfH2(void)
{   
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.OverPreaaureWarn > 999)
				SPI_Send_Data(table[SysParameter.OverPreaaureWarn/1000]);
			else
				SPI_Send_Data(table[0]);
			
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.OverPreaaureWarn > 99 )
				SPI_Send_Data(table[(SysParameter.OverPreaaureWarn/100)%10]|0x80);
			else
				SPI_Send_Data(table[0]|0x80);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			if( SysParameter.OverPreaaureWarn >9 )
				SPI_Send_Data(table[(SysParameter.OverPreaaureWarn/10)%10]);
			else
				SPI_Send_Data(table[0]);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[SysParameter.OverPreaaureWarn%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//*******************************************************************************
//H3界面
//******************************************************************************
void Display_SubpageOfH3(void)
{
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.OverPreaaureAlarm > 999)
				SPI_Send_Data(table[SysParameter.OverPreaaureAlarm/1000]);
			else
				SPI_Send_Data(table[0]);
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.OverPreaaureAlarm > 99 )
				SPI_Send_Data(table[(SysParameter.OverPreaaureAlarm/100)%10]|0x80);
			else
				SPI_Send_Data(table[0]|0x80);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.OverPreaaureAlarm >9 )
				SPI_Send_Data(table[(SysParameter.OverPreaaureAlarm/10)%10]);
			else
				SPI_Send_Data(table[0]);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[SysParameter.OverPreaaureAlarm%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//*******************************************************************************
//H4界面
//******************************************************************************
void Display_SubpageOfH4(void)
{
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureAlarm > 999)
				SPI_Send_Data(table[SysParameter.UnderPreaaureAlarm/1000]);
			else
				SPI_Send_Data(table[0]);
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureWarn > 99 )
				SPI_Send_Data(table[(SysParameter.UnderPreaaureWarn/100)%10]|0x80);
			else
				SPI_Send_Data(table[0]|0x80);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureWarn >9 )
				SPI_Send_Data(table[(SysParameter.UnderPreaaureWarn/10)%10]);
			else
				SPI_Send_Data(table[0]);
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[SysParameter.UnderPreaaureWarn%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//H5界面
//******************************************************************************
void Display_SubpageOfH5(void)
{   
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureAlarm > 999)
				SPI_Send_Data(table[SysParameter.UnderPreaaureAlarm/1000]);
			else
				SPI_Send_Data(table[0]);
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureAlarm > 99 )
				SPI_Send_Data(table[(SysParameter.UnderPreaaureAlarm/100)%10]|0x80);
			else
				SPI_Send_Data(table[0]|0x80);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			if( SysParameter.UnderPreaaureAlarm >9 )
				SPI_Send_Data(table[(SysParameter.UnderPreaaureAlarm/10)%10]);
			else
				SPI_Send_Data(table[0]);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[SysParameter.UnderPreaaureAlarm%10]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//*******************************************************************************
//H6界面
//******************************************************************************
void Display_SubpageOfH6(void)
{
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(0);
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(0);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		    if(SysParameter.DetectionMode == VoltageDetection)
			    SPI_Send_Data(CHAR_U);
			else
				SPI_Send_Data(CHAR_A);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(0);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//*******************************************************************************
//H7界面
//******************************************************************************
void Display_SubpageOfH7(void)
{
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(0);
		

			
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
		
			SPI_Send_Data(0);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(CHAR_H);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(table[gGui_2nd_Num]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
void Display_CHECK_A(void)
{ 
}
uint16_t BCD2HEX(uint16_t bcd_data) //BCD转为HEX子程序 
{
    uint16_t result = 0;
    uint8_t i = 0 ;

    for(i=0;i<4;i++)
    {
		result *= 10;
		
        result += bcd_data>>12;

        bcd_data <<= 4;
    }

    return result;
}
uint16_t HEX2BCD(uint16_t hex_data)// HEX转BCD子程序 
{
    uint16_t bcd_data;
    uint16_t temp;
    temp=hex_data%100;
    bcd_data=((uint16_t)hex_data)/100<<8;
    bcd_data=bcd_data|temp/10<<4;
    bcd_data=bcd_data|temp%10;
    return bcd_data;
}
