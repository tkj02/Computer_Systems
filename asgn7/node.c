#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    // Allocates memory for node
    Node *n = (Node *) malloc(sizeof(Node));

    // Sets left and right to NULL
    // Allocates memory and copies old/new speak
    if (n) {
        n->left = NULL;
        n->right = NULL;
        n->oldspeak = strdup(oldspeak);

        // If given newspeak is not NULL, copies it to node newspeak
        if (newspeak != NULL) {
            n->newspeak = strdup(newspeak);

            // If given newspeak is NULL, sets node newspeak to NULL
        } else {
            n->newspeak = NULL;
        }
    }

    // Returns node pointer
    return n;
}

void node_delete(Node **n) {
    // Frees memory of old/new speak
    if ((*n) == NULL) {
        return;
    }

    // Frees if oldspeak is not NULL yet
    if ((*n)->oldspeak != NULL) {
        free((*n)->oldspeak);
    }

    // Frees if newspeak is not NULL yet
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
    }
    // Frees memory of node
    free(*n);
    *n = NULL;
}

void node_print(Node *n) {
    // If oldspeak and newspeak exist, print both
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    // If only oldspeak exists, print it
    else if (n->oldspeak != NULL && n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
}
