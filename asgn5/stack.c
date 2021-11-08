#include "node.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Creates Stack stuct
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// Creates stack with top set to zero, capacity, and
// enough memory allocated for node items
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node **));
    }
    return s;
}

// Frees memory of node items and stack pointer
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

// If the top is zero, the stack is empty
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

// If the top is the capacity, the stack is full
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

// The stack size is the top of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Pushes value at pointer n to the top of the stack
// if the stack is not full
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top++;
    return true;
}

// Pops top of the stack and passes it to pointer n
// if the stack is not empty
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    --s->top;
    *n = s->items[s->top];
    return true;
}

// Prints all nodes of the stack
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        printf("%u\n", (uint32_t) s->items[i]);
    }
}
