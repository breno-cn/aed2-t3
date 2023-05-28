#pragma once

#include "music.h"

#define WORDS_LIMIT 1024
#define WORD_SIZE 32

typedef struct frequency_t {
    char word[WORD_SIZE];
    int count;
    music_t *music;
} frequency_t;

typedef struct word_count_t {
    frequency_t *words[WORDS_LIMIT];
    int words_inserted;
} word_count_t;

struct frequency_t *Frequency_new();
void Frequency_delete(struct frequency_t *frequency);

struct word_count_t *WordCount_new();
void WordCount_delete(struct word_count_t *word_count);
void WordCount_insert_word(struct word_count_t *word_count, char *word, struct music_t *music);
struct word_count_t *WordCount_insert_music(struct word_count_t *word_count, struct music_t *music);
void WordCount_print(struct word_count_t *word_count);

void WordCount_insert_frequency(struct word_count_t *word_count, struct frequency_t *freq);
void WordCount_merge(struct word_count_t *to, struct word_count_t *from);
