/**
 * @file Stack.c
 * @Brief  Stack implementation
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-29
 */

#include <stdlib.h>

#include "stack.h"
#include "util/Log.h"


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_new Initial stack struct
 *
 * @Param stack Stack struct
 * @Param size Stack size, if size=0, select default(10);or size is just size
 *
 * @Returns   0 is OK; other is failed
 */
/* ----------------------------------------------------------------------------*/
int stack_new(Stack *stack, unsigned int size)
{
    /**
     * set default size 10
     */
    if (size == 0)
	size = 10;
    if (stack == NULL){
	ERROR("null pointer!");
	return -1;
    }

    /**
     * initial stack
     */
    stack->start_address = (void**)malloc(size*sizeof(void*));
    if (stack->start_address == NULL){
	ERROR("malloc error!");
	return -1;
    }
    stack->size = size;
    stack->top = 0;

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_clear Clear the stack
 *
 * @Param stack Stack struct
 * @Param destroy_data The function that handles the data, like freeing memory
 *
 * @Returns   -1 is failed; >=0 is the number of data element
 */
/* ----------------------------------------------------------------------------*/
int stack_clear(Stack *stack, handle_destroy destroy_data)
{
    if (stack == NULL){
	ERROR("null pointer!");
	return -1;
    }

    int i;
    if (destroy_data != NULL)
	for (i=0; i<stack->top; i++)
	    destroy_data(stack->start_address[i]);

    int ret = stack->top;
    stack->top = 0;
    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_delete Delete the stack
 *
 * @Param stack Stack struct
 *
 * @Returns   -1 is failed; >=0 is the number of data element
 */
/* ----------------------------------------------------------------------------*/
int stack_delete(Stack *stack)
{
    if (stack == NULL){
	ERROR("null pointer!");
	return -1;
    }

    int ret = stack_clear(stack);
    free(stack->start_address);
    stack->start_address = NULL;
    stack->size = 0;

    return ret;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_enlarge Enlarge the stack by calling realloc
 *
 * @Param stack Stack struct
 * @Param size The aimed size
 *
 * @Returns   -1 is failed; other is the size of stack
 */
/* ----------------------------------------------------------------------------*/
int stack_enlarge(Stack *stack, unsigned int size)
{
    if (stack == NULL){
	ERROR("null pointer!");
	return -1;
    }

    /**
     * if size = 0, it means enlarging the stack twice than old
     * if size <= stack->size, it means no change
     */ 
    unsigned int new_size = 0;
    if (size == 0)
	new_size = stack->size * 2;
    else if (size > stack->size)
	new_size = size;
    else
	new_size = stack->size;

    void **temp;
    if (new_size > stack->size){
	temp = (void**)realloc(stack->start_address, new_size*sizeof(void*));
	if (temp == NULL)
	{
	    ERROR("realloc error!");
	    return -1;
	}
	stack->start_address = temp;
	stack->size = new_size;
    }

    return new_size;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_decrease Decrease the stack
 *
 * @Param stack Stack struct
 * @Param size The aimed size
 *
 * @Returns  -1 is failed; other is the size of stack 
 */
/* ----------------------------------------------------------------------------*/
int stack_decrease(Stack *stack, unsigned int size)
{
    if (stack == NULL){
	ERROR("null pointer!");
	return -1;
    }

    /**
     * if size >= stack size, will not change the size;
     * if stack->top < size < stack->size, will set new size
     * if size <= stack->top, will change the size to the stack->top
     */ 
    unsigned int new_size = 0;
    if (size >= stack->size)
	new_size = stack->size;
    else if (size > stack->top)
	new_size = size;
    else
	new_size = stack->top;

    void **temp;
    if (new_size < stack->size){
	temp = (void**)realloc(stack->start_address, new_size*sizeof(void*));
	if (temp == NULL)
	{
	    ERROR("realloc error!");
	    return -1;
	}
	stack->start_address = temp;
	stack->size = new_size;
    }

    return new_size;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_push Push element to stack
 *
 * @Param stack Stack struct
 * @Param element The element that needs to be pushed into the stack
 *
 * @Returns   0 is OK; -1 is failed
 */
/* ----------------------------------------------------------------------------*/
int stack_push(Stack *stack, void *element)
{
    if (stack == NULL || element == NULL){
	ERROR("null pointer!");
	return -1;
    }

    /**
     * if the stack is not full, put element into the stack directly
     * or enlarge the stack, then push the element
     */ 
    if (STACK_FULL(stack)){
	if (stack_enlarge(stack, 0) == -1)
	    return -1;
    }
    stack->start_address[stack->top] = element;
    stack->top++;

    return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief  stack_pop Pop an element
 *
 * @Param stack Stack struct
 *
 * @Returns   NULL is failed; other is the address of the element
 */
/* ----------------------------------------------------------------------------*/
void* stack_pop(Stack *stack)
{
    if (stack == NULL){
	ERROR("null pointer!");
	return NULL;
    }

    void *ret =NULL;
    if (STACK_EMPTY(stack))
    {
	INFO("stack is empty!");
	return ret;
    }else{
	ret = stack->start_address[stack->top-1];
	stack->top--;
    }

    return ret;
}
