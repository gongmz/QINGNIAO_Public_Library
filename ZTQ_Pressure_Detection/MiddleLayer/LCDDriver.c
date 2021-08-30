/**********************************头文件**************************************/
#include   "LCDDriver.h"
/**********************************宏定义声明**********************************/
#define LEDFLASHPERIOD  50   
#define DIGITALFLASHPERIOD   40
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/

volatile uint8_t gGui_State=GUI_MAIN;     
volatile uint8_t gGui_2nd_Num = 1;
volatile uint8_t gGui_3rd_Num = 1;

static uint8_t SegSelect;//数码管刷新区域
uint8_t g_edit_area;//数码管当前编辑区域   1：个位
uint8_t g_bar_tube_num;//光柱数码管显示数目

static uint8_t table[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
static uint8_t table2[9] ={0x00,0x01,0x03,0x07,0xF,0x1F,0x3F,0x7F,0xFF};//光柱数码管显示条数
/**********************************函数声明************************************/
void ClrAllLcd(void);
void DisplayMainInterface(void);
void Display2NDInterface(void);
void Display3NDInterface(void);
void Display_SubpageOfHx(void);//H1~H5界面
void Display_SubpageOfH6(void);//H6界面
uint16_t HEX2BCD(uint16_t hex_data);// HEX转BCD子程序 
uint16_t BCD2HEX(uint16_t bcd_data); //BCD转为HEX子程序 


void Screen()
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
			if(gGui_2nd_Num==6)
				Display_SubpageOfH6();
			else
				Display_SubpageOfHx();
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
    switch (SegSelect) 
	{
		case 0://
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			if(PressureValue>=SysParameter.OverPreaaureAlarm) //超压报警
				SET_LED3;
			else
				RESET_LED3;
		
			if(PressureValue<=SysParameter.UnderPreaaureAlarm ) //欠压报警
				SET_LED4;
			else
				RESET_LED4;
			
			//光柱数码管
			if(g_bar_tube_num<20)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=20&&g_bar_tube_num<=28)
				SPI_Send_Data(table2[g_bar_tube_num-20]);
			else if(g_bar_tube_num==29)
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
		
			if(PressureValue>=SysParameter.OverPreaaureWarn&&PressureValue<SysParameter.OverPreaaureAlarm) //超压预警
				SET_LED3;
			else
				RESET_LED3;
			
			if(PressureValue>SysParameter.UnderPreaaureAlarm&&PressureValue<=SysParameter.UnderPreaaureWarn) //欠压预警
				SET_LED4;
			else
				RESET_LED4;
		
			//光柱数码管
			if(g_bar_tube_num<10)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=10&&g_bar_tube_num<=18)
				SPI_Send_Data(table2[g_bar_tube_num-10]);
			else if(g_bar_tube_num==19)
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
		
			LEDFlashCnt++;
		    if(LEDFlashCnt>=LEDFLASHPERIOD*2)LEDFlashCnt=0;
			if(LEDFlashCnt<LEDFLASHPERIOD)
				SET_LED4;
			else
				RESET_LED4;
			
			//光柱数码管
			if(g_bar_tube_num<8)
				SPI_Send_Data(table2[g_bar_tube_num]);
			else if(g_bar_tube_num==9)
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

			//光柱数码管
			if(g_bar_tube_num<30)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=30&&g_bar_tube_num<=38)
				SPI_Send_Data(table2[g_bar_tube_num-30]);
			else if(g_bar_tube_num==39)
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
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//二级界面
//******************************************************************************
void Display2NDInterface(void)
{
	static uint16_t LEDFlashCnt;
    switch (SegSelect) 
	{
		case 0:
			SET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			if(PressureValue>=SysParameter.OverPreaaureAlarm) //超压报警
				SET_LED3;
			else
				RESET_LED3;
		
			if(PressureValue<=SysParameter.UnderPreaaureAlarm ) //欠压报警
				SET_LED4;
			else
				RESET_LED4;
			
			//光柱数码管
			if(g_bar_tube_num<20)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=20&&g_bar_tube_num<=28)
				SPI_Send_Data(table2[g_bar_tube_num-20]);
			else if(g_bar_tube_num==29)
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
			
			SPI_Send_Data(0);
		

		break;
		
		case 1:
			RESET_SEG1;
			SET_SEG2;
			RESET_SEG3;
			RESET_SEG4;
		
			if(PressureValue>=SysParameter.OverPreaaureWarn&&PressureValue<SysParameter.OverPreaaureAlarm) //超压预警
				SET_LED3;
			else
				RESET_LED3;
			
			if(PressureValue>SysParameter.UnderPreaaureAlarm&&PressureValue<=SysParameter.UnderPreaaureWarn) //欠压预警
				SET_LED4;
			else
				RESET_LED4;
		
			//光柱数码管
			if(g_bar_tube_num<10)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=10&&g_bar_tube_num<=18)
				SPI_Send_Data(table2[g_bar_tube_num-10]);
			else if(g_bar_tube_num==19)
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
		
			SPI_Send_Data(0);
		break;
		
		case 2:
			RESET_SEG1;
			RESET_SEG2;
			SET_SEG3;
			RESET_SEG4;
		
			LEDFlashCnt++;
		    if(LEDFlashCnt>=LEDFLASHPERIOD*2)LEDFlashCnt=0;
			if(LEDFlashCnt<LEDFLASHPERIOD)
				SET_LED4;
			else
				RESET_LED4;
			
			//光柱数码管
			if(g_bar_tube_num<8)
				SPI_Send_Data(table2[g_bar_tube_num]);
			else if(g_bar_tube_num==9)
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
			
			SPI_Send_Data(CHAR_H);
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			//光柱数码管
			if(g_bar_tube_num<30)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=30&&g_bar_tube_num<=38)
				SPI_Send_Data(table2[g_bar_tube_num-30]);
			else if(g_bar_tube_num==39)
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
//Hx界面
//******************************************************************************
void Display_SubpageOfHx(void)
{ 
	static uint8_t DigitalFlashCnt;
	static uint16_t LEDFlashCnt;
    switch (SegSelect) 
	{
		case 0:
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
			
			//光柱数码管
			if(g_bar_tube_num<20)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=20&&g_bar_tube_num<=28)
				SPI_Send_Data(table2[g_bar_tube_num-20]);
			else if(g_bar_tube_num==29)
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
				SPI_Send_Data(table[EditData.thousand]);
			}
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
		
			//光柱数码管
			if(g_bar_tube_num<10)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=10&&g_bar_tube_num<=18)
				SPI_Send_Data(table2[g_bar_tube_num-10]);
			else if(g_bar_tube_num==19)
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
		
			if(g_edit_area == 2)
			{
				DigitalFlashCnt++;
				if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
				if(DigitalFlashCnt<DIGITALFLASHPERIOD)
				{
					SPI_Send_Data(table[EditData.hundred]|0x80);
				}
				else
				{
					SPI_Send_Data(0x80);
				}
		    }else
			{
				SPI_Send_Data(table[EditData.hundred]|0x80);
			}
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
			
			//光柱数码管
			if(g_bar_tube_num<8)
				SPI_Send_Data(table2[g_bar_tube_num]);
			else if(g_bar_tube_num==9)
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
				SPI_Send_Data(table[EditData.decade]);
			}
			
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			//光柱数码管
			if(g_bar_tube_num<30)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=30&&g_bar_tube_num<=38)
				SPI_Send_Data(table2[g_bar_tube_num-30]);
			else if(g_bar_tube_num==39)
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
				SPI_Send_Data(table[EditData.uint]);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//H6界面
