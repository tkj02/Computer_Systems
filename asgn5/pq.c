#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct PriorityQueue {
    uint32_t capacity;
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    Node **nodes;
} PriorityQueue;

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
    if (pq_full(q)) {
        return false;
    }
    if (pq_empty(q)) {
        n = q->nodes[q->tail];
        q->head++;
        return true;
    }
    //min heap to sort n by priority
    n = q->nodes[q->head];
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->nodes[q->head];
    --q->head;
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->head; i++) {
        printf("%u\n", (uint32_t) q->nodes[i]);
    }
}
