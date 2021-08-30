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

#define FIRE_QUEUE_SIZE 10           //火警队列空间
#define FIRE_ARRAY_SIZE (FIRE_QUEUE_SIZE+1)   //预留1位用来判断满或空
#define FIRE_QUEUE_TYPE t_send_data

#define EVENT_QUEUE_SIZE 5               //其他事件队列空间
#define EVENT_ARRAY_SIZE (EVENT_QUEUE_SIZE+1)//预留1位用来判断满或空
#define EVENT_QUEUE_TYPE t_send_data

SqQueue FireQueue;//火警队列
SqQueue EventQueue;//其它事件队列

static FIRE_QUEUE_TYPE queue1[FIRE_ARRAY_SIZE];
static EVENT_QUEUE_TYPE queue2[EVENT_ARRAY_SIZE];

/*
**队列初始化
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
**清空队列，暂未使用
*/
void clearQueue( SqQueue *Q )
{
    memset(queue,0,sizeof(queue));//清空队列
    Q->front = 1;
    Q->rear = 0;
}
/*
**获取队列长度
*/
INT8U QueueLength( const SqQueue *Q )
{
        return (Q->rear - Q->front + Q->array_size + 1)%Q->array_size;
}
/*
**判断队列是否为空
*/
INT8U QueueIsEmpty( const SqQueue *Q )
{
        return (Q->rear + 1)%Q->array_size==Q->front;
}
/*
**判断队列是否为满
*/
INT8U QueueIsFull( const SqQueue *Q )
{
        return (Q->rear + 2)%Q->array_size==Q->front;
}
/*
**插入队列
*/
INT8U EnQueue( SqQueue *Q , t_send_data e )
{
     if( (Q->rear + 2) % Q->array_size == Q->front )//判断是否为满
         return 0;
     Q->rear = (Q->rear + 1)%Q->array_size;//
     Q->base[Q->rear] = e;
     return 1;
}
/*
**从队列取出元素
*/
INT8U DeQueue( SqQueue *Q ,  t_send_data *e )
{
   if( (Q->rear + 1) % Q->array_size == Q->front )//判断是否为空
         return 0;
   *e = Q->base[Q->front];
   Q->front = (Q->front + 1)%Q->array_size;
   return 1;
}
