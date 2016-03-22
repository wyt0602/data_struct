/**
 * @file Linkedlist.h
 * @Brief  define the struct about linked list
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-22
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "Common.h"

/**
 * Represent a node
 */
typedef struct LinkedNode{
    /**
     * Pointer to the node value
     */
    void *element;

    /**
     * Pointer to the next node
     */ 
    struct LinkedNode *next;
}LinkedNode;

/**
 * Represent a linked list
 */
typedef struct LinkedList{
    /**
     * Pointer to the first node in the list
     */
    LinkedNode *first; 

    /**
     * Pointer to the last node in the list
     */
    LinkedNode *last;

    /**
     * the number of node in the list
     */
    int size;
}LinkedList;

int llist_new(DataCommon *common);
int llist_delete(DataCommon *common);

#endif
