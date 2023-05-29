#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_count.h"
#include "../utils/utils.h"

#define INSERTED_WORDS_SIZE 1024

frequency_t *Frequency_new(char *word, int count, music_t *music) {
    frequency_t *frequency = malloc(sizeof(frequency_t));
    if (!frequency)
        return NULL;

    strcpy(frequency->word, word);
    frequency->count = count;
    frequency->music = music;
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

    word_count->words_inserted = 0;

    return word_count;
}

void WordCount_delete(word_count_t *word_count) {
    if (!word_count)
        return;

    free(word_count);
}

void WordCount_insert_word(struct word_count_t *word_count, char *word, music_t *music) {
    if (word_count->words_inserted == 0) {
        frequency_t *freq = Frequency_new(word, 1, music);
        word_count->words[0] = freq;
        word_count->words_inserted += 1;
        word_count->words[0]->music = music;
        return;
    }

    int i;
    for (i = 0; i < word_count->words_inserted; i++) {
        if (strcmp(word_count->words[i]->word, word) == 0) {
            word_count->words[i]->count += 1;
            word_count->words[i]->music = music;
            return;
        }
    }

    frequency_t *freq = Frequency_new(word, 1, music);
    word_count->words[i] = freq;
    word_count->words_inserted += 1;
    word_count->words[i]->music = music;
}

word_count_t *WordCount_insert_music(word_count_t *word_count, music_t *music) {
    word_count_t *new_count = WordCount_new();
    char *word = strtok(music->lyrics, " ");

    while (1) {
        if (word == NULL)
            break;

        str_clean(word);
        if (strlen(word) > 3) {
            str_lowercase(word);
            WordCount_insert_word(new_count, word, music);
        }

        word = strtok(NULL, " ");
    }

    WordCount_merge(word_count, new_count);
    return new_count;
}

void WordCount_print(word_count_t *word_count) {
    // for (int i = 0; i < word_count->words_inserted; i++) {
        // char *word = word_count->words[i];
        // int count = word_count->frequency[i]->total_count;

        // printf("%s -> %d\n", word, count);
        // printf("%s\n", word);
    // }

    printf("%d\n", word_count->words_inserted);
    // OrderedVector_print(word_count->vector);
}

void WordCount_insert_frequency(word_count_t *word_count, frequency_t *freq) {
    if (word_count->words_inserted == 0) {
        word_count->words[0] = freq;
        word_count->words_inserted = 1;

        return;
    }

    int i;
    for (i = 0; i < word_count->words_inserted; i++) {
        if (strcmp(word_count->words[i]->word, freq->word) == 0) {
            word_count->words[i]->count += freq->count;

            return;
        }
    }

    word_count->words[i] = freq;
    word_count->words_inserted += 1;
}

void WordCount_merge(word_count_t *to, word_count_t *from) {
    for (int i = 0; i < from->words_inserted; i++) {
        WordCount_insert_frequency(to, from->words[i]);
    }
}
