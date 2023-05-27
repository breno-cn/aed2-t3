#pragma once

#include "../music/music.h"

#define WORD_SIZE 32

typedef struct search_frequency_t {
    char word[WORD_SIZE];
    int most_appeared;
    music_t *music_info;
} search_frequency_t;

search_frequency_t *SearchFrequency_new();
void SearchFrequency_delete(search_frequency_t *freq);
