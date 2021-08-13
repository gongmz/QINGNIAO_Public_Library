/**********************************ͷ�ļ�**************************************/
#include "init.h"
/**********************************�궨������**********************************/
/**********************************�ṹ������**********************************/
/**********************************��������************************************/
/**********************************��������************************************/
void SysClockInit(void)
{
    stc_sysctrl_clk_cfg_t stcCfg;
    ///< ��Ҫʹ�õ�ʱ��ԴHCLKС��24M���˴�����FLASH ���ȴ�����Ϊ0 cycle(Ĭ��ֵҲΪ0 cycle)
    Flash_WaitCycle(FlashWaitCycle0);

    ///< ʱ�ӳ�ʼ��ǰ����������Ҫʹ�õ�ʱ��Դ���˴�����RCHΪ24MHz��Ĭ��ֵΪ4MHz��
    Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
    Sysctrl_SetRTCAdjustClkFreq(SysctrlRTC24MHz);  //��������ʱ��Դ   

    ///< ѡ���ڲ�RCH��ΪHCLKʱ��Դ;
    stcCfg.enClkSrc    = SysctrlClkRCH;
    ///< HCLK SYSCLK/2
    stcCfg.enHClkDiv   = SysctrlHclkDiv1;
    ///< PCLK ΪHCLK/8
    stcCfg.enPClkDiv   = SysctrlPclkDiv1;
    ///< ϵͳʱ�ӳ�ʼ����������ʱ��
    Sysctrl_ClkInit(&stcCfg);//
	//ʹ���ⲿ����ʱ��
	Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);
	
	//ʹ���ڲ�����
//	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);        ///<
//    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);   ///< ʹ��RCLʱ��
}

