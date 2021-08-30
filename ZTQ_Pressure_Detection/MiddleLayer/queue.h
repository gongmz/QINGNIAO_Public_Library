#ifndef __QUEUE_H__
#define __QUEUE_H__


typedef struct
{
    INT8U state;  //状态
    INT8U event;  //事件
}t_send_data;

typedef struct
{
    t_send_data *base;  //队列起始地址
    INT8U front;  //队头
    INT8U rear;   //队尾
    INT8U array_size;//队列长度
}SqQueue;


extern SqQueue FireQueue;//火警队列
extern SqQueue EventQueue;//其它事件队列


void InitQueue(void);
INT8U QueueLength(const SqQueue *Q );
INT8U QueueIsEmpty( const SqQueue *Q );
INT8U QueueIsFull(const SqQueue *Q );
INT8U EnQueue( SqQueue *Q , t_send_data e );
INT8U DeQueue( SqQueue *Q ,  t_send_data *e );
void clearQueue( SqQueue *Q );

#endif
