
/**********************************头文件**************************************/
#include   "LCDDriver.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
volatile uint8_t gGui_State=GUI_MAIN;     
volatile uint8_t gGui_2nd_Num = 0;
volatile uint8_t gGui_3rd_Num = 1;
uint8_t i;
/**********************************函数声明************************************/
void ClrAllLcd(void);
void DisplayMainInterface(void);



static uint8_t table[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};



void Screen(void)
{
	ClrAllLcd();

    switch (gGui_State) 
	{
		case GUI_MAIN:
			DisplayMainInterface();
		break;
		
		case GUI_2ND:
			
		break;
		
		case GUI_3RD:
		break;
		
		default:break;
	}
}
//******************************************************************************
//显示主界面
//******************************************************************************
void DisplayMainInterface(void)
{
    switch (i) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0x3F);
			SPI_Send_Data(0x3F);
			
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0x06);
			SPI_Send_Data(0x06);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0x5B);
			SPI_Send_Data(0x5B);
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0x4F);
			SPI_Send_Data(0x4F);
		break;
		
		default:break;
	}
	i++;
	i=i%4;	
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
//H2二级界面
//******************************************************************************
void Display_SubpageOfH2(void)
{   

    
}
//*******************************************************************************
//H3二级界面
//******************************************************************************
void Display_SubpageOfH3(void)
{

}

void Display_SubpageOfH4(void)
{
 
}
//******************************************************************************
//屏幕显示月净历史数据查询
//******************************************************************************

void Display_CHECK_A(void)
{ 
}