/**************************************************************
*
*�����������ã�����Ϊ�������������
*
**************************************************************/
void GPIO_Init(void)
{
	
	 stc_gpio_cfg_t pstcGpioCfg;
	 Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
	
    pstcGpioCfg.enDir = GpioDirIn;
    pstcGpioCfg.enDrv = GpioDrvL;
    pstcGpioCfg.enPu = GpioPuDisable;
	  pstcGpioCfg.enPd = GpioPdDisable;
    pstcGpioCfg.enOD = GpioOdDisable;
    pstcGpioCfg.enCtrlMode = GpioAHB;

	//PORTA
    Gpio_Init(GpioPortA, GpioPin0, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin1, &pstcGpioCfg);
	  Gpio_Init(GpioPortA, GpioPin2, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin3, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin4, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin5, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin6, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin7, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin8, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin9, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin10, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin11, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin12, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin13, &pstcGpioCfg);
	  Gpio_Init(GpioPortA, GpioPin14, &pstcGpioCfg);
    Gpio_Init(GpioPortA, GpioPin15, &pstcGpioCfg);

	  Gpio_ClrIO(GpioPortA, GpioPin0);
    Gpio_ClrIO(GpioPortA, GpioPin1);
    Gpio_ClrIO(GpioPortA, GpioPin2);
    Gpio_ClrIO(GpioPortA, GpioPin3);
	  Gpio_ClrIO(GpioPortA, GpioPin4);
	  Gpio_ClrIO(GpioPortA, GpioPin5);
    Gpio_ClrIO(GpioPortA, GpioPin6);
    Gpio_ClrIO(GpioPortA, GpioPin7);
    Gpio_ClrIO(GpioPortA, GpioPin8);
    Gpio_ClrIO(GpioPortA, GpioPin9);
    Gpio_ClrIO(GpioPortA, GpioPin10);
    Gpio_ClrIO(GpioPortA, GpioPin11);
    Gpio_ClrIO(GpioPortA, GpioPin12);
    Gpio_ClrIO(GpioPortA, GpioPin13);
    Gpio_ClrIO(GpioPortA, GpioPin14);
    Gpio_ClrIO(GpioPortA, GpioPin15);

	//PORTB
    Gpio_Init(GpioPortB, GpioPin0, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin1, &pstcGpioCfg);
  	Gpio_Init(GpioPortB, GpioPin2, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin3, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin4, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin6, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin7, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin8, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin9, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin10, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin11, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin12, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin13, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin14, &pstcGpioCfg);
    Gpio_Init(GpioPortB, GpioPin15, &pstcGpioCfg);	
	
	
	  Gpio_ClrIO(GpioPortB, GpioPin0);
    Gpio_ClrIO(GpioPortB, GpioPin1);
    Gpio_ClrIO(GpioPortB, GpioPin2);
    Gpio_ClrIO(GpioPortB, GpioPin3);
	  Gpio_ClrIO(GpioPortB, GpioPin4);
    Gpio_ClrIO(GpioPortB, GpioPin5);
    Gpio_ClrIO(GpioPortB, GpioPin6);
    Gpio_ClrIO(GpioPortB, GpioPin7);
    Gpio_ClrIO(GpioPortB, GpioPin8);
    Gpio_ClrIO(GpioPortB, GpioPin9);
    Gpio_ClrIO(GpioPortB, GpioPin10);
    Gpio_ClrIO(GpioPortB, GpioPin11);
    Gpio_ClrIO(GpioPortB, GpioPin12);
    Gpio_ClrIO(GpioPortB, GpioPin13);
    Gpio_ClrIO(GpioPortB, GpioPin14);
    Gpio_ClrIO(GpioPortB, GpioPin15);
	
	//PORTC
    Gpio_Init(GpioPortC, GpioPin0, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin1, &pstcGpioCfg);
  	Gpio_Init(GpioPortC, GpioPin2, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin3, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin4, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin5, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin6, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin7, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin8, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin9, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin10, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin11, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin12, &pstcGpioCfg);
    Gpio_Init(GpioPortC, GpioPin13, &pstcGpioCfg);

    Gpio_ClrIO(GpioPortC, GpioPin0);
    Gpio_ClrIO(GpioPortC, GpioPin1);
    Gpio_ClrIO(GpioPortC, GpioPin2);
  	Gpio_ClrIO(GpioPortC, GpioPin3);
    Gpio_ClrIO(GpioPortC, GpioPin4);
    Gpio_ClrIO(GpioPortC, GpioPin5);
    Gpio_ClrIO(GpioPortC, GpioPin6);
    Gpio_ClrIO(GpioPortC, GpioPin7);
    Gpio_ClrIO(GpioPortC, GpioPin8);
    Gpio_ClrIO(GpioPortC, GpioPin9);
    Gpio_ClrIO(GpioPortC, GpioPin10);
    Gpio_ClrIO(GpioPortC, GpioPin11);
    Gpio_ClrIO(GpioPortC, GpioPin12);
    Gpio_ClrIO(GpioPortC, GpioPin13);

	//PORTD
    Gpio_Init(GpioPortD, GpioPin0, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin1, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin2, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin3, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin6, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin7, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin8, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin9, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin10, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin11, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin12, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin13, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin14, &pstcGpioCfg);
    Gpio_Init(GpioPortD, GpioPin15, &pstcGpioCfg);

    Gpio_ClrIO(GpioPortD, GpioPin0);
    Gpio_ClrIO(GpioPortD, GpioPin1);
    Gpio_ClrIO(GpioPortD, GpioPin2);
    Gpio_ClrIO(GpioPortD, GpioPin3);//MODE (PD03)Ϊ�ߵ�ƽ�������߱��ģʽ��ͨ����λ�����Խ������߱�̡� MODE (PD03)Ϊ�͵�ƽΪ����ģʽ
	  Gpio_ClrIO(GpioPortD, GpioPin4);
    Gpio_ClrIO(GpioPortD, GpioPin5);
    Gpio_ClrIO(GpioPortD, GpioPin6);
    Gpio_ClrIO(GpioPortD, GpioPin7);
    Gpio_ClrIO(GpioPortD, GpioPin8);
    Gpio_ClrIO(GpioPortD, GpioPin9);
    Gpio_ClrIO(GpioPortD, GpioPin10);
    Gpio_ClrIO(GpioPortD, GpioPin11);
    Gpio_ClrIO(GpioPortD, GpioPin12);
    Gpio_ClrIO(GpioPortD, GpioPin13);
    Gpio_ClrIO(GpioPortD, GpioPin14);
    Gpio_ClrIO(GpioPortD, GpioPin15);

}
/**************************************************************
*
*
*
**************************************************************/
void Wdt_Interface_Init(void)
{
	  Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt,TRUE);
    Wdt_Init(WdtResetEn,WdtT13s1);
    Wdt_Start();
}
/**************************************************************
* ������ʼ��
*
*
**************************************************************/
void KEY_Init(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< ��GPIO����ʱ���ſ�
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    ///< �˿ڷ�������->����
    stcGpioCfg.enDir = GpioDirIn;
    ///< �˿�������������->����������
    stcGpioCfg.enDrv = GpioDrvL;
    ///< �˿�����������->��
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< �˿ڿ�©�������->��©����ر�
    stcGpioCfg.enOD = GpioOdDisable;
    ///< �˿�����/���ֵ�Ĵ������߿���ģʽ����->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    ///< GPIO IO USER KEY��ʼ��
    Gpio_Init(MENU_PORT, MENU_PIN, &stcGpioCfg); 
	Gpio_Init(UP_PORT, UP_PIN, &stcGpioCfg); 
	Gpio_Init(DOWN_PORT, DOWN_PIN, &stcGpioCfg); 
	Gpio_Init(ENTER_PORT, ENTER_PIN, &stcGpioCfg); 
}
/**************************************************************
* LED�����ų�ʼ��
*
*
**************************************************************/
void Init_LED(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< ��GPIO����ʱ���ſ�
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
    stcGpioCfg.enDir = GpioDirOut;
    ///< �˿�����������->����
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    
    ///< LED�ر�
    Gpio_ClrIO(LED1_PORT, LED1_PIN);
	Gpio_ClrIO(LED2_PORT, LED2_PIN);
	Gpio_ClrIO(LED3_PORT, LED3_PIN);
	Gpio_ClrIO(LED4_PORT, LED4_PIN);
	
	Gpio_ClrIO(SEG1_PORT, SEG1_PIN);
	Gpio_ClrIO(SEG2_PORT, SEG2_PIN);
	Gpio_ClrIO(SEG3_PORT, SEG3_PIN);
	Gpio_ClrIO(SEG4_PORT, SEG4_PIN);
    
    ///< GPIO IO LED�˿ڳ�ʼ��
	Gpio_Init(LED1_PORT, LED1_PIN, &stcGpioCfg);
	Gpio_Init(LED2_PORT, LED2_PIN, &stcGpioCfg);
	Gpio_Init(LED3_PORT, LED3_PIN, &stcGpioCfg);
	Gpio_Init(LED4_PORT, LED4_PIN, &stcGpioCfg);
	
	Gpio_Init(SEG1_PORT, SEG1_PIN, &stcGpioCfg);
	Gpio_Init(SEG2_PORT, SEG2_PIN, &stcGpioCfg);
	Gpio_Init(SEG3_PORT, SEG3_PIN, &stcGpioCfg);
	Gpio_Init(SEG4_PORT, SEG4_PIN, &stcGpioCfg);
	
}
/**
 ******************************************************************************
 ** \brief  ��ʼ��LPTIMER
 **
 ** \return ��
 ******************************************************************************/
