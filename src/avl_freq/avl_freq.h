#pragma once

#include "../music/word_count.h"

struct avlfreq_node {
    struct frequency_t *frequency;
    int height;
    struct avlfreq_node *left;
    struct avlfreq_node *right;
};
typedef struct avlfreq_node *AVLFreqTree;

AVLFreqTree *avlfreqtree_new();
int avlfreqtree_is_empty(AVLFreqTree *root);
int avlfreqtree_node_count(AVLFreqTree *root);
int avlfreqtree_height(AVLFreqTree *root);
frequency_t **avlfreqtree_search(AVLFreqTree *root, int frequency, int *ammount);
int avlfreqtree_insert(AVLFreqTree *root, struct frequency_t *freq);
void avlfreqtree_print_inorder(AVLFreqTree *raiz);
void avlfreqtree_free(AVLFreqTree *root);

void avlfreq_merge(AVLFreqTree *root, word_count_t *word_count);

