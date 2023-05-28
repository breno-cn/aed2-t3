#pragma once

#include "../music/word_count.h"

#define VECTOR_SIZE 2048

typedef struct ordered_vector_t {
    struct frequency_t *words[VECTOR_SIZE];
    int words_inserted;
} ordered_vector_t;

struct ordered_vector_t *OrderedVector_new();
void OrderedVector_delete(struct ordered_vector_t *vector);
void OrderedVector_insert(struct ordered_vector_t *vector, struct frequency_t *freq);
struct frequency_t *OrderedVector_find(struct ordered_vector_t *vector, char *word);

void OrderedVector_insert_frequency(struct ordered_vector_t *vector, struct frequency_t *freq);
void OrderedVector_merge(struct ordered_vector_t *vector, struct word_count_t *word_count);