void LPTimerInit(void)
{
    stc_lptim_cfg_t    stcLptCfg;
    DDL_ZERO_STRUCT(stcLptCfg);

    ///< ʹ��LPTIM0 ����ʱ��
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, TRUE);

    stcLptCfg.enGate   = LptimGateLow;
    stcLptCfg.enGatep  = LptimGatePLow;
    stcLptCfg.enTcksel = LptimXtl;
    stcLptCfg.enTogen  = LptimTogEnLow;
    stcLptCfg.enCt     = LptimTimerFun;         //��ʱ������
    stcLptCfg.enMd     = LptimMode2;            //�Զ�����16λ������/��ʱ��
    stcLptCfg.u16Arr   = 0xBFFF;                //Ԥװ�ؼĴ���ֵ��0.5sһ���ж�
    Lptim_Init(M0P_LPTIMER, &stcLptCfg);
		
    Lptim_ClrItStatus(M0P_LPTIMER);   //����жϱ�־λ
    Lptim_ConfIt(M0P_LPTIMER, TRUE);  //����LPTIMER�ж�
    EnableNvic(LPTIM_IRQn, IrqLevel3, TRUE);
	
	Lptim_Cmd(M0P_LPTIMER,TRUE);
}
/**************************************************************
*
*SPI����
*
**************************************************************/
void SPI_Init(void)
{

    stc_gpio_cfg_t GpioInitStruct;
	  stc_spi_cfg_t  SpiInitStruct;
	
    DDL_ZERO_STRUCT(GpioInitStruct);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
	  Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0,TRUE);

    //SPI0��������:����
    GpioInitStruct.enDrv = GpioDrvH;
    GpioInitStruct.enDir = GpioDirOut;

    Gpio_Init(GpioPortA, GpioPin7,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin7,GpioAf1);        //��������PA7��ΪSPI0_MOSI

    Gpio_Init(GpioPortA, GpioPin4,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin4,GpioAf1);         //��������PA04��ΪSPI0_CS

    Gpio_Init(GpioPortA, GpioPin5,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin5,GpioAf1);         //��������PA05��ΪSPI0_SCK


    //SPI0ģ�����ã�����
    SpiInitStruct.enSpiMode = SpiMskMaster;   //����λ����ģʽ
    SpiInitStruct.enPclkDiv = SpiClkMskDiv2;  //�����ʣ�fsys/2
    SpiInitStruct.enCPHA    = SpiMskCphafirst;//��һ���ز���
    SpiInitStruct.enCPOL    = SpiMskcpollow;  //����Ϊ��
    Spi_Init(M0P_SPI0, &SpiInitStruct);
		
}
/**************************************************************
*
*SPI����һ���ֽ�����
*
**************************************************************/
void SPI_Send_Data(uint8_t data)
{
	Spi_SetCS(M0P_SPI0, FALSE);
	

	Spi_SendData(M0P_SPI0, data);
	while(Spi_GetStatus(M0P_SPI0, SpiTxe) == FALSE); 

	Spi_SetCS(M0P_SPI0, TRUE);
}