//******************************************************************************
void Display_SubpageOfH6(void)
{ 
	static uint8_t DigitalFlashCnt;
	static uint16_t LEDFlashCnt;
    switch (SegSelect) 
	{
		case 0:
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
			
			//光柱数码管
			if(g_bar_tube_num<20)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=20&&g_bar_tube_num<=28)
				SPI_Send_Data(table2[g_bar_tube_num-20]);
			else if(g_bar_tube_num==29)
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

			SPI_Send_Data(0);
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
		
			//光柱数码管
			if(g_bar_tube_num<10)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=10&&g_bar_tube_num<=18)
				SPI_Send_Data(table2[g_bar_tube_num-10]);
			else if(g_bar_tube_num==19)
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

			SPI_Send_Data(0);

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
			
			//光柱数码管
			if(g_bar_tube_num<8)
				SPI_Send_Data(table2[g_bar_tube_num]);
			else if(g_bar_tube_num==9)
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
		  
			DigitalFlashCnt++;
			if(DigitalFlashCnt>=DIGITALFLASHPERIOD*2)DigitalFlashCnt=0;
			if(DigitalFlashCnt<DIGITALFLASHPERIOD)
			{
				if(SysParameter.DetectionMode == VoltageDetection)
					SPI_Send_Data(CHAR_U);
				else 
					SPI_Send_Data(CHAR_A);
			}
			else
			{
				SPI_Send_Data(0);
			}
		break;
		
		case 3:
			RESET_SEG1;
			RESET_SEG2;
			RESET_SEG3;
			SET_SEG4;
		
			//光柱数码管
			if(g_bar_tube_num<30)
				SPI_Send_Data(table2[0]);
			else if(g_bar_tube_num>=30&&g_bar_tube_num<=38)
				SPI_Send_Data(table2[g_bar_tube_num-30]);
			else if(g_bar_tube_num==39)
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
		
		  SPI_Send_Data(0);
		break;
		
		default:break;
	}
	SegSelect++;
	SegSelect=SegSelect%4;	
}
//******************************************************************************
//光柱数码管条数计算
//******************************************************************************
uint8_t DigitalCalculate(const uint16_t *data)
{ 
	if(*data<6)
		return 0;
	else if(*data>=6&&*data<246)
		return (*data+6)/12;//
	else if(*data>=246&&*data<500)
		return (*data-246)/13+21;
	else
		return 40;
}
/*==================================================================
* Function	: charsToHex
* Description	: 字符串转十六进制
* Input Para	: asc
* Output Para	: 无
* Return Value: 16进制数据
==================================================================*/
uint8_t charsToHex(uint8_t *asc)
{
  
    uint8_t hex=0;
    
    if((asc[0]>='0')&&(asc[0]<='9')){
        hex=asc[0]-0x30;
    }
    else if((asc[0]>='a')&&(asc[0]<='f')){
        hex=asc[0]-'a'+0xa;
    }
    else if((asc[0]>='A')&&(asc[0]<='F')){
        hex=asc[0]-'A'+0xa;
    }

    if((asc[1]>='0')&&(asc[1]<='9')){
        hex=hex<<4;
        hex+=(asc[1]-0x30);
    }
    else if((asc[1]>='a')&&(asc[1]<='f')){
        hex=hex<<4;
        hex+=(asc[1]-'a'+0xa);
    }
    else if((asc[1]>='A')&&(asc[1]<='F')){
        hex=hex<<4;
        hex+=(asc[1]-'A'+0xa);
    } 

    return hex;
}

/*==================================================================
* Function	: HexsTochars
* Description	: 十六进制转字符串
* Input Para	: hexs:源地址；length：长度
* Output Para	: ascs:目的地址；
* Return Value: 字符串长度
==================================================================*/
uint16_t  HexsTochars(uint8_t *ascs,uint8_t *hexs,uint16_t length)
{
    uint16_t j=0;
    uint8_t hex_hi;
    uint8_t hex_lo;
    uint16_t i=0;

		if(length == 0)
			return 0;

    for(i=0;i<length;i++){

        hex_hi = hexs[i]>>4;
        hex_lo = hexs[i]&0x0f;
        j = 2*i;

        if(hex_hi <= 9)
            ascs[j] = hex_hi + 0x30;
        else 
            ascs[j] = hex_hi + 'A'- 0xa;

        if(hex_lo <= 9)
            ascs[j+1] = hex_lo + 0x30;
        else 
            ascs[j+1] = hex_lo + 'A'-0xa; 

    } 
    return (j+2);
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
