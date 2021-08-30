/*
@--------------------------------------------------------------------------------------------------
@
@   File Name  :    LoRaFun.h
@
@   Description:
@
@   Date       :
@--------------------------------------------------------------------------------------------------
*/
#ifndef	LORAFUN_H
#define LORAFUN_H

#include    <stdio.h>
#include    <stdint.h>
#include    <stdlib.h>

// ===== work state define =====
enum enumLoRaWorkState {
    LORA_ST_SEND_EVENT,
    LORA_ST_POWERON, 
    LORA_ST_IDLE,
    LORA_ST_SETSTATE,
	LORA_ST_SELFCHECK,
};

typedef struct
{
    uint8_t state;  //状态
    uint8_t event;  //事件
}t_send_data;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LORA_MSG_ENTRY            0x80    
#define LORA_MSG_RX_OK            0x40   
#define LORA_MSG_TMOUT1           0x20      
#define LORA_MSG_SEND_OK          0x10 
#define LORA_MSG_SEND_ERROR       0x08 
#define LORA_MSG_NSJOIN           0x04
#define LORA_MSG_TMOUT2           0x02  
#define LORA_MSG_SEND_EVENT       0x01  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//设备状态（DeviceState）标志位
#define DS_UNDERVOLTAGE            0x01
#define DS_POLLUTE                 0x02 
#define DS_SEPARATE                0x04
#define DS_FIRE                    0x10
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern t_send_data send_data;
extern uint8_t  LoRaState;
extern uint8_t EnterShortKeyNum;
extern void TaskLoRa(void);
extern void LoRaWorkStateTran(uint8_t state);
extern void Reset_Wm121(void);
//====================================================================================================
#endif  //LORAFUN_H
