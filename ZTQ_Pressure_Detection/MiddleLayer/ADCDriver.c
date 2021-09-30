/**********************************头文件**************************************/
#include   "ADCDriver.h"
#include   "logic.h"
/**********************************宏定义声明**********************************/
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
uint16_t curADC;//
float VoltageGain=0.19413919;
float VoltageOffset=-16.39804639;
float CurrentGain=0.30149960;
float CurrentOffset=-150.74980268;
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
		temp=curADC*VoltageGain+VoltageOffset;
	else
		temp=curADC*CurrentGain+CurrentOffset;
	
	*data=temp;
}
/**************************************************************
*
*ADC校正
*
**************************************************************/
void AdcCalibration(void)
{
	if(SysParameter.DetectionMode == VoltageDetection)
		VoltageOffset=0-curADC*VoltageGain;
	else
		CurrentOffset=0-curADC*CurrentGain;
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
	
	 if( PressureValue>=SysParameter.OverPreaaureAlarm )
	 {
		DeviceState |=DS_OVER_PRESSURE;
		 
		DeviceState &= ~DS_OVER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE;
	 }
	 else if(PressureValue>=SysParameter.OverPreaaureWarn&&PressureValue<SysParameter.OverPreaaureAlarm)
	 {
		DeviceState |=DS_OVER_PRESSURE_WARN;
		 
		DeviceState &= ~DS_OVER_PRESSURE;
		DeviceState &= ~DS_UNDER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE;
	 }
	 else if(PressureValue>SysParameter.UnderPreaaureAlarm&&PressureValue<=SysParameter.UnderPreaaureWarn)
	 {
		DeviceState |=DS_UNDER_PRESSURE_WARN;
		 
		DeviceState &= ~DS_OVER_PRESSURE;
		DeviceState &= ~DS_OVER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE;
	 }
	 else if(PressureValue<=SysParameter.UnderPreaaureAlarm)
	 {
		DeviceState |=DS_UNDER_PRESSURE;
		 
		DeviceState &= ~DS_OVER_PRESSURE;
		DeviceState &= ~DS_OVER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE_WARN;
	 }
	 else
	 {
		DeviceState &= ~DS_OVER_PRESSURE;
		DeviceState &= ~DS_OVER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE_WARN;
		DeviceState &= ~DS_UNDER_PRESSURE;
	 }
	 
	 if( PressureValue>SysParameter.Range )
        DeviceState |=DS_OUTRANGE;
     else
        DeviceState &= ~DS_OUTRANGE;

	 
	 //报警条件
	 if(((DeviceState&DS_OVER_PRESSURE)||(DeviceState&DS_UNDER_PRESSURE))&&(WorkState==MODE_NORMAL_ST))
		 MsgPost(LOGIC_PRIO, LOGIC_ALARM_MSG);
	 else if(((DeviceState&DS_OVER_PRESSURE)==0)&&((DeviceState&DS_UNDER_PRESSURE)==0)&&(WorkState==MODE_ALARM_ST))
		 MsgPost(LOGIC_PRIO, LOGIC_NORMAL_MSG);
}

