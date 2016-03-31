/**
 * @file Queue.c
 * @Brief  queue implementation
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-31
 */
#include <stdlib.h>

#include "Queue.h"
#include "util/Log.h"


/* --------------------------------------------------------------------------*/
/**
 * @Brief  queue_in Append a node to the queue 
 *
 * @Param queue Queue struct
 * @Param element The value of a QueueNode
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
int queue_in(Queue *queue, void *element)
{
    if (queue == NULL || element == NULL){
	ERROR("Null pointer!");
	return -1;
    }

    /**
     * if spare list is NULL, malloc a node;
     * else get a node from the spare list
     */ 
    QueueNode *node = NULL;
    if (queue->spare == NULL){
	node = (QueueNode*)malloc(sizeof(QueueNode));
	if (node == NULL){
	    ERROR("malloc error!");
	    return -1;
	}
	node->element = element;
	node->next = NULL;

	queue->node_count++;
    }else{
	node = queue->spare;
	queue->spare = node->next;
	node->element = element;
	node->next = NULL;
    }

    /**
     * if queue is empty, insert node to the head of queue;
     * else insert the node to the tail of queue.
     */ 
    if (QUEUE_EMPTY(queue)){
	queue->head = node;
	queue->tail = node;
    }else{
	queue->tail->next = node;
	queue->tail = node;
    }

    queue->queue_size++;

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  queue_out Out a node from the head of the queue
 *
 * @Param queue Queue struct
 *
 * @Returns   NULL is failed; other is the address of element
 */
/* ----------------------------------------------------------------------------*/
void* queue_out(Queue *queue)
{
    if (queue == NULL){
	ERROR("Null pointer!");
	return NULL;
    }

    if (QUEUE_EMPTY(queue)){
	INFO("Queue is empty!");
	return NULL;
    }

    void *ret = queue->head->element;
    QueueNode *node = queue->head;

    /**
     * only one node in the queue or not
     */ 
    if (queue->tail == node){
	queue->head = NULL;
	queue->tail = NULL;
    }else{
	queue->head = node->next;
    }
    queue->queue_size--;

    /**
     * insert one node into the spare list(in the head)
     */ 
    node->element = NULL;
    node->next = queue->spare;
    queue->spare = node;

    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  queue_clear Clear the queue list
 *
 * @Param queue Queue struct
 * @Param destroy_node Destroy node function
 *
 * @Returns   -1 is failed; other is the count of the node in the queue
 */
/* ----------------------------------------------------------------------------*/
int queue_clear(Queue *queue, handle destroy_node)
{
    if (queue == NULL){
	ERROR("Null pointer!");
	return -1;
    }

    if (QUEUE_EMPTY(queue)){
	INFO("Queue is empty!");
	return 0;
    }

    QueueNode *node = queue->head;
    int ret = 0;

    /**
     * if destroy_node function is not null, free element
     */ 
    if (destroy_node){
	while (node){
	    destroy_node(node->element);
	    node->element = NULL;
	    node = node->next;
	    ret++;
	}
    }

    /**
     * add the queue list to the spare list
     */ 
    queue->tail->next = queue->spare;
    queue->spare = queue->head;
    queue->tail = NULL;
    queue->head = NULL;

    ret = ret != 0 ? ret : queue->queue_size;
    queue->queue_size = 0;

    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  queue_delete Delete the queue
 *
 * @Param queue Queue struct
 * @Param destroy_node Destroy funcion
 *
 * @Returns   -1 is failed; other is the number of all the node
 */
/* ----------------------------------------------------------------------------*/
int queue_delete(Queue *queue, handle destroy_node)
{
    if (queue == NULL){
	ERROR("Null pointer!");
	return -1;
    }

    int ret = 0;
    if (!QUEUE_EMPTY(queue))
	queue_clear(queue, destroy_node);

    /**
     * free spare list
     */ 
    QueueNode *node = queue->spare;
    QueueNode *temp;
    while (node){
	temp = node;
	node = node->next;
	temp->next = NULL;
	free(temp);
    }

    ret = queue->node_count;
    queue->spare = NULL;
    queue->node_count = 0;

    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  queue_iterate Iterate the queue
 *
 * @Param queue Queue struct
 * @Param handle_iteration iterate function
 *
 * @Returns   -1 is failed; other is the number of node in the queue
 */
/* ----------------------------------------------------------------------------*/
int queue_iterate(Queue *queue, handle handle_iteration)
{
    if (queue == NULL || handle_iteration == NULL){
	ERROR("Null pointer!");
	return -1;
    }

    int ret = 0;
    QueueNode *node = queue->head;
    while (node){
	handle_iteration(node->element);
	node = node->next;
	ret++;
    }

    return ret;
}
