/**
 * @file Linkedlist.c
 * @Brief  linked list interface source
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-22
 */


#include <stdlib.h>
#include "../Common.h"
#include "Linkedlist.h"
#include "../util/Log.h"


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_insert insert node to the list
 *
 * @Param common data commont struct
 * @Param element the node that need to be inserted
 *
 * @Returns   0 means successe;other means error
 */
/* ----------------------------------------------------------------------------*/
static int llist_insert(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return -1;
    }

    /**
     *new a linked node and add element to it
     */ 
    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (node == NULL){
	ERROR("pointer is null!");
	return -1;
    }
    node->element = element;
    node->next = NULL;
    
    if (list->first != NULL){
    /**
     *add a new node to the end of list
     */ 
	list->last->next = node;
	list->last = node;
    }else{
    /**
     *add first node to the list
     */ 
	list->first = node;
	list->last = node;
    }
    list->size++;

    return 0;
}

















