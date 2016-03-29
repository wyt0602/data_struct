/**
 * @file Stack.h
 * @Brief  Stack interfaces
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-29
 */

#ifndef STACK_H_
#define STACK_H_

typedef struct Stack{
    /**
     * stack array's start address
     */
    void **start_address;
    /**
     * stack's size
     */
    unsigned int size;
    /**
     * top of the stack
     */
    unsigned int top;
}Stack;

#define STACK_EMPTY(stack) ((stack->top) == 0)
#define STACK_FULL(stack) ((stack->top) == (stack->size))
#define STACK_TOP(stack) ((stack->start_address)[stack->top-1])

typedef void (*handle_destroy)(void *element);

int stack_new(Stack *stack, unsigned int size);
int stack_delete(Stack *stack, handle_destroy destroy_data);
int stack_clear(Stack *stack, handle_destroy destroy_data);

int stack_enlarge(Stack *stack, unsigned int size);
int stack_decrease(Stack *stack, unsigned int size);

int stack_push(Stack *stack, void *element);
void* stack_pop(Stack *stack);

#endif
