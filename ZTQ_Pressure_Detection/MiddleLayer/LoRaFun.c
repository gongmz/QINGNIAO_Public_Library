/***************************************************************************************
****************************************************************************************
* FILE		: LoRaFun.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/
/**********************************ͷ�ļ�**************************************/
#include "includes.h"
/**********************************�궨������**********************************/
#define  MAX_RESEND_TIMES     10
#define  MAX_RESEND_TIMES_3   10
/**********************************�ṹ������**********************************/

/**********************************��������************************************/
uint8_t  LoRaState = LORA_ST_POWERON;
uint8_t EnterShortKeyNum;
t_send_data send_data;
static uint8_t    send_times = 0;//�װ���ģ��ظ����ط�����
static uint8_t    send_times_2 = 0;//�װ峬ʱδ�յ�����ָ����ط�����
static uint8_t    send_times_3 = 0;//�װ��յ����ط����¼�����ָ����ط�����
static uint8_t    LoRaStep = 0;
/**********************************��������************************************/
void  SetLoRaPrio(void);
void  Send_Device_Type(void);
void  LoRaWorkStateTran(uint8_t state);
/****************************************************************************** 
* �������ƣ�TaskLoRa
* �������ܣ�ͨ������
* �����������
* �����������
* �������أ���
* ʹ��˵����
******************************************************************************/
void TaskLoRa(void)
{
    uint8_t sig;

    if (Msg[LORAFUN_PRIO - 1] & LORA_MSG_ENTRY) 
	{
        Msg[LORAFUN_PRIO - 1] &= 0x7F;
        sig = LORA_MSG_ENTRY;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & LORA_MSG_RX_OK) 
    {
        Msg[LORAFUN_PRIO - 1] &= 0xBF;
        sig = LORA_MSG_RX_OK;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & 	LORA_MSG_TMOUT1)
	{
        Msg[LORAFUN_PRIO - 1] &= 0xDF;
        sig = LORA_MSG_TMOUT1;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & LORA_MSG_SEND_OK) 
    {
        Msg[LORAFUN_PRIO - 1] &= 0xEF;
        sig = LORA_MSG_SEND_OK;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & 	LORA_MSG_SEND_ERROR)
	{
        Msg[LORAFUN_PRIO - 1] &= 0xF7;
        sig = LORA_MSG_SEND_ERROR;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & 	LORA_MSG_NSJOIN)
	{
        Msg[LORAFUN_PRIO - 1] &= 0xFB;
        sig = LORA_MSG_NSJOIN;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & LORA_MSG_TMOUT2) 
    {
        Msg[LORAFUN_PRIO - 1] &= 0xFD;
        sig = LORA_MSG_TMOUT2;
    } 
	else if (Msg[LORAFUN_PRIO - 1] & 	LORA_MSG_SEND_EVENT)
	{
        Msg[LORAFUN_PRIO - 1] &= 0xFE;
        sig = LORA_MSG_SEND_EVENT;
    } 	
	else
    {
        sig = Msg[LORAFUN_PRIO - 1];
        Msg[LORAFUN_PRIO - 1] = 0;
    }
    switch(LoRaState)
    {
        case LORA_ST_POWERON:
            switch(sig)
            {
                case LORA_MSG_ENTRY:
                    switch(LoRaStep)
                    {
                        case 0:
                            Send_Device_Type();
                            Start4_3Sec();
                        break;

                        case 1:
                            UartPackageTx("00\r\nAT+CCLK\r\n");//��ȡʱ��
                            Start4_3Sec();
                        break;
                        default:break;
                    }
                break;

                case LORA_MSG_TMOUT1:
                    send_times++;
                    if(send_times>=MAX_RESEND_TIMES)
                    {
                        LoRaStep = 0;
                        send_times=0;
                        LoRaWorkStateTran(LORA_ST_IDLE);
                    }
                    else
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                break;

                case LORA_MSG_RX_OK:
                    send_times=0;
                    Stop4_Sec_Timer();
                    LoRaStep++;
                    if(LoRaStep == 2)  
                    {
                        LoRaWorkStateTran(LORA_ST_IDLE);
                        LoRaStep = 0;
                    }
                    else
                    {
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                    }
                    
                break;
                default:break;
            }
        break;
			
       case LORA_ST_SELFCHECK:
            switch(sig)
            {
                case LORA_MSG_ENTRY:
                    switch(LoRaStep)
                    {
                        case 0:
                            UartPackageTx("00\r\nAT+NSSTATUS=0x7B,00\r\n");
                            Start4_3Sec();
                        break;

                        case 1:
                            UartPackageTx("00\r\nAT+NSEVENT\r\n");
                            Start4_3Sec();
                        break;
                        default:break;
                    }
                break;

                case LORA_MSG_TMOUT1:
                    send_times++;
                    if(send_times>=MAX_RESEND_TIMES)
                    {
                        LoRaStep = 0;
                        send_times=0;
                        LoRaWorkStateTran(LORA_ST_IDLE);
                    }
                    else
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                break;

                case LORA_MSG_RX_OK:
                    send_times=0;
                    Stop4_Sec_Timer();
                    LoRaStep++;
                    if(LoRaStep == 2)  
                    {
                        LoRaWorkStateTran(LORA_ST_IDLE);
                        LoRaStep = 0;
                    }
                    else
                    {
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                    }
                    
                break;
                default:break;
            }
        break;
        
        case LORA_ST_IDLE:
            switch(sig)
            {
                case LORA_MSG_ENTRY: 
                    LoRaStep = 0;
                break;

                case LORA_MSG_NSJOIN:
                    UartPackageTx("00\r\nAT+NSJOIN\r\n");//�����¼�
                break;

                case LORA_MSG_SEND_EVENT:
                    LoRaWorkStateTran(LORA_ST_SETSTATE);
                break;
                default:break;
            }
        break;

        case LORA_ST_SETSTATE://����ģ��״̬�ͻ�����
            switch(sig)
            {
                case LORA_MSG_ENTRY:
                    switch(LoRaStep)
                    {
                         case 0:
                            Send_Device_Type();
                            Start4_3Sec();
                        break;

                        case 1:
                            DataTxBuff[0] = 'A';
                            DataTxBuff[1] = 'T';
                            DataTxBuff[2] = '+';
                            DataTxBuff[3] = 'N';
                            DataTxBuff[4] = 'S';
                            DataTxBuff[5] = 'S';
                            DataTxBuff[6] = 'T';
                            DataTxBuff[7] = 'A';
                            DataTxBuff[8] = 'T';
                            DataTxBuff[9] = 'U';
                            DataTxBuff[10] = 'S';
                            DataTxBuff[11] = '=';
                            DataTxBuff[12] = '0';
                            DataTxBuff[13] = 'x';

                            HexsTochars(&DataTxBuff[14],&send_data.event,1);

                            DataTxBuff[16] = ',';

                            HexsTochars(&DataTxBuff[17],&send_data.state,1);
						
                            HexsTochars(&DataTxBuff[19],(uint8_t *)&PressureValue,2);
               
                            DataTxBuff[23] = '\r';
                            DataTxBuff[24] = '\n';
                            
                            FUN_USART_SENDPACKET(&DataTxBuff[0],25);//�����¼�
                            Start4_3Sec();
                        break;

                        default:break;
                    }
                break;

                case LORA_MSG_RX_OK:
                    send_times=0;
                    Stop4_Sec_Timer();
                    LoRaStep++;
                    if(LoRaStep == 2)  
                    {
                        LoRaWorkStateTran(LORA_ST_SEND_EVENT);
                        LoRaStep = 0;
                    }
                    else
                    {
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                    }
                break;

                case LORA_MSG_TMOUT1:
                    send_times++;
                    if(send_times>=MAX_RESEND_TIMES)//��λ
                    {
						LoRaWorkStateTran(LORA_ST_IDLE);
                    }else
                    {
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                    }
                break;
                default:break;
            }
        break;

        case LORA_ST_SEND_EVENT:
        {
            switch(sig)
            {
                case LORA_MSG_ENTRY:
                    UartPackageTx("00\r\nAT+NSEVENT\r\n");//�����¼�
                    Start4_3Sec();
                break;

                case LORA_MSG_RX_OK:
                    send_times=0;
	                Stop4_Sec_Timer(); 
					Start1_7min();
                break;

                case LORA_MSG_SEND_OK://���ػظ����ͳɹ�ָ��
					send_data.event=0;
                    send_times_2=0;
                    send_times_3=0;
	                LoRaWorkStateTran(LORA_ST_IDLE);
                    Stop1_min_timer();
                break;

                case LORA_MSG_TMOUT1:
                    send_times++;
                    if(send_times >= MAX_RESEND_TIMES)
                    {
						send_times=0;
						LoRaWorkStateTran(LORA_ST_IDLE);
                    }
                    else
                    {
                        MsgPost(LORAFUN_PRIO,LORA_MSG_ENTRY);
                    }
                break;

                case LORA_MSG_NSJOIN:
                    UartPackageTx("00\r\nAT+NSJOIN\r\n");//�����¼�
                break;
                
                case LORA_MSG_SEND_ERROR:
                    send_times_3++;
                    Stop1_min_timer();
                    if(send_times_3 >= MAX_RESEND_TIMES_3)
                    {
                        send_times_3=0;
                        LoRaWorkStateTran(LORA_ST_IDLE);
                    }
                    else
                    {
                        LoRaWorkStateTran(LORA_ST_SETSTATE);
                    }
                break;

                case LORA_MSG_TMOUT2:
                    send_times_2++;
                    Stop1_min_timer();
                    if(send_times_2 >= MAX_RESEND_TIMES)
                    {
                        send_times_2=0;
                        LoRaWorkStateTran(LORA_ST_IDLE);
                    }
                    else
                    {
                        LoRaWorkStateTran(LORA_ST_SETSTATE);
                    }
                break;

                default:break;
            }
        }
        break;
        default:break;
    }

    SetLoRaPrio();
}   
/****************************************************************************** 
* �������ƣ�Send_Device_Type
* �������ܣ�����ģ���豸����
* �����������
* �����������
* �������أ���
* ʹ��˵����
******************************************************************************/
void Send_Device_Type(void)
{
        DataTxBuff[0] = 'A';
        DataTxBuff[1] = 'T';
        DataTxBuff[2] = '+';
        DataTxBuff[3] = 'N';
        DataTxBuff[4] = 'S';
        DataTxBuff[5] = 'C';
        DataTxBuff[6] = 'S';
        DataTxBuff[7] = 'T';
        DataTxBuff[8] = '=';
        DataTxBuff[9] = DEVICE_CPSN + 0x30;
        DataTxBuff[10] = ',';
        DataTxBuff[11] = DEVICE_CLASS/10 + 0x30;
        DataTxBuff[12] = DEVICE_CLASS%10 + 0x30;
        DataTxBuff[13] = ',';
        DataTxBuff[14] = DEVICE_TYPE + 0x30;
        DataTxBuff[15] = ',';
        DataTxBuff[16] = DEVICE_HV + 0x30;
        DataTxBuff[17] = ',';     
        DataTxBuff[18] = DEVICE_SV + 0x30;        
        DataTxBuff[19] = ',';     
        DataTxBuff[20] = DEVICE_NET + 0x30;      
        DataTxBuff[21] = '\r';
        DataTxBuff[22] = '\n';

        FUN_USART_SENDPACKET(&DataTxBuff[0],23);//�����豸����
}
/****************************************************************************** 
* �������ƣ�Reset_Wm121
* �������ܣ���λģ��
* �����������
* �����������
* �������أ���
* ʹ��˵����
******************************************************************************/
void Reset_Wm121(void)
{
	;
}
void SetLoRaPrio(void)
{
    if (Msg[LORAFUN_PRIO - 1] != 0)
		{
        OS_ENTER_CRITICAL();
        ThreadSet(LORAFUN_PRIO);
        OS_EXIT_CRITICAL();
    }
}
void  LoRaWorkStateTran(uint8_t state)
{
    LoRaState = state;
    MsgPost(LORAFUN_PRIO, LORA_MSG_ENTRY);
}

