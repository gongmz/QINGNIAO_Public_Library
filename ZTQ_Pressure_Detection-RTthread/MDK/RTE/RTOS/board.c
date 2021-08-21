/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "gpio.h"
#include "stdint.h"
#include "wdt.h"
#include "spi.h"
#include "flash.h"
#include "uart.h"
#include "global_variable.h"
#include "lptim.h"
#include "lpm.h"

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_os_tick_callback(void)
{
    rt_interrupt_enter();
    
    rt_tick_increase();

    rt_interrupt_leave();
}
void SysTick_IRQHandler()
{
	rt_os_tick_callback();
}
/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
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
	
	//ʹ���ڲ�����
		Sysctrl_SetRCLTrim(SysctrlRclFreq32768);        ///<
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);   ///< ʹ��RCLʱ��
	
//#error "TODO 1: OS Tick Configuration."
    /* 
     * TODO 1: OS Tick Configuration
     * Enable the hardware timer and call the rt_os_tick_callback function
     * periodically with the frequency RT_TICK_PER_SECOND. 
     */

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE

static int uart_init(void)
{
#error "TODO 2: Enable the hardware uart and config baudrate."
    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
#error "TODO 3: Output the string 'str' through the uart."
}

#endif
