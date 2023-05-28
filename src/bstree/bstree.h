#pragma once

#include "../music/word_count.h"

struct bst_node {
    struct frequency_t *frequency;
    // char *word;
    struct bst_node *left;
    struct bst_node *right;
};

typedef struct bst_node *BSTree;

BSTree *bstree_new();
int bstree_free(BSTree *root);
int bstree_is_empty(BSTree *root);
int bstree_node_count(BSTree *root);
int bstree_height(BSTree *root);
int bstree_insert(BSTree *root, frequency_t *freq);
frequency_t *bstree_search(BSTree *root, char *word);
int bstree_delete(BSTree *root, char *word);
void bstree_print_preorder(BSTree *root);
void bstree_print_inorder(BSTree *root);
void bstree_print_postorder(BSTree *root);

void bstree_merge(BSTree *root, struct word_count_t *word_count);
