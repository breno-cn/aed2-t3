#pragma once

#include "../music/word_count.h"

#define VECTOR_SIZE 2048

typedef struct ordered_vector_t {
    frequency_t *words[VECTOR_SIZE];
    int words_inserted;
} ordered_vector_t;

ordered_vector_t *OrderedVector_new();
void OrderedVector_delete(ordered_vector_t *vector);
void OrderedVector_insert(ordered_vector_t *vector, frequency_t *freq);
void OrderedVector_print(ordered_vector_t *vector);
frequency_t *OrderedVector_find(ordered_vector_t *vector, char *word);
