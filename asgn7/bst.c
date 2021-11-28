#include "node.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *bst_create(void) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return n;
    }
    n->oldspeak = NULL;
    n->newspeak = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

uint32_t max(uint32_t a, uint32_t b) {
    if (a >= b) {
        return a;
    }
    return b;
}

uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

uint32_t bst_size(Node *root) {
    uint32_t counter = 0;
    if (root) {
        counter += 1;
        counter += bst_size(root->left);

        counter += bst_size(root->right);
    }
    return counter;
}

Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        // Current node matches oldspeak
        if (strcmp(root->oldspeak, oldspeak) == 0) {
            return root;
        }

        // Current node is greater than oldspeak
        else if (strcmp(root->oldspeak, oldspeak) > 0) {
            Node *temp;
            temp = bst_find(root->left, oldspeak);
            return temp;
        }

        // Current node is less than oldspeak
        else if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }

        // Oldspeak is not in tree
        else {
            return NULL;
        }
    } else {
        return root;
    }
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
    }

    if (root->oldspeak == NULL) {
        root->oldspeak = strdup(oldspeak);

        if (newspeak != NULL) {
            root->newspeak = strdup(newspeak);
        }

        return root;
    }

    // Checks if oldspeak and newspeak are in bst
    // If so, does not insert and returns NULL
    if (strcmp(root->oldspeak, oldspeak) == 0) {
        return NULL;
    }

    else if (strcmp(root->oldspeak, oldspeak) > 0) {
        root->left = bst_insert(root->left, oldspeak, newspeak);
    }

    else if (strcmp(root->oldspeak, oldspeak) < 0) {
        root->right = bst_insert(root->right, oldspeak, newspeak);
    }

    return root;
}

void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

void bst_delete(Node **root) {
    if (*root == NULL) {
        return;
    }
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
    *root = NULL;
}
