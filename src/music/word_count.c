#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_count.h"
#include "../utils/utils.h"

#define INSERTED_WORDS_SIZE 256

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

    word_count->vector = OrderedVector_new();

    return word_count;
}

void WordCount_delete(word_count_t *word_count) {
    if (!word_count)
        return;

    if (word_count->vector)
        OrderedVector_delete(word_count->vector);
    
    free(word_count);
}

int WordCount_insert_word(word_count_t *word_count, char *word, int music_index) {
    // primeira palavra
    if (word_count->words_inserted == 0) {
        strcpy(word_count->words[0], word);
        word_count->frequencies[0][music_index] = 1;
        word_count->words_inserted = 1;

        return 0;
    }

    int i;
    for (i = 0; i < word_count->words_inserted; i++) {
        // A palavra já foi inserida
        if (strcmp(word_count->words[i], word) == 0) {
            word_count->frequencies[i][music_index] += 1;
            return i;
        }
    }

    // Chegou ao final, inserir palavra nova
    strcpy(word_count->words[i], word);
    word_count->frequencies[i][music_index] += 1;
    word_count->words_inserted += 1;
    
    return i;
}

void WordCount_insert_music(word_count_t *word_count, music_t *music) {
    char *word = strtok(music->lyrics, " ");
    int words_index[INSERTED_WORDS_SIZE];
    int inserted_words = 0;

    while (1) {
        if (word == NULL)
            break;

        str_clean(word);
        if (strlen(word) > 3) {
            // printf("%s\n", word);

            str_lowercase(word);
            int word_index = WordCount_insert_word(word_count, word, music->index);
            words_index[inserted_words] = word_index;
            inserted_words += 1;
        }

        word = strtok(NULL , " ");
    }

    printf("Inserindo palavras no vetor ordenado...\n");
    for (int i = 0; i < inserted_words; i++) {
        int word_index = words_index[i];

        char *word = word_count->words[word_index];
        int count = word_count->frequencies[word_index][music->index];
        frequency_t *freq = Frequency_new(word, count, music);
        
        OrderedVector_insert(word_count->vector, freq);
    }
}

void WordCount_print(word_count_t *word_count) {
    for (int i = 0; i < word_count->words_inserted; i++) {
        char *word = word_count->words[i];
        // int count = word_count->frequency[i]->total_count;

        // printf("%s -> %d\n", word, count);
        printf("%s\n", word);
    }
}
