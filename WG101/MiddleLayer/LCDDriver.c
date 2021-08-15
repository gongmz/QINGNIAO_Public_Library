/**********************************头文件**************************************/
#include   "LCDDriver.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/

volatile uint8_t gGui_State=GUI_MAIN;     
volatile uint8_t gGui_2nd_Num = 0;
volatile uint8_t gGui_3rd_Num = 1;
uint8_t i;

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
	  if(PressureValue>9999)PressureValue=9999;
    switch (i) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
	
		
		  if(PressureValue<180)
				SPI_Send_Data(table2[PressureValue/20]);
			else if(PressureValue>=180&&PressureValue<200)
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
		
		
		  if(PressureValue<180)
				SPI_Send_Data(table2[PressureValue/20]);
			else if(PressureValue>=180&&PressureValue<200)
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
		
		
		  if(PressureValue<180)
				SPI_Send_Data(table2[PressureValue/20]);
			else if(PressureValue>=180&&PressureValue<200)
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
	
		
		  if(PressureValue<180)
				SPI_Send_Data(table2[PressureValue/20]);
			else if(PressureValue>=180&&PressureValue<200)
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
			
			
			SPI_Send_Data(table[PressureValue%10]);
		break;
		
		default:break;
	}
	i++;
	i=i%4;	
}
//******************************************************************************
//二级界面
//******************************************************************************
void Display2NDInterface(void)
{
    switch (i) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
//		    DispNumLcd1(CHAR_H);
 //           DispNumLcd2(gGui_2nd_Num);  
			
		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0x06);
		
			SPI_Send_Data(0x06|0x80);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(gGui_2nd_Num);
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			SPI_Send_Data(0);
			SPI_Send_Data(CHAR_H);
		break;
		
		default:break;
	}
	i++;
	i=i%4;	
}
//******************************************************************************
//����
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
//H2��������
//******************************************************************************
void Display_SubpageOfH1(void)
{   

    
}
//******************************************************************************
//H2��������
//******************************************************************************
void Display_SubpageOfH2(void)
{   

    
}
//*******************************************************************************
//H3��������
//******************************************************************************
void Display_SubpageOfH3(void)
{

}
//*******************************************************************************
//H4��������
//******************************************************************************
void Display_SubpageOfH4(void)
{
 
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
