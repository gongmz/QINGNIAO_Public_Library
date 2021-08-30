/***************************************************************************************
****************************************************************************************
* FILE		: queue.c
* Description	: 
*			  
* Copyright (c) 2021 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   
****************************************************************************************
****************************************************************************************/
#include "includes.h"

#define FIRE_QUEUE_SIZE 10           //�𾯶��пռ�
#define FIRE_ARRAY_SIZE (FIRE_QUEUE_SIZE+1)   //Ԥ��1λ�����ж������
#define FIRE_QUEUE_TYPE t_send_data

#define EVENT_QUEUE_SIZE 5               //�����¼����пռ�
#define EVENT_ARRAY_SIZE (EVENT_QUEUE_SIZE+1)//Ԥ��1λ�����ж������
#define EVENT_QUEUE_TYPE t_send_data

SqQueue FireQueue;//�𾯶���
SqQueue EventQueue;//�����¼�����

static FIRE_QUEUE_TYPE queue1[FIRE_ARRAY_SIZE];
static EVENT_QUEUE_TYPE queue2[EVENT_ARRAY_SIZE];

/*
**���г�ʼ��
*/
void InitQueue(void)
{
        FireQueue.base = queue1;
        FireQueue.front = 1;
        FireQueue.rear = 0;
        FireQueue.array_size = FIRE_ARRAY_SIZE;

        EventQueue.base = queue2;
        EventQueue.front = 1;
        EventQueue.rear = 0;
        EventQueue.array_size = EVENT_ARRAY_SIZE;
}
/*
**��ն��У���δʹ��
*/
void clearQueue( SqQueue *Q )
{
    memset(queue,0,sizeof(queue));//��ն���
    Q->front = 1;
    Q->rear = 0;
}
/*
**��ȡ���г���
*/
INT8U QueueLength( const SqQueue *Q )
{
        return (Q->rear - Q->front + Q->array_size + 1)%Q->array_size;
}
/*
**�ж϶����Ƿ�Ϊ��
*/
INT8U QueueIsEmpty( const SqQueue *Q )
{
        return (Q->rear + 1)%Q->array_size==Q->front;
}
/*
**�ж϶����Ƿ�Ϊ��
*/
INT8U QueueIsFull( const SqQueue *Q )
{
        return (Q->rear + 2)%Q->array_size==Q->front;
}
/*
**�������
*/
INT8U EnQueue( SqQueue *Q , t_send_data e )
{
     if( (Q->rear + 2) % Q->array_size == Q->front )//�ж��Ƿ�Ϊ��
         return 0;
     Q->rear = (Q->rear + 1)%Q->array_size;//
     Q->base[Q->rear] = e;
     return 1;
}
/*
**�Ӷ���ȡ��Ԫ��
*/
INT8U DeQueue( SqQueue *Q ,  t_send_data *e )
{
   if( (Q->rear + 1) % Q->array_size == Q->front )//�ж��Ƿ�Ϊ��
         return 0;
   *e = Q->base[Q->front];
   Q->front = (Q->front + 1)%Q->array_size;
   return 1;
}
