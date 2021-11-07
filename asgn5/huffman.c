#include "defines.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

bool read_bit(int infile, uint8_t *bit);

Node *build_tree(uint64_t hist[static ALPHABET]) {
    bool return_stat;
    PriorityQueue *pq = pq_create(ALPHABET);
    if (pq == NULL) {
        printf("pq failed\n");
        return NULL;
    }
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] == 0) {
            continue;
        }
        Node *node = node_create(i, hist[i]);
        enqueue(pq, node);
    }
    while (pq_size(pq) >= 2) {
        Node *nl, *nr, *np;
        return_stat = dequeue(pq, &nl);
        if (return_stat == false) {
            printf("error dequeueing left\n");
            pq_delete(&pq);
            return NULL;
        }
        return_stat = dequeue(pq, &nr);
        if (return_stat == false) {
            printf("error dequeueing right\n");
            pq_delete(&pq);
            return NULL;
        }
        np = node_join(nl, nr);
        if (np == NULL) {
            printf("error joining\n");
            pq_delete(&pq);
            return NULL;
        }
        enqueue(pq, np);
    }
    if (pq_size(pq) == 1) {
        Node *root;
        return_stat = dequeue(pq, &root);
        if (return_stat == false) {
            printf("error dequeueing root\n");
            pq_delete(&pq);
            return NULL;
        }
        return root;
    } else {
        printf("error q count isn't 1 for root\n");
    }
    return NULL;
}
int recur_count1 = 0;
int tree_depth = 0;

void building_codes(Node *root, Code table[static ALPHABET], Code *c) {
    uint8_t popped_bit;
    tree_depth++;
    if (root == NULL)
        return;
    //if (root->symbol != '$') {
    if (root->left == NULL && root->right == NULL) {
        table[root->symbol] = *c;
        recur_count1++;
        //yy	printf("Adding code for 0x%02x Count: %d Depth:%d \n", root->symbol, recur_count1, tree_depth);
        tree_depth--;
        return;
    }
    code_push_bit(c, 0);
    if (root->left == NULL) {
        printf("Left = NULL  0x%02x Count: %d Depth:%d \n", root->symbol, recur_count1, tree_depth);
    }
    if (root->right == NULL) {
        printf(
            "Rightt = NULL  0x%02x Count: %d Depth:%d \n", root->symbol, recur_count1, tree_depth);
    }
    building_codes(root->left, table, c);
    code_pop_bit(c, &popped_bit);
    code_push_bit(c, 1);
    building_codes(root->right, table, c);
    code_pop_bit(c, &popped_bit);
    tree_depth--;
}
Code g_c;

void build_codes(Node *root, Code table[static ALPHABET]) {
    //Code c = code_init();
    g_c = code_init();
    building_codes(root, table, &g_c);
}

void dump_tree(int outfile, Node *root) {
	if (root == NULL){
		return;
	}
	dump_tree(outfile, root->left);
	dump_tree(outfile, root->right);
	uint8_t ch[2];
	if (root->left == NULL && root->right == NULL){
		ch[0] = 'L';
		ch[1] = root->symbol;
		write_bytes(outfile, ch, 2);
	}
	else {
		ch[0] = 'I';
		write_bytes(outfile, ch, 1);
	}
}

#if 0
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
}

void delete_tree(Node **root) {
}
#endif

int recur_count = 0;

bool decode(Node *root, int infile, int outfile) {

    if (root == NULL) {
        return false;
    }
   // if (root->symbol != '$') {
   if (root->left == NULL && root->right == NULL){
        write(outfile, &root->symbol, 1);
        recur_count++;
        //printf("recursive count %d\n",recur_count);
        return true;
    }
    uint8_t bit;
    bool flag;
    flag = read_bit(infile, &bit);
    if (flag == false) {
        return false;
    }
    if (bit == 0) {
        return decode(root->left, infile, outfile);
    } else {
        return decode(root->right, infile, outfile);
    }
    return false;
}
