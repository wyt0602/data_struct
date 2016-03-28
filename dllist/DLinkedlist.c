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
    DLinkeList *list = (DLinkedList*)(common->kinked_type);
    DLinkeNode *node = (DLinkedNode*)malloc(sizeof(DLinkedNode));
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






