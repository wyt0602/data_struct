/**
 * @file DLinkedlist.h
 * @Brief  double linked list header
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-28
 */

#ifndef DLINKED_LIST_H_
#define DLINKED_LIST_H_

#include "Common.h"

typedef struct DLinkedNode{
    void *element;
    struct DLinkedNode *previous;
    struct DLinkedNode *next;
}DLinkedNode;

typedef struct DLinkedList{
    DLinkedNode *first;
    DLinkedNode *last;
    int size;
}DLinkedList;

int dllist_new(DataCommon *common);
int dllist_delete(DataCommon *common);

#endif
