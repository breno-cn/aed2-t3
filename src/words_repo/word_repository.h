#pragma once

#include "../music/word_count.h"
#include "../vector/vector.h"

typedef struct word_repository_t {
    word_count_t *word_count;
    ordered_vector_t *vector;
} word_repository_t;

struct word_repository_t *WordRepository_new();
void WordRepository_insert_music(struct word_repository_t *repo, music_t *music);