void parameter_init(void)
{

}


void TogleGpio(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    boolean_t Status;
    Status= Gpio_ReadOutputIO(enPort,enPin);
    if(Status == TRUE)
    {
        Gpio_WriteOutputIO(enPort,enPin,FALSE);
    }
    else
    {
        Gpio_WriteOutputIO(enPort,enPin,TRUE);
    }
}


/**************************************************************
*
*Timer3����
*
**************************************************************/
void Timer3Init(void )
{
    uint16_t                    u16ArrValue;
    uint16_t                    u16CntValue;
    stc_tim3_mode0_cfg_t     stcTim3BaseCfg;
    
    //�ṹ���ʼ������
    DDL_ZERO_STRUCT(stcTim3BaseCfg);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); //Base Timer����ʱ��ʹ��
    
    stcTim3BaseCfg.enWorkMode = Tim3WorkMode0;              //��ʱ��ģʽ
    stcTim3BaseCfg.enCT       = Tim3Timer;                  //��ʱ�����ܣ�����ʱ��Ϊ�ڲ�PCLK
    stcTim3BaseCfg.enPRS      = Tim3PCLKDiv32;              //PCLK/64
    stcTim3BaseCfg.enCntMode  = Tim316bitArrMode;           //�Զ�����16λ������/��ʱ��
    stcTim3BaseCfg.bEnTog     = FALSE;
    stcTim3BaseCfg.bEnGate    = FALSE;
    stcTim3BaseCfg.enGateP    = Tim3GatePositive;
    
    Tim3_Mode0_Init(&stcTim3BaseCfg);                       //TIM3 ��ģʽ0���ܳ�ʼ��
        
    u16ArrValue = 0xF159;//10MS
    
    Tim3_M0_ARRSet(u16ArrValue);                            //��������ֵ(ARR = 0x10000 - ����)
    
    u16CntValue = 0xF159;
    
    Tim3_M0_Cnt16Set(u16CntValue);                          //���ü�����ֵ
    
    Tim3_ClearIntFlag(Tim3UevIrq);                          //���жϱ�־
    Tim3_Mode0_EnableIrq();                                 //ʹ��TIM3�ж�(ģʽ0ʱֻ��һ���ж�)
    EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 ���ж� 
		
		Tim3_M0_Run(); 
}

