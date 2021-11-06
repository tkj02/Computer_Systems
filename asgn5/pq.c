#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct PriorityQueue {
    uint32_t capacity;
    uint32_t num_entries;
    Node **nodes;
} PriorityQueue;

void min_heapify(Node *nptr[], uint32_t start_node, uint32_t size){
	uint32_t li = start_node*2;
	uint32_t ri = li+1;
	uint32_t min_index = start_node;
	if (ri<=size && nptr[ri-1]->frequency < nptr[min_index-1]->frequency){
		min_index = ri;
	}
	if (li<=size && nptr[li-1]->frequency < nptr[min_index-1]->frequency){
                min_index = li;
        }
	if (min_index != start_node){
		Node *temp = nptr[min_index-1];
		nptr[min_index-1] = nptr[start_node-1];
		nptr[start_node-1] = temp;
		min_heapify(nptr, min_index, size);
	}
}

void build_heap(Node *nptr[], uint32_t size){
	uint32_t parent_index = size/2;
	for (uint32_t i = parent_index; i > 0; i--){
		min_heapify(nptr, i, size);
	}
}

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
	q->num_entries = 0;
        q->nodes = (Node **) malloc(capacity * sizeof(Node *));
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->nodes){
        free((*q)->nodes);
        free(*q);
        *q = NULL;
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->num_entries == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->num_entries == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->num_entries;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    q->nodes[q->num_entries] = n;
    q->num_entries++;
    build_heap(q->nodes, q->num_entries);
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->nodes[0];
    --q->num_entries;
    q->nodes[0] = q->nodes[q->num_entries];
    min_heapify (q->nodes, 1, q->num_entries);
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->num_entries; i++) {
	printf("%3d symbol: 0x%02X freq: %lu\n", i, q->nodes[i]->symbol, q->nodes[i]->frequency);
    }
}
