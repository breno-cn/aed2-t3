#pragma once

#include "music.h"

#define WORDS_LIMIT 1024
#define WORD_SIZE 32

typedef struct word_count_t {
    char word[WORDS_LIMIT][WORD_SIZE];
    int count[WORDS_LIMIT];
    int words_inserted;
} word_count_t;

word_count_t *WordCount_new();
void WordCount_delete(word_count_t *word_count);
void WordCount_insert_word(word_count_t *word_count, char *word);
void WordCount_insert_music(word_count_t *word_count, music_t *music);
void WordCount_print(word_count_t *word_count);
