#include "Save.h"
uint32_t flashInformationAddress    = 0xfe00;
/*******************************************************************************
 * FLASH 中断服务函数
 ******************************************************************************/
static volatile uint32_t u32FlashTestFlag   = 0;

void FlashInt(void)
{
    if (TRUE == Flash_GetIntFlag(FlashPCInt))
    {
        Flash_ClearIntFlag(FlashPCInt);
        u32FlashTestFlag |= 0x01;
        Flash_DisableIrq(FlashPCInt);
    }
    if (TRUE == Flash_GetIntFlag(FlashSlockInt))
    {
        Flash_ClearIntFlag(FlashSlockInt);
        u32FlashTestFlag |= 0x02;
        Flash_DisableIrq(FlashSlockInt);
    }
}

void Flash_Read(uint32_t Address, uint8_t *data, uint16_t length)
{
	int  addr;
    for(addr=0; addr<length; addr++)
    {
        data[addr]= *((volatile uint8_t*)(Address+addr));
    }
}
void Flash_Write(uint32_t Address, uint8_t *data, uint16_t length)
{
	int i;
    Flash_SectorErase(Address);
    for(i=0; i<length; i++)
    {
        Flash_WriteByte(Address+i,data[i]);
    }
}


