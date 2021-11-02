#include "node.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Stack Stack;

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    --s->top;
    *n = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    //check stack_create
    //check push and pop return true
    //check with example stack
}
