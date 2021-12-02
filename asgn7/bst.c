#include "node.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *bst_create(void) {
    // Returns empty tree
    return NULL;
}

// Helper function for bst_height
uint32_t max(uint32_t a, uint32_t b) {
    // Returns greatest value between a and b
    if (a >= b) {
        return a;
    }
    return b;
}

uint32_t bst_height(Node *root) {
    // If root is not NULL, returns max height + root height
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }

    // Root is NULL and the height is zero
    return 0;
}

uint32_t bst_size(Node *root) {
    // Keeps track of size
    uint32_t counter = 0;

    // Increases count for every recursive call
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
            // Traverses to left of tree as new root
            return bst_find(root->left, oldspeak);
        }

        // Current node is less than oldspeak
        else if (strcmp(root->oldspeak, oldspeak) < 0) {
            // Traverses to right of tree as new root
            return bst_find(root->right, oldspeak);
        }

        // Oldspeak is not in tree
        else {
            return NULL;
        }

        // Root is NULL
    } else {
        return root;
    }
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    // If bst does not already exist:

    // Creates root of new bst
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
    }
#if 0
    // Duplicates oldspeak to root's oldspeak
    if (root->oldspeak == NULL) {
        root->oldspeak = strdup(oldspeak);

        // If newspeak exists, duplicates it to root's newspeak
        if (newspeak != NULL) {
            root->newspeak = strdup(newspeak);
        }

        // Returns root of new bst
        return root;
    }
#endif
    // If bst already exists:

    // Checks if oldspeak and newspeak are in bst
    // If so, does not insert and returns NULL
    if (strcmp(root->oldspeak, oldspeak) == 0) {
        return NULL;
    }

    // Current node is greater than oldspeak
    else if (strcmp(root->oldspeak, oldspeak) > 0) {
        // Traverses to left of tree as new root
        root->left = bst_insert(root->left, oldspeak, newspeak);
    }

    // Current node is lss than oldspeak
    else if (strcmp(root->oldspeak, oldspeak) < 0) {
        // Traverses to right of tree as new root
        root->right = bst_insert(root->right, oldspeak, newspeak);
    }

    return root;
}

void bst_print(Node *root) {
    // If root is not NULL, prints nodes in inorder
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

void bst_delete(Node **root) {
    // Recursively frees node memory in postorder
    if (*root == NULL) {
        return;
    }
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
    *root = NULL;
}