void Uart0_Init( void )
{
	  //��������
	  stc_gpio_cfg_t stcGpioCfg;
	  stc_uart_cfg_t    stcCfg;
    DDL_ZERO_STRUCT(stcGpioCfg);
    DDL_ZERO_STRUCT(stcCfg);
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //ʹ��GPIOģ��ʱ��
    ///<TX
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);          //����PA09 �˿�ΪURART0_TX
    ///<RX
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);          //����PA010 �˿�ΪURART0_RX
	
	
	  //��������
    ///< ��������ʱ��
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);///<ʹ��uart0ģ��ʱ��

    ///<UART Init
    stcCfg.enRunMode        = UartMskMode1;          ///<ģʽ1
    stcCfg.enStopBit        = UartMsk1bit;           ///<1bitֹͣλ
    stcCfg.enMmdorCk        = UartMskEven;           ///<ż����
    stcCfg.stcBaud.u32Baud  = 115200;                ///<������115200
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<ͨ��������Ƶ����
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<�������ʱ�ӣ�PCLK��Ƶ��ֵ
    Uart_Init(M0P_UART0, &stcCfg);                   ///<���ڳ�ʼ��
}

#ifdef Printf_Enable
void LPuart1_Init( void )
{
	stc_lpuart_cfg_t  stcCfg;
	stc_gpio_cfg_t stcGpioCfg;
    DDL_ZERO_STRUCT(stcCfg);
	DDL_ZERO_STRUCT(stcGpioCfg);
    
    ///<����ģ��ʱ��ʹ��
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1,TRUE);    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
	
    
    ///<TX
    stcGpioCfg.enDir =  GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin0,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin0,GpioAf2); //����PA00ΪLPUART1_TX
    
    //<RX
    stcGpioCfg.enDir =  GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin1,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin1,GpioAf2); //����PA01ΪLPUART1_RX
	
    ///<LPUART ��ʼ��
    stcCfg.enStopBit = LPUart1bit;                   ///<1ֹͣλ    
    stcCfg.enMmdorCk = LPUartEven;                   ///<żУ��
    stcCfg.stcBaud.enSclkSel = LPUartMskPclk;        ///<����ʱ��Դ
    stcCfg.stcBaud.u32Sclk = Sysctrl_GetPClkFreq();  ///<PCLK��ȡ
    stcCfg.stcBaud.enSclkDiv = LPUartMsk4Or8Div;     ///<������Ƶ
    stcCfg.stcBaud.u32Baud = 115200;                   ///<������
    stcCfg.enRunMode = LPUartMskMode1;               ///<����ģʽ
    LPUart_Init(M0P_LPUART1, &stcCfg);
}
/**
 ******************************************************************************
 ** \brief  Re-target putchar function
 ******************************************************************************/
int fputc(int ch, FILE *f)
{

    if (((uint8_t)ch) == '\n')
    {
		LPUart_SendData( M0P_LPUART1, '\r' );
    }
    LPUart_SendData( M0P_LPUART1,ch );

    return ch;
}
#endif






