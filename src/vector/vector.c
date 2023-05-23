#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

ordered_vector_t *OrderedVector_new() {
    ordered_vector_t *vector = malloc(sizeof(ordered_vector_t));
    if (!vector)
        return NULL;

    vector->words_inserted = 0;
    return vector;
}

void OrderedVector_delete(ordered_vector_t *vector) {
    if (!vector)
        return;

    free(vector);
}

void OrderedVector_insert(ordered_vector_t *vector, frequency_t *freq) {
    // Primeira palavra a ser inserida
    if (vector->words_inserted == 0) {
        vector->words[0] = freq;
        vector->words_inserted = 1;
        
        return;
    }

    int i;
    for (i = 0; i < vector->words_inserted - 1; i++) {
        // Encontrou a posição a ser inserida, mover todos uma casa
        // pra frente e inserir
        if (strcmp(freq->word, vector->words[i]->word) <= 0) {
            for (int j = vector->words_inserted; j > i; j--) {
                vector->words[j] = vector->words[j - 1];
            }

            vector->words[i] = freq;
            vector->words_inserted += 1;
            return;
        }
    }

    // A palavra deve ser inserida no final do vetor
    vector->words[i] = freq;
    vector->words_inserted += 1;
}

void OrderedVector_print(ordered_vector_t *vector) {
    printf("%d\n", vector->words_inserted);

    for (int i = 0; i < vector->words_inserted; i++) {
        printf("%p\n", vector->words[i]);

        char *word = vector->words[i]->word;
        int frequency = vector->words[i]->count;

        printf("%s -> %d\n", word, frequency);
    }
}
