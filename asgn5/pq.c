#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    uint32_t capacity;
    uint32_t head;
    uint32_t tail;
    Node **nodes;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->head = 0;
        q->tail = 0;
        q->nodes = NULL;
        q->nodes = (Node **) malloc(capacity * sizeof(Node *));
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q) {
    if (q->head == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->head == q->capacity) {
	return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->head;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full) {
        return false;
    }
    if (q->tail == NULL){
	    q->tail = q->head = n;
	    return true;
    }
    q->tail->next = n;
    q->tail = n;
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty) {
        return true;
    }
    //will add
    return true;
}

void pq_print(PriorityQueue *q) {
    //print queue
}
