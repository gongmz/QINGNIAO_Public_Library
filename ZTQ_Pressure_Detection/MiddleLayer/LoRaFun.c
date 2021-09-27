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
static uint8_t    send_times = 0;//�װ���ģ��ظ����ط�����
static uint8_t    send_times_2 = 0;//�װ峬ʱδ�յ�����ָ����ط�����
static uint8_t    send_times_3 = 0;//�װ��յ����ط����¼�����ָ����ط�����
static uint8_t    LoRaStep = 0;
/**********************************��������************************************/
void  SetLoRaPrio(void);
void  Send_Device_Type(void);
void  LoRaWorkStateTran(uint8_t state);
void Send_Device_Data(uint8_t Event,uint16_t State);
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
                            strcpy(DataTxBuff,"00\r\nAT+CCLK\r\n");//��ȡʱ��
							StartUartPackageTx();
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
							Send_Device_Data(0x7B,DeviceState);
                            Start4_3Sec();
                        break;

                        case 1:
                            strcpy(DataTxBuff,"00\r\nAT+NSEVENT\r\n");//�����¼�
							StartUartPackageTx();
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
					strcpy(DataTxBuff,"00\r\nAT+NSJOIN\r\n");
					StartUartPackageTx();	
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
                            Send_Device_Data(DeviceEvent,DeviceState);
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
					strcpy(DataTxBuff,"00\r\nAT+NSEVENT\r\n");
					StartUartPackageTx();	
                    Start4_3Sec();
                break;

                case LORA_MSG_RX_OK:
                    send_times=0;
	                Stop4_Sec_Timer(); 
					Start1_7min();
                break;

                case LORA_MSG_SEND_OK://���ػظ����ͳɹ�ָ��
					DeviceEvent=0;
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
					strcpy(DataTxBuff,"00\r\nAT+NSJOIN\r\n");//�����¼�
					StartUartPackageTx();	
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
* �������ƣ�Send_Device_Data
* �������ܣ���������
* �����������
* �����������
* �������أ���
* ʹ��˵����
******************************************************************************/
void Send_Device_Data(uint8_t Event,uint16_t State)
{
		uint8_t i=0;
		float temp;

		DataTxBuff[i++] = '0';
		DataTxBuff[i++] = '0';
		DataTxBuff[i++] = '\r';
		DataTxBuff[i++] = '\n';
		DataTxBuff[i++] = 'A';
		DataTxBuff[i++] = 'T';
		DataTxBuff[i++] = '+';
		DataTxBuff[i++] = 'N';
		DataTxBuff[i++] = 'S';
		DataTxBuff[i++] = 'S';
		DataTxBuff[i++] = 'T';
		DataTxBuff[i++] = 'A';
		DataTxBuff[i++] = 'T';
		DataTxBuff[i++] = 'U';
		DataTxBuff[i++] = 'S';
		DataTxBuff[i++] = '=';
		DataTxBuff[i++] = '0';
		DataTxBuff[i++] = 'x';

		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&Event,1);
		i+=2;

		DataTxBuff[i++] = ',';

		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&State,1);
		i+=2;

		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&State+1,1);
		i+=2;

		temp=((float)PressureValue)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);
		i+=8;


		temp=((float)SysParameter.UnderPreaaureWarn)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);
		i+=8;

		temp=((float)SysParameter.UnderPreaaureAlarm)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);
		i+=8;

		temp=((float)SysParameter.OverPreaaureWarn)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);
		i+=8;

		temp=((float)SysParameter.OverPreaaureAlarm)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);	
		i+=8;							

		temp=((float)SysParameter.Range)/100;
		HexsTochars((uint8_t *)&DataTxBuff[i],(uint8_t *)&temp,4);	
		i+=8;

		DataTxBuff[i++] = '\r';
		DataTxBuff[i++] = '\n';
		DataTxBuff[i++] = '\0';

		StartUartPackageTx();

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
		DataTxBuff[0] = '0';
		DataTxBuff[1] = '0';
		DataTxBuff[2] = '\r';
		DataTxBuff[3] = '\n';
        DataTxBuff[4] = 'A';
        DataTxBuff[5] = 'T';
        DataTxBuff[6] = '+';
        DataTxBuff[7] = 'N';
        DataTxBuff[8] = 'S';
        DataTxBuff[9] = 'C';
        DataTxBuff[10] = 'S';
        DataTxBuff[11] = 'T';
        DataTxBuff[12] = '=';
        DataTxBuff[13] = DEVICE_CPSN + 0x30;
        DataTxBuff[14] = ',';
        DataTxBuff[15] = DEVICE_CLASS/10 + 0x30;
        DataTxBuff[16] = DEVICE_CLASS%10 + 0x30;
        DataTxBuff[17] = ',';
        DataTxBuff[18] = DEVICE_TYPE + 0x30;
        DataTxBuff[19] = ',';
        DataTxBuff[20] = DEVICE_HV + 0x30;
        DataTxBuff[21] = ',';     
        DataTxBuff[22] = DEVICE_SV + 0x30;        
        DataTxBuff[23] = ',';     
        DataTxBuff[24] = DEVICE_NET + 0x30;      
        DataTxBuff[25] = '\r';
        DataTxBuff[26] = '\n';
        DataTxBuff[27] = '\0';
		
        StartUartPackageTx();
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

