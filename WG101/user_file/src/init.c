/**********************************头文件**************************************/
#include "init.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
/**********************************函数声明************************************/
void SysClockInit(void)
{
    stc_sysctrl_clk_cfg_t stcCfg;
    ///< 因要使用的时钟源HCLK小于24M：此处设置FLASH 读等待周期为0 cycle(默认值也为0 cycle)
    Flash_WaitCycle(FlashWaitCycle0);

    ///< 时钟初始化前，优先设置要使用的时钟源：此处设置RCH为24MHz（默认值为4MHz）
    Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
    Sysctrl_SetRTCAdjustClkFreq(SysctrlRTC24MHz);  //补偿高速时钟源   

    ///< 选择内部RCH作为HCLK时钟源;
    stcCfg.enClkSrc    = SysctrlClkRCH;
    ///< HCLK SYSCLK/2
    stcCfg.enHClkDiv   = SysctrlHclkDiv1;
    ///< PCLK 为HCLK/8
    stcCfg.enPClkDiv   = SysctrlPclkDiv1;
    ///< 系统时钟初始化，并启动时钟
    Sysctrl_ClkInit(&stcCfg);//
	//使能外部低速时钟
	Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);
	
	//使能内部低速
//	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);        ///<
//    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);   ///< 使能RCL时钟
}

/**************************************************************
*
*空闲引脚配置，设置为输出，无上下拉
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
    Gpio_ClrIO(GpioPortD, GpioPin3);//MODE (PD03)为高电平进入在线编程模式，通过上位机可以进行在线编程。 MODE (PD03)为低电平为工作模式
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
* 按键初始化
*
*
**************************************************************/
void KEY_Init(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    ///< 端口方向配置->输入
    stcGpioCfg.enDir = GpioDirIn;
    ///< 端口驱动能力配置->高驱动能力
    stcGpioCfg.enDrv = GpioDrvL;
    ///< 端口上下拉配置->无
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< 端口开漏输出配置->开漏输出关闭
    stcGpioCfg.enOD = GpioOdDisable;
    ///< 端口输入/输出值寄存器总线控制模式配置->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    ///< GPIO IO USER KEY初始化
    Gpio_Init(MENU_PORT, MENU_PIN, &stcGpioCfg); 
	Gpio_Init(UP_PORT, UP_PIN, &stcGpioCfg); 
	Gpio_Init(DOWN_PORT, DOWN_PIN, &stcGpioCfg); 
	Gpio_Init(ENTER_PORT, ENTER_PIN, &stcGpioCfg); 
}
/**************************************************************
* LED灯引脚初始化
*
*
**************************************************************/
void Init_LED(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
    ///< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    
    ///< LED关闭
    Gpio_ClrIO(LED1_PORT, LED1_PIN);
	Gpio_ClrIO(LED2_PORT, LED2_PIN);
	Gpio_ClrIO(LED3_PORT, LED3_PIN);
	Gpio_ClrIO(LED4_PORT, LED4_PIN);
	
	Gpio_ClrIO(SEG1_PORT, SEG1_PIN);
	Gpio_ClrIO(SEG2_PORT, SEG2_PIN);
	Gpio_ClrIO(SEG3_PORT, SEG3_PIN);
	Gpio_ClrIO(SEG4_PORT, SEG4_PIN);
    
    ///< GPIO IO LED端口初始化
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
 ** \brief  初始化LPTIMER
 **
 ** \return 无
 ******************************************************************************/
void LPTimerInit(void)
{
    stc_lptim_cfg_t    stcLptCfg;
    DDL_ZERO_STRUCT(stcLptCfg);

    ///< 使能LPTIM0 外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, TRUE);

    stcLptCfg.enGate   = LptimGateLow;
    stcLptCfg.enGatep  = LptimGatePLow;
    stcLptCfg.enTcksel = LptimXtl;
    stcLptCfg.enTogen  = LptimTogEnLow;
    stcLptCfg.enCt     = LptimTimerFun;         //定时器功能
    stcLptCfg.enMd     = LptimMode2;            //自动重载16位计数器/定时器
    stcLptCfg.u16Arr   = 0xBFFF;                //预装载寄存器值，0.5s一个中断
    Lptim_Init(M0P_LPTIMER, &stcLptCfg);
		
    Lptim_ClrItStatus(M0P_LPTIMER);   //清除中断标志位
    Lptim_ConfIt(M0P_LPTIMER, TRUE);  //允许LPTIMER中断
    EnableNvic(LPTIM_IRQn, IrqLevel3, TRUE);
	
	Lptim_Cmd(M0P_LPTIMER,TRUE);
}
/**************************************************************
*
*SPI配置
*
**************************************************************/
void SPI_Init(void)
{

    stc_gpio_cfg_t GpioInitStruct;
	  stc_spi_cfg_t  SpiInitStruct;
	
    DDL_ZERO_STRUCT(GpioInitStruct);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
	  Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0,TRUE);

    //SPI0引脚配置:主机
    GpioInitStruct.enDrv = GpioDrvH;
    GpioInitStruct.enDir = GpioDirOut;

    Gpio_Init(GpioPortA, GpioPin7,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin7,GpioAf1);        //配置引脚PA7作为SPI0_MOSI

    Gpio_Init(GpioPortA, GpioPin4,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin4,GpioAf1);         //配置引脚PA04作为SPI0_CS

    Gpio_Init(GpioPortA, GpioPin5,&GpioInitStruct);
    Gpio_SetAfMode(GpioPortA, GpioPin5,GpioAf1);         //配置引脚PA05作为SPI0_SCK


    //SPI0模块配置：主机
    SpiInitStruct.enSpiMode = SpiMskMaster;   //配置位主机模式
    SpiInitStruct.enPclkDiv = SpiClkMskDiv2;  //波特率：fsys/2
    SpiInitStruct.enCPHA    = SpiMskCphafirst;//第一边沿采样
    SpiInitStruct.enCPOL    = SpiMskcpollow;  //极性为低
    Spi_Init(M0P_SPI0, &SpiInitStruct);
		
}
/**************************************************************
*
*SPI发送一个字节数据
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
*Timer3配置
*
**************************************************************/
void Timer3Init(void )
{
    uint16_t                    u16ArrValue;
    uint16_t                    u16CntValue;
    stc_tim3_mode0_cfg_t     stcTim3BaseCfg;
    
    //结构体初始化清零
    DDL_ZERO_STRUCT(stcTim3BaseCfg);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); //Base Timer外设时钟使能
    
    stcTim3BaseCfg.enWorkMode = Tim3WorkMode0;              //定时器模式
    stcTim3BaseCfg.enCT       = Tim3Timer;                  //定时器功能，计数时钟为内部PCLK
    stcTim3BaseCfg.enPRS      = Tim3PCLKDiv32;              //PCLK/64
    stcTim3BaseCfg.enCntMode  = Tim316bitArrMode;           //自动重载16位计数器/定时器
    stcTim3BaseCfg.bEnTog     = FALSE;
    stcTim3BaseCfg.bEnGate    = FALSE;
    stcTim3BaseCfg.enGateP    = Tim3GatePositive;
    
    Tim3_Mode0_Init(&stcTim3BaseCfg);                       //TIM3 的模式0功能初始化
        
    u16ArrValue = 0xF159;//10MS
    
    Tim3_M0_ARRSet(u16ArrValue);                            //设置重载值(ARR = 0x10000 - 周期)
    
    u16CntValue = 0xF159;
    
    Tim3_M0_Cnt16Set(u16CntValue);                          //设置计数初值
    
    Tim3_ClearIntFlag(Tim3UevIrq);                          //清中断标志
    Tim3_Mode0_EnableIrq();                                 //使能TIM3中断(模式0时只有一个中断)
    EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 开中断 
		
		Tim3_M0_Run(); 
}

