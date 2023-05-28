#pragma once

#include "../music/word_count.h"
#include "../vector/vector.h"
#include "../bstree/bstree.h"
#include "../avl/avl.h"
#include "../avl_freq/avl_freq.h"

typedef struct word_repository_t {
    word_count_t *word_count;
    ordered_vector_t *vector;
    struct bst_node **bstree;
    struct avl_node **avl;
    struct avlfreq_node **avlfreq;
} word_repository_t;

struct word_repository_t *WordRepository_new();
void WordRepository_insert_music(struct word_repository_t *repo, music_t *music);
frequency_t *WordRepository_search(struct word_repository_t *repo, char *word);
frequency_t **WordRepository_search_by_freq(struct word_repository_t *repo, int freq, int *ammount);
