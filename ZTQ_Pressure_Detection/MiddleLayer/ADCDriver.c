/**********************************头文件**************************************/
#include   "ADCDriver.h"
#include   "logic.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
uint16_t curADC;//
/**********************************函数声明************************************/

/**************************************************************
*
*ADC初始化
*
**************************************************************/
void AdcInit(void)
{
	stc_adc_cfg_t    stcAdcCfg;
	stc_adc_sqr_cfg_t          stcAdcSqrCfg;
	DDL_ZERO_STRUCT(stcAdcCfg);
	
	
    Gpio_SetAnalogMode(GpioPortB, GpioPin1);
    
    
    ///< 开启ADC/BGR 外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE); 
    
    Bgr_BgrEnable();        ///< 开启BGR
    
    ///< ADC 初始化配置
    stcAdcCfg.enAdcMode         = AdcScanMode;           
    stcAdcCfg.enAdcClkDiv       = AdcMskClkDiv1;            ///<采样分频-1
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle12Clk;     ///<采样周期数-12
    stcAdcCfg.enAdcRefVolSel    = AdcMskRefVolSelInBgr2p5;  ///<参考电压选择-内部2.5V
    stcAdcCfg.enAdcOpBuf        = AdcMskBufDisable;         ///<OP BUF配置-关
    stcAdcCfg.enInRef           = AdcMskInRefEnable;        ///<内部参考电压使能-开
    stcAdcCfg.enAdcAlign        = AdcAlignRight;            ///<转换结果对齐方式-右
    Adc_Init(&stcAdcCfg);
	
	stcAdcSqrCfg.bSqrDmaTrig = FALSE;
    stcAdcSqrCfg.enResultAcc = AdcResultAccDisable;
    stcAdcSqrCfg.u8SqrCnt    = 2;
    Adc_SqrModeCfg(&stcAdcSqrCfg);
	
	
    ///< 配置顺序扫描转换通道
    Adc_CfgSqrChannel(AdcSQRCH1MUX, AdcExInputCH9);  
    ///< ADC 中断使能
    Adc_EnableIrq();
    EnableNvic(ADC_IRQn, IrqLevel3, TRUE);
}

/**************************************************************
*
*ADC计算
*
**************************************************************/
void AdcCalculate(uint16_t *data)
{
	float temp;
	
	if(SysParameter.DetectionMode == VoltageDetection)
		temp=(curADC*555)/4095;
	else
		temp=((curADC-752)*500)/2534;
	
	*data=temp;
}
/****************************************************************************** 
* 函数名称：TaskAdc
* 函数功能：ADC任务
* 输入参数：无
* 输出参数：无
* 函数返回：无
* 使用说明：1秒调用1次
******************************************************************************/
void TaskAdc(void)
{
	 AdcCalculate(&PressureValue);
	 g_bar_tube_num=DigitalCalculate(&PressureValue);
	
	 if( PressureValue>=SysParameter.OverPreaaureAlarm )
		DeviceState |=DS_OVER_PRESSURE;
	 else
		DeviceState &= ~DS_OVER_PRESSURE;

	 if( PressureValue<=SysParameter.UnderPreaaureAlarm )
		DeviceState |=DS_UNDER_PRESSURE;
	 else
		DeviceState &= ~DS_UNDER_PRESSURE;	

	 if( PressureValue>SysParameter.Range )
		DeviceState |=DS_OUTRANGE;
	 else
		DeviceState &= ~DS_OUTRANGE;
	 
	 if((DeviceState&DS_OVER_PRESSURE)||(DeviceState&DS_UNDER_PRESSURE))
		 MsgPost(LOGIC_PRIO, LOGIC_ALARM_MSG);
	 else 
		 MsgPost(LOGIC_PRIO, LOGIC_NORMAL_MSG);
}

