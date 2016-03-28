/**
 * @file Linkedlist.c
 * @Brief  linked list interface source
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-22
 */


#include <stdlib.h>
#include "Common.h"
#include "Linkedlist.h"
#include "util/Log.h"


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_insert insert node to the list
 *
 * @Param common data commont struct
 * @Param element the node that need to be inserted
 *
 * @Returns   0 is OK;other is failed
 */
/* ----------------------------------------------------------------------------*/
static int llist_insert(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return -1;
    }

    /**
     *create a linked node and add element to it
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


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_remove:remove a node from the list
 *
 * @Param common data common struct
 * @Param element the node's information that needs to be removed
 *
 * @Returns   0 is OK;other is failed
 */
/* ----------------------------------------------------------------------------*/
static int llist_remove(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return -1;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *cur = list->first;
    LinkedNode *pre = NULL;

    while(cur){
	/**
	 *match the node 
	 */ 
	if ((common->remove_match)(cur->element, element) == 0){
	    /**
	     *remove the middle node 
	     */ 
	    if ((cur != list->first) && (cur != list->last)){
		pre->next = cur->next;
	    }

	    /**
	     *remove the first node 
	     */ 
	    if (cur == list->first){
		list->first = cur->next;
	    }

	    /**
	     *remove the last node 
	     */ 
	    if (cur == list->last){
		if (pre != NULL)
		    pre->next = NULL;
		list->last = pre;
	    }

	    common->destroy_node(cur->element);
	    cur->element = NULL;
	    cur->next = NULL;
	    free(cur);
	    list->size--;
	    return 0;
	}

	pre = cur;
	cur = cur->next;
    }

    INFO("can not match a node!");
    return -1;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_search get the node that user needs
 *
 * @Param common data common struct
 * @Param element the index of the node
 *
 * @Returns   NULL means no one; other is the address of the matched node
 */
/* ----------------------------------------------------------------------------*/
static void* llist_search(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return NULL;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *node = list->first;

    while(node){
	if((common->search_match)(node->element, element) == 0)
	    return node->element;
	else
	    node = node->next;
    }

    INFO("no matched node!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_alter alter the matched node
 *
 * @Param common data common struct
 * @Param element the searched node's information
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
static int llist_alter(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return -1;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *node = list->first;

    while(node){
	if ((common->alter_match)(node->element, element) == 0)
	    return 0;
	else
	    node = node->next;
    }

    INFO("no matched node!");
    return -1;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_prior return the prior node of the matched one
 *
 * @Param common data common struct
 * @Param element match information
 *
 * @Returns   NULL means can not find the matched one;other is the address of 
 * 	      the node
 */
/* ----------------------------------------------------------------------------*/
static void* llist_prior(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return NULL;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *cur = list->first;
    LinkedNode *pre = NULL;

    while(cur){
	if((common->search_match)(cur->element, element) == 0)
	{
	    if (pre == NULL)
		return NULL;
	    else
		return pre->element;
	}else{
	    pre = cur;
	    cur = cur->next;
	}
    }

    INFO("no matched one!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_next return the next node of the matched node
 *
 * @Param common data common struct
 * @Param element match information
 *
 * @Returns   NULL means can not find the matched one;other is the address of 
 *            the node
 */
/* ----------------------------------------------------------------------------*/
static void* llist_next(DataCommon *common, void * element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("pointer is null!");
	return NULL;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *cur = list->first;

    while(cur){
	if((common->search_match)(cur->element, element) == 0){
	    if (cur->next == NULL)
		return NULL;
	    else
		return cur->next->element;
	}else{
	    cur = cur->next;
	}
    }

    INFO("no matched one!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_iterate iterate the list
 *
 * @Param common data common struct
 *
 * @Returns   0 is OK;other is failed
 */
/* ----------------------------------------------------------------------------*/
static int llist_iterate(DataCommon *common)
{
    if (common == NULL){
	ERROR("pointer is null!");
	return -1;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *node = list->first;

    while(node){
	if ((common->handle_iteration)(node->element) == 0)
	    node = node->next;
	else{
	    ERROR("handle_iteration function error!");
	    return -1;
	}
    }

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_size return the number of the node
 *
 * @Param common data common struct
 *
 * @Returns   -1 is failed; >=0 is the number of the node
 */
/* ----------------------------------------------------------------------------*/
static int llist_size(DataCommon *common)
{
    if (common == NULL){
	ERROR("pointer is null!");
	return -1;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);

    return list->size;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_clear destroy the list
 *
 * @Param common data common struct
 *
 * @Returns   -1 is failed; >=0 is the number of the node that is destroyed
 */
/* ----------------------------------------------------------------------------*/
static int llist_clear(DataCommon *common)
{
    if (common == NULL){
	ERROR("pointer is null!");
	return -1;
    }

    LinkedList *list = (LinkedList*)(common->linked_type);
    LinkedNode *node = list->first;
    LinkedNode *temp = NULL;
    int ret = 0;

    while(node){
	temp = node;
	node = node->next;

	common->destroy_node(temp->element);
	temp->element = NULL;
	temp->next = NULL;
	free(temp);

	ret++;
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_new create a list, initial datacommon struct
 *
 * @Param common data common struct
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
int llist_new(DataCommon *common)
{
    if (common == NULL){
	ERROR("pointer is null!");
	return -1;
    }

    /**
     * check the user-defined functhion
     */
    int handle_check = common->remove_match \
		       &&common->search_match \
		       &&common->alter_match \
		       &&common->destroy_node \
		       &&common->handle_iteration;
    if (handle_check == 0){
	ERROR("missed user defined function!");
	return -1;
    }

    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL){
	ERROR("malloc error!");
	return -1;
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    common->linked_type = list;
    common->insert = llist_insert;
    common->remove = llist_remove;
    common->search = llist_search;
    common->alter = llist_alter;
    common->prior = llist_prior;
    common->next = llist_next;
    common->iterate = llist_iterate;
    common->size = llist_size;
    common->clear = llist_clear;

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  llist_delete delete the list
 *
 * @Param common data common struct
 *
 * @Returns   -1 is failed; >=0 is the number of node 
 */
/* ----------------------------------------------------------------------------*/
int llist_delete(DataCommon *common)
{
    if (common == NULL){
	ERROR("pointer is null!");
	return -1;
    }

    int ret = llist_clear(common);

    LinkedList *list = (LinkedList*)(common->linked_type);
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    free(list);

    return ret;
}
