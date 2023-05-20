#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_count.h"
#include "../utils/utils.h"

frequency_t *Frequency_new() {
    frequency_t *frequency = malloc(sizeof(frequency_t));
    if (!frequency)
        return NULL;

    frequency->count = 0;
    return frequency;
}

void Frequency_delete(frequency_t *frequency) {
    if (!frequency)
        return;

    free(frequency);
}

word_count_t *WordCount_new() {
    word_count_t *word_count = malloc(sizeof(word_count_t));
    if (!word_count)
        return NULL;

    for (int i = 0; i < WORDS_LIMIT; i++)
        word_count->frequency[i] = Frequency_new();

    word_count->words_inserted = 0;

    return word_count;
}

void WordCount_delete(word_count_t *word_count) {
    if (!word_count)
        return;

    for (int i = 0; i < WORDS_LIMIT; i++)
        Frequency_delete(word_count->frequency[i]);

    free(word_count);
}

void WordCount_insert_word(word_count_t *word_count, char *word) {
    // primeira palavra
    if (word_count->words_inserted == 0) {
        strcpy(word_count->frequency[0]->word, word);
        word_count->frequency[0]->count = 1;
        word_count->words_inserted = 1;

        return;
    }

    int i;
    for (i = 0; i < word_count->words_inserted; i++) {
        // A palavra já foi inserida
        if (strcmp(word_count->frequency[i]->word, word) == 0) {
            word_count->frequency[i]->count += 1;
            return;
        }
    }

    // Chegou ao final, inserir palavra nova
    strcpy(word_count->frequency[i]->word, word);
    word_count->frequency[i]->count = 1;
    word_count->words_inserted += 1;
}

void WordCount_insert_music(word_count_t *word_count, music_t *music) {
    char *word = strtok(music->lyrics, " ");

    while (1) {
        if (word == NULL)
            break;

        str_clean(word);
        if (strlen(word) > 3) {
            // printf("%s\n", word);

            str_lowercase(word);
            WordCount_insert_word(word_count, word);
        }

        word = strtok(NULL , " ");
    }
}

void WordCount_print(word_count_t *word_count) {
    for (int i = 0; i < word_count->words_inserted; i++) {
        char *word = word_count->frequency[i]->word;
        int count = word_count->frequency[i]->count;

        printf("%s -> %d\n", word, count);
    }
}
