#pragma once

#include "../music/word_count.h"

struct avl_node {
    struct frequency_t *frequency;
    int height;
    struct avl_node *left;
    struct avl_node *right;
};
typedef struct avl_node *AVLTree;

AVLTree *avltree_new();
int avltree_is_empty(AVLTree *root);
int avltree_node_count(AVLTree *root);
int avltree_height(AVLTree *root);
frequency_t *avltree_search(AVLTree *root, char *word);
int avltree_delete(AVLTree *root, char *word);
int avltree_insert(AVLTree *root, struct frequency_t *freq);
void avltree_print_inorder(AVLTree *raiz);
void avltree_free(AVLTree *root);

void avl_merge(AVLTree *root, word_count_t *word_count);
