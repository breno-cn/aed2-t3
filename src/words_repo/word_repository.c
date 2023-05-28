#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word_repository.h"
#include "../bstree/bstree.h"
#include "../avl/avl.h"

word_repository_t *WordRepository_new() {
    word_repository_t *repo = malloc(sizeof(word_repository_t));
    if (!repo)
        return NULL;

    repo->word_count = WordCount_new();
    repo->vector = OrderedVector_new();
    repo->bstree = bstree_new();
    repo->avl = avltree_new();

    return repo;
}

void WordRepository_insert_music(word_repository_t *repo, music_t *music) {
    struct word_count_t *new_count = WordCount_insert_music(repo->word_count, music);

    clock_t start;
    clock_t end;
    clock_t time_spent;

    start = clock();
    OrderedVector_merge(repo->vector, new_count);
    end = clock();
    time_spent = end - start;
    printf("Vetor ordenado: %f\n", (float) time_spent / CLOCKS_PER_SEC);

    start = clock();
    bstree_merge(repo->bstree, new_count);
    end = clock();
    time_spent = end - start;
    printf("BSTree: %f\n", (float) time_spent / CLOCKS_PER_SEC);

    start = clock();
    avl_merge(repo->avl, new_count);
    end = clock();
    time_spent = end - start;
    printf("AVL: %f\n", (float) time_spent / CLOCKS_PER_SEC);
}
