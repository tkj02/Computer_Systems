#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Prototypes min_heapify and build_heap
// Both will be used in enqueue/dequeue
// They are similar to assignment three's heap
void min_heapify(Node *nptr[], uint32_t start_node, uint32_t size);
void build_heap(Node *nptr[], uint32_t size);

// Priority Queue structure
// Has capacity and number of entries
typedef struct PriorityQueue {
    uint32_t capacity;
    uint32_t num_entries;
    Node **nodes;
} PriorityQueue;

// Will create a priority queue of capacity, zero entries, and Node
// size of nodes
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->num_entries = 0;
        q->nodes = (Node **) malloc(capacity * sizeof(Node *));
    }
    return q;
}

// Frees memory and sets queue pointer to null
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->nodes) {
        free((*q)->nodes);
        free(*q);
        *q = NULL;
    }
}

// Checks if queue is empty if there are no entries
bool pq_empty(PriorityQueue *q) {
    if (q->num_entries == 0) {
        return true;
    }
    return false;
}

// Checks if queue is full if capacity is reached
bool pq_full(PriorityQueue *q) {
    if (q->num_entries == q->capacity) {
        return true;
    }
    return false;
}

// Returns the size of the queue, or the number of entries
uint32_t pq_size(PriorityQueue *q) {
    return q->num_entries;
}

// If the queue is not full, then add the node
// Call build_heap to use min_heapify and sort all the nodes
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    q->nodes[q->num_entries] = n;
    q->num_entries++;
    build_heap(q->nodes, q->num_entries);
    return true;
}

// If the queue is not empty, then remove the node
// Call min_heapify to sort all the nodes
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->nodes[0];
    --q->num_entries;
    q->nodes[0] = q->nodes[q->num_entries];
    min_heapify(q->nodes, 1, q->num_entries);
    return true;
}

// Prints the queue's nodes' symbols and frequencies
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->num_entries; i++) {
        printf("%3d symbol: 0x%02X freq: %lu\n", i, q->nodes[i]->symbol, q->nodes[i]->frequency);
    }
}

// Min heap implementation
// Compares frequencies of adjacent nodes
void min_heapify(Node *nptr[], uint32_t start_node, uint32_t size) {
    uint32_t li = start_node * 2;
    uint32_t ri = li + 1;
    uint32_t min_index = start_node;
    if (ri <= size && nptr[ri - 1]->frequency < nptr[min_index - 1]->frequency) {
        min_index = ri;
    }
    if (li <= size && nptr[li - 1]->frequency < nptr[min_index - 1]->frequency) {
        min_index = li;
    }
    if (min_index != start_node) {
        Node *temp = nptr[min_index - 1];
        nptr[min_index - 1] = nptr[start_node - 1];
        nptr[start_node - 1] = temp;
        min_heapify(nptr, min_index, size);
    }
}

// Build heap implementation
// Calls min_heapify to sort
void build_heap(Node *nptr[], uint32_t size) {
    uint32_t parent_index = size / 2;
    for (uint32_t i = parent_index; i > 0; i--) {
        min_heapify(nptr, i, size);
    }
}
