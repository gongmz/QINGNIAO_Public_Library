#ifndef __QUEUE_H__
#define __QUEUE_H__


typedef struct
{
    INT8U state;  //״̬
    INT8U event;  //�¼�
}t_send_data;

typedef struct
{
    t_send_data *base;  //������ʼ��ַ
    INT8U front;  //��ͷ
    INT8U rear;   //��β
    INT8U array_size;//���г���
}SqQueue;


extern SqQueue FireQueue;//�𾯶���
extern SqQueue EventQueue;//�����¼�����


void InitQueue(void);
INT8U QueueLength(const SqQueue *Q );
INT8U QueueIsEmpty( const SqQueue *Q );
INT8U QueueIsFull(const SqQueue *Q );
INT8U EnQueue( SqQueue *Q , t_send_data e );
INT8U DeQueue( SqQueue *Q ,  t_send_data *e );
void clearQueue( SqQueue *Q );

#endif
