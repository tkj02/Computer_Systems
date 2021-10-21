#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct Stack {
	uint32_t top; // Index of the next empty slot .
	uint32_t capacity ; // Number of items that can be pushed .
	uint32_t * items ; // Array of items , each with type uint32_t .
};

Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *) malloc (sizeof(Stack));
	if (s) {
		s->top = 0;
		s->capacity = capacity;
		s->items = (uint32_t *) calloc (capacity, sizeof(uint32_t));
		if (!s->items) {
			free(s);
			s = NULL;
		}
	}
	return s;
}

void stack_delete(Stack **s) {
	if (*s && (*s)-> items) {
		free((*s)->items);
		free(*s);
		*s = NULL;
	}
	return;
}

bool stack_empty(Stack *s){
	if (*s == NULL){
		return true;
	}
	else {
		return false;
	}
}

bool stack_full(Stack *s){
	return;
}

uint32_t stack_size(Stack *s){
	return;
}

bool stack_push(Stack *s, uint32_t x){
	return;
}

bool stack_pop(Stack *s, uint32_t *x){
	return;
}

bool stack_peek(Stack *s, uint32_t *x){
	return;
}

void stack_copy(Stack *dst, Stack *src){
	return;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]){
	return;
}
