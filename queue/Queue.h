/**
 * @file Queue.h
 * @Brief  queue interfaces
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-31
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct QueueNode{
    void *element;
    struct QueueNode *next;
}QueueNode;

typedef struct Queue{
    /**
     * point the head of the queue
     */
    QueueNode *head;
    /**
     * point the tail of the queue
     */
    QueueNode *tail;
    /**
     * point the spare node list
     */
    QueueNode *spare;
    /**
     * size of the queue
     */
    int queue_size;
    /**
     * the number of all the node(used and unused)
     */
    int node_count;
}Queue;

#define QUEUE_EMPTY(queue) (queue->head == NULL)
#define QUEUE_INIT {\
    .head = NULL, \
    .tail = NULL, \
    .spare = NULL, \
    .queue_size = 0, \
    .node_count = 0 \
}

typedef void (*handle)(void *element);

int queue_clear(Queue *queue, handle destroy_node);
int queue_delete(Queue *queue, handle destroy_node);
int queue_iterate(Queue *queue, handle handle_iteration);

int queue_in(Queue *queue, void *element);
void* queue_out(Queue *queue);

#endif
