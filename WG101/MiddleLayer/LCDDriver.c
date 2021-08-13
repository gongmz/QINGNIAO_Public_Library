
/**********************************ͷ�ļ�**************************************/
#include   "LCDDriver.h"
/**********************************�궨������**********************************/
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
volatile uint8_t gGui_State=GUI_MAIN;     
volatile uint8_t gGui_2nd_Num = 0;
volatile uint8_t gGui_3rd_Num = 1;
uint8_t i;

static uint8_t table[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
/**********************************��������************************************/
void ClrAllLcd(void);
void DisplayMainInterface(void);
void Display2NDInterface(void);
void Display3NDInterface(void);
void Display_SubpageOfH1(void);
void Display_SubpageOfH2(void);
void Display_SubpageOfH3(void);
void Display_SubpageOfH4(void);




void Screen(void)
{
	ClrAllLcd();

    switch (gGui_State) 
	{
		case GUI_MAIN://������
			DisplayMainInterface();
		break;
		
		case GUI_2ND://��������
			Display2NDInterface();

		break;
		
		case GUI_3RD://��������
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
//��ʾ������
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
		
			SPI_Send_Data(0x06|0x80);
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
//��ʾ�ڶ�����
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
//******************************************************************************
//��Ļ��ʾ�¾���ʷ���ݲ�ѯ
//******************************************************************************

void Display_CHECK_A(void)
{ 
}

