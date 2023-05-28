#pragma once

#include "music.h"
#include "../vector/vector.h"

#define WORDS_LIMIT 1024
#define WORD_SIZE 32

typedef struct frequency_t {
    char word[WORD_SIZE];
    int count;
    music_t *music;
} frequency_t;

typedef struct word_count_t {
    char words[WORDS_LIMIT][WORD_SIZE];
    int frequencies[WORDS_LIMIT][MUSICS_AMMOUNT];
    int words_inserted;

    struct ordered_vector_t *vector;
} word_count_t;

frequency_t *Frequency_new();
void Frequency_delete(frequency_t *frequency);

word_count_t *WordCount_new();
void WordCount_delete(word_count_t *word_count);
int WordCount_insert_word(word_count_t *word_count, char *word, int music_index);
void WordCount_insert_music(word_count_t *word_count, music_t *music);
void WordCount_print(word_count_t *word_count);
