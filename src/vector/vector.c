#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "../utils/utils.h"

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
    // Primeira palavra, inserir no começo do vetor
    if (vector->words_inserted == 0) {
        vector->words[0] = freq;
        vector->words_inserted = 1;
        
        return;
    }

    int i;
    for (i = 0; i < vector->words_inserted; i++) {
        int compare = strcmp(freq->word, vector->words[i]->word);

        // A palavra já existe, verificar se a nova frequeência é maior
        // se sim, substituir, se não, não fazer nada
        if (compare == 0) {
            if (vector->words[i]->count >= freq->count)
                return;

            vector->words[i] = freq;
            return;
        } else if (compare < 0) {
            for (int j = vector->words_inserted; j > i; j--) {
                vector->words[j] = vector->words[j - 1];
            }

            vector->words[i] = freq;
            vector->words_inserted += 1;
            
            return;
        }
    }

    // Caso especial para o final do vetor
    vector->words[i] = freq;
    vector->words_inserted += 1;
}

// void OrderedVector_insert(ordered_vector_t *vector, frequency_t *freq) {
//     // Primeira palavra a ser inserida
//     if (vector->words_inserted == 0) {
//         vector->words[0] = freq;
//         vector->words_inserted = 1;
        
//         return;
//     }

//     int i;
//     for (i = 0; i < vector->words_inserted; i++) {
//         // Encontrou a posição a ser inserida, mover todos uma casa
//         // pra frente e inserir
//         int compare = strcmp(freq->word, vector->words[i]->word);
//         if (compare == 0 && vector->words[i]->count >= freq->count) {
//             return;
//         } else if (vector->words[i]->count < freq->count) {
//             vector->words[i]->count = freq->count;
//             return;
//         } else if (compare < 0) {
//             // if (vector->words[i]->count >= freq->count)
//                 // return;
            
//             for (int j = vector->words_inserted; j > i; j--) {
//                 vector->words[j] = vector->words[j - 1];
//             }

//             vector->words[i] = freq;
//             vector->words_inserted += 1;
//             return;
//         }
//     }

//     // A palavra deve ser inserida no final do vetor
//     vector->words[i] = freq;
//     vector->words_inserted += 1;
// }

void OrderedVector_print(ordered_vector_t *vector) {
    printf("%d\n", vector->words_inserted);

    // for (int i = 0; i < vector->words_inserted; i++) {
    //     // printf("%p\n", vector->words[i]);

    //     char *word = vector->words[i]->word;
    //     int frequency = vector->words[i]->count;

    //     printf("%s -> %d\n", word, frequency);
    // }
}

frequency_t *OrderedVector_find(ordered_vector_t *vector, char *word) {
    int left = 0;
    int right = vector->words_inserted - 1;
    int middle = (left + right) / 2;

    while (left <= right) {
        int compare = strcmp(vector->words[middle]->word, word);

        if (compare < 0)
            left = middle + 1;
        else if (compare == 0)
            return vector->words[middle];
        else
            right = middle - 1;

        middle = (left + right) / 2;
    }

    return NULL;
}

void OrderedVector_insert_music(ordered_vector_t *vector, music_t *music) {
    char *word = strtok(music->lyrics, " ");

    while (1) {
        if (word == NULL)
            break;

        str_clean(word);
        if (strlen(word) > 3) {
            str_lowercase(word);
            // OrderedVector_insert(vector, word);
        }

        word = strtok(NULL, " ");
    }
}

void OrderedVector_insert_frequency(ordered_vector_t *vector, frequency_t *freq) {
    if (vector->words_inserted == 0) {
        vector->words[0] = freq;
        vector->words_inserted = 1;

        return;
    }

    int i;
    for (i = 0; i < vector->words_inserted; i++) {
        int compare = strcmp(freq->word, vector->words[i]->word);

        if (compare == 0) {
            if (vector->words[i]->count < freq->count) {
                vector->words[i] = freq;
            }

            return;
        }

        if (compare < 0) {
            for (int j = vector->words_inserted; j > i; j--) {
                vector->words[j] = vector->words[j - 1];
            }

            vector->words[i] = freq;
            vector->words_inserted += 1;
            return;
        }
    }

    vector->words[i] = freq;
    vector->words_inserted += 1;
}

void OrderedVector_merge(ordered_vector_t *vector, struct word_count_t *word_count) {
    for (int i = 0; i < word_count->words_inserted; i++) {
        OrderedVector_insert_frequency(vector, word_count->words[i]);
    }
}