void Uart0_Init( void )
{
	  //引脚配置
	  stc_gpio_cfg_t stcGpioCfg;
	  stc_uart_cfg_t    stcCfg;
    DDL_ZERO_STRUCT(stcGpioCfg);
    DDL_ZERO_STRUCT(stcCfg);
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //使能GPIO模块时钟
    ///<TX
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);          //配置PA09 端口为URART0_TX
    ///<RX
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);          //配置PA010 端口为URART0_RX
	
	
	  //串口配置
    ///< 开启外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);///<使能uart0模块时钟

    ///<UART Init
    stcCfg.enRunMode        = UartMskMode1;          ///<模式1
    stcCfg.enStopBit        = UartMsk1bit;           ///<1bit停止位
    stcCfg.enMmdorCk        = UartMskEven;           ///<偶检验
    stcCfg.stcBaud.u32Baud  = 115200;                ///<波特率115200
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<通道采样分频配置
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<获得外设时钟（PCLK）频率值
    Uart_Init(M0P_UART0, &stcCfg);                   ///<串口初始化
}

#ifdef Printf_Enable
void LPuart1_Init( void )
{
	stc_lpuart_cfg_t  stcCfg;
	stc_gpio_cfg_t stcGpioCfg;
    DDL_ZERO_STRUCT(stcCfg);
	DDL_ZERO_STRUCT(stcGpioCfg);
    
    ///<外设模块时钟使能
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1,TRUE);    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
	
    
    ///<TX
    stcGpioCfg.enDir =  GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin0,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin0,GpioAf2); //配置PA00为LPUART1_TX
    
    //<RX
    stcGpioCfg.enDir =  GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin1,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin1,GpioAf2); //配置PA01为LPUART1_RX
	
    ///<LPUART 初始化
    stcCfg.enStopBit = LPUart1bit;                   ///<1停止位    
    stcCfg.enMmdorCk = LPUartEven;                   ///<偶校验
    stcCfg.stcBaud.enSclkSel = LPUartMskPclk;        ///<传输时钟源
    stcCfg.stcBaud.u32Sclk = Sysctrl_GetPClkFreq();  ///<PCLK获取
    stcCfg.stcBaud.enSclkDiv = LPUartMsk4Or8Div;     ///<采样分频
    stcCfg.stcBaud.u32Baud = 115200;                   ///<波特率
    stcCfg.enRunMode = LPUartMskMode1;               ///<工作模式
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






