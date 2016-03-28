/**
 * @file DLinkedlist.c
 * @Brief  Double linked list implementation.
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-28
 */

#include <stdlib.h>

#include "DLinkedlist.h"
#include "Common.h"
#include "util/Log.h"


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_insert Insert a node to the list
 *
 * @Param common Data common struct
 * @Param element The node's value
 *
 * @Returns   0 is OK;other is failed
 */
/* ----------------------------------------------------------------------------*/
static int dllist_insert(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return -1;
    }

    /**
     * Create a new linked node and initial it
     */
    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = (DLinkedNode*)malloc(sizeof(DLinkedNode));
    if (node == NULL){
	ERROR("malloc failed!");
	return -1;
    }
    node->element = element;
    node->previous = NULL;
    node->next = NULL;

    if (list->first != NULL){
	/**
	 * Add a new linked node to the end of the list
	 */
	list->last->next = node;
	node->previous = list->last;
	list->last = node;
    }else{
	/**
	 * Add the first node to the list
	 */
	list->first = node;
	list->last = node;
    }

    list->size++;
    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_remove Remove a node from the list
 *
 * @Param common Data common struct
 * @Param element The node's information that need to be removed
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
static int dllist_remove(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return -1;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	/**
	 * Match the node
	 */ 
	if (common->remove_match(node->element, element) == 0){
	    /**
	     * Remove the middle node
	     */ 
	    if ((node != list->first) && (node != list->last)){
		node->previous->next = node->next;
		node->next->previous = node->previous;
	    }

	    /**
	     * Remove the first node
	     */ 
	    if (node == list->first){
		if (node->next != NULL)
		    node->next->previous = NULL;
		list->first = node->next;
	    }

	    /**
	     * Remove the last node
	     */ 
	    if (node == list->last){
		if (node->previous != NULL)
		    node->previous->next = NULL;
		list->last = node->previous;
	    }

	    /**
	     * Destroy node
	     */ 
	    common->destroy_node(node->element);
	    node->element = NULL;
	    node->previous = NULL;
	    node->next = NULL;
	    free(node);

	    list->size--;
	    return 0;
	}

	node = node->next;
    }

    INFO("no matched node!");
    return -1;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_search Search a node from the list
 *
 * @Param common Data common struct
 * @Param element The node's information
 *
 * @Returns   NULL is failed; other is the node's address
 */
/* ----------------------------------------------------------------------------*/
static void* dllist_search(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return NULL;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	if (common->search_match(node->element, element) == 0)
	    return node->element;
	node = node->next;
    }

    INFO("no matched node!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_alter Alter a node
 *
 * @Param common Data common struct
 * @Param element the node's information
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
static int dllist_alter(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return -1;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	if (common->alter_match(node->element, element) == 0)
	    return 0;
	else
	    node = node->next;
    }

    INFO("no matched node!");
    return -1;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_prior Find the node's previous node
 *
 * @Param common Data common struct
 * @Param element the node's information
 *
 * @Returns   NULL is failed; other is the node's address
 */
/* ----------------------------------------------------------------------------*/
static void* dllist_prior(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return NULL;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	if (common->search_match(node->element, element) == 0){
	    if (node->previous != NULL)
		return node->previous->element;
	    else
		return NULL;
	}else
	    node = node->next;
    }

    INFO("no matched node!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_next Find the node's next node
 *
 * @Param common Data common struct
 * @Param element The node's information
 *
 * @Returns   NULL is failed; other is the node's address
 */
/* ----------------------------------------------------------------------------*/
static void* dllist_next(DataCommon *common, void *element)
{
    if ((common == NULL) || (element == NULL)){
	ERROR("null pointer!");
	return NULL;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	if (common->search_match(node->element, element) == 0){
	    if (node->next != NULL)
		return node->next->element;
	    else
		return NULL;
	}else
	    node = node->next;
    }

    INFO("no matched node!");
    return NULL;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_iterate Iterate the list
 *
 * @Param common Data common struct
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
static int dllist_iterate(DataCommon *common)
{
    if (common == NULL){
	ERROR("null pointer!");
	return -1;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;

    while (node){
	if (common->handle_iteration(node->element) == 0)
	    node = node->next;
	else{
	    ERROR("handle iteration error!");
	    return -1;
	}
    }
    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_size Return the list's size
 *
 * @Param common Data common struct
 *
 * @Returns   -1 is failed; >=0 is the number of list
 */
/* ----------------------------------------------------------------------------*/
static int dllist_size(DataCommon *common)
{
    if (common == NULL){
	ERROR("null pointer!");
	return -1;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);

    return list->size;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_clear Delete all node in the list
 *
 * @Param common Data common struct
 *
 * @Returns -1 is failed; >=0 is the number of node that is destroyed   
 */
/* ----------------------------------------------------------------------------*/
static int dllist_clear(DataCommon *common)
{
    if (common == NULL){
	ERROR("null pointer!");
	return -1;
    }

    DLinkedList *list = (DLinkedList*)(common->linked_type);
    DLinkedNode *node = list->first;
    DLinkedNode *temp = NULL;
    int ret = 0;

    while (node){
	temp = node;
	node = node->next;

	common->destroy_node(temp->element);
	temp->element = NULL;
	temp->previous = NULL;
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
 * @Brief  dllist_new Create a double linked list and initial it
 *  
 * @Param common Data common struct
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
int dllist_new(DataCommon *common)
{
    if (common == NULL){
	ERROR("NULL pointer!");
	return -1;
    }

    /**
     * check the user-defined function
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

    /**
     * create a double linked list struct and initial it
     */ 
    DLinkedList *list = (DLinkedList*)malloc(sizeof(DLinkedList));
    if (list == NULL){
	ERROR("malloc error!");
	return -1;
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    /**
     * initial DataCommon struct
     */ 
    common->linked_type = list;
    common->insert = dllist_insert;
    common->remove = dllist_remove;
    common->search = dllist_search;
    common->alter = dllist_alter;
    common->prior = dllist_prior;
    common->next = dllist_next;
    common->iterate = dllist_iterate;
    common->size = dllist_size;
    common->clear = dllist_clear;

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  dllist_delete Delete the list
 *
 * @Param common Data common struct
 *
 * @Returns   -1 is failed; >=0 is the number of node
 */
/* ----------------------------------------------------------------------------*/
int dllist_delete(DataCommon *common)
{
    if (common == NULL){
	ERROR("NULL pointer!");
	return -1;
    }

    int ret = dllist_clear(common);
    DLinkedList *list = (DLinkedList*)(common->linked_type);
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    free(list);

    return ret;
}

