/**********************************头文件**************************************/
#include "rtthread.h"
#include "includes.h"
//#include "rtc_app.h"
//#include "time_app.h"
//#include "save.h"
//#include "global_variable.h"
//#include "CJT188.h"
/**********************************结构体声明**********************************/
/**********************************变量声明************************************/
static rt_thread_t      tid_key      =   RT_NULL;
static rt_thread_t      tid_key1      =   RT_NULL;
#define THREAD_PRIORITY             14
#define THREAD_STACK_SIZE           256
#define THREAD_TIMESLICE            5

/**********************************函数声明************************************/
static void key_thread_entry(void *param)
{   
    while (1)
    {
		    Screen();
//				rt_kprintf("thread1.................\r\n");
        rt_thread_mdelay(1);   
    }
}

static void key1_thread_entry(void *param)
{   
    while (1)
    {
	//	    rt_kprintf("thread3.................\r\n");
        rt_thread_mdelay(10000);   
    }
}
int32_t main(void)
{
	
		tid_key = rt_thread_create("key",
												key_thread_entry, RT_NULL,
												THREAD_STACK_SIZE,
												THREAD_PRIORITY, THREAD_TIMESLICE);
		rt_thread_startup(tid_key);
	
	
	
	
	
			tid_key1 = rt_thread_create("key1",
												key1_thread_entry, RT_NULL,
												THREAD_STACK_SIZE,
												15, THREAD_TIMESLICE);
		rt_thread_startup(tid_key1);
	
    while(1)
	{
//		rt_kprintf("main_thread.................\r\n");
		rt_thread_mdelay(1000);
	}

}

