#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue Queue;

Queue *queueCreate(int maxSize);
bool queueEmpty(Queue *q);
bool queueFull(Queue *q);
void queuePush(Queue *q, int d);
int queuePop(Queue *q);
int queueView(Queue *q);
void queueDestroy(Queue *q);

#endif