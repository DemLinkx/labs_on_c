#include "stack.h"
#include <stdlib.h>


typedef struct StackNode {
    double value;              
    struct StackNode* next;    
} StackNode;

struct Stack {
    StackNode* top;   
    size_t size;       
};

Stack* stack_create(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

void stack_free(Stack* stack) {
    if (stack == NULL) {
        return;
    }
    stack_clear(stack);
    free(stack);
}

int stack_push(Stack* stack, double value) {
    if (stack == NULL) {
        return -1;
    }
    
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node == NULL) {
        return -1;  /* Ошибка выделения памяти */
    }
    
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    
    return 0;
}

int stack_pop(Stack* stack, double* out_value) {
    if (stack == NULL || stack->top == NULL) {
        return -1;
    }
    
    StackNode* temp = stack->top;
    if (out_value != NULL) {
        *out_value = temp->value;
    }
    
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    
    return 0;
}

int stack_peek(const Stack* stack, double* out_value) {
    if (stack == NULL || stack->top == NULL || out_value == NULL) {
        return -1;
    }
    
    *out_value = stack->top->value;
    return 0;
}

int stack_is_empty(const Stack* stack) {
    if (stack == NULL) {
        return 1;
    }
    return (stack->top == NULL) ? 1 : 0;
}

size_t stack_size(const Stack* stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->size;
}

void stack_clear(Stack* stack) {
    if (stack == NULL) {
        return;
    }
    
    while (stack->top != NULL) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    stack->size = 0;
}