#include <stdio.h>
#include <stdlib.h>

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

    printf("Inserindo no vetor ordenado...\n");
    OrderedVector_merge(repo->vector, new_count);

    printf("Inserindo na arvore de busca binaria...\n");
    bstree_merge(repo->bstree, new_count);

    printf("Inserindo na AVL...\n");
    avl_merge(repo->avl, new_count);

    WordCount_print(repo->word_count);
    OrderedVector_print(repo->vector);
}
