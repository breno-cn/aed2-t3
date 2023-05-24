#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

BSTree *bstree_new() {
    BSTree *root = (BSTree*) malloc(sizeof(BSTree));
    if (!root)
        *root = NULL;

    return root;
}

int node_free(struct node *node) {
    if (node == NULL)
        return 0;

    node_free(node->left);
    node_free(node->right);
    free(node);
    node = NULL;

    return 0;
}

int bstree_free(BSTree *root) {
    if (root == NULL)
        return 0;

    node_free(*root);
    free(root);
    return 0;
}

int bstree_is_empty(BSTree *root) {
    if (root == NULL)
        return 1;
    if (*root == NULL)
        return 1;

    return 0;
}

int bstree_node_count(BSTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    int left_height = bstree_node_count(&((*root)->left));
    int right_height = bstree_node_count(&((*root)->right));

    return (left_height + right_height + 1);
}

int bstree_height(BSTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    int left_height = bstree_height(&((*root)->left));
    int right_height = bstree_height(&((*root)->right));

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }

}

int bstree_insert(BSTree *root, char *word) {
    if (root == NULL) {
        return 0;
    }
    struct node *new;
    new = (struct node*) malloc(sizeof(struct node));
    if (new == NULL)
        return -1;

    strcpy(new->word, word);
    new->left = NULL;
    new->right = NULL;

    if (*root == NULL) {
        *root = new;
    } else {
        struct node *current = *root;
        struct node *previous = NULL;
        while (current != NULL) {
            previous = current;

            if (strcmp(word, current->word) == 0) {
                free(new);
                return 0;
            }

            if (strcmp(word, current->word) > 0) {
                current = current->right;
            } else {
                current = current->left;
            }
        }

        if (strcmp(word, previous->word) > 0) {
            previous->right = new;
        } else {
            previous->left = new;
        }
    }

    return 0;
}

/*
 * TODO: Create remove functions
 */

struct node* bstree_remove_current(struct node *current) {
    struct node *node_1, *node_2;

    if (current->left == NULL) {
        node_2 = current->right;
        free(current);
        return node_2;
    }

    node_1 = current;
    node_2 = current->left;
    while (node_2->right != NULL) {
        node_1 = node_2;
        node_2 = node_2->right;
    }

    if (node_1 != current) {
        node_1->right = node_2->left;
        node_2->left = current->left;
    }
    node_2->right = current->right;
    free(current);

    return node_2;
}

int bstree_delete(BSTree *root, char *word) {
    if (root == NULL) {
        return 0;
    }
    struct node *previous;
    struct node *current = *root;
    while (current != NULL) {
        if (strcmp(word, current->word) == 0) {
            if (current == *root) {
                *root = bstree_remove_current(current);
            } else {
                if (previous->right == current) {
                    previous->right = bstree_remove_current(current);
                } else {
                    previous->left = bstree_remove_current(current);
                }

                return 1;
            }
        }

        previous = current;
        if (strcmp(word, current->word) > 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return 0;
}

int bstree_search(BSTree *root, char *word) {
    if (root == NULL) {
        return 0;
    }

    struct node *current = *root;
    while (current != NULL) {
        if (strcmp(word, current->word) == 0) {
            return 1;
        }

        if (strcmp(word, current->word) > 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return 0;
}

void bstree_print_preorder(BSTree *root) {
    if (root == NULL)
        return;

    if (*root != NULL) {
        printf("%s\n", (*root)->word);
        bstree_print_preorder(&((*root)->left));
        bstree_print_preorder(&((*root)->right));
    }
}

void bstree_print_inorder(BSTree *root) {
    if (root == NULL) {
        return;
    }

    if (*root != NULL) {
        bstree_print_inorder(&((*root)->left));
        printf("%s\n", (*root)->word);
        bstree_print_inorder(&((*root)->right));
    }
}

void bstree_print_postorder(BSTree *root) {
    if (root == NULL) {
        return;
    }

    if (*root != NULL) {
        bstree_print_inorder(&((*root)->left));
        bstree_print_inorder(&((*root)->right));
        printf("%s\n", (*root)->word);
    }
}
