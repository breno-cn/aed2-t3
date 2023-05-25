#include <stdio.h>

#include "music/music.h"
#include "music/word_count.h"

#include "vector/vector.h"

#define MUSICS_AMMOUNT 16

int main() {
    char filepath[64];
    music_t *music_repo[MUSICS_AMMOUNT];

    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        sprintf(filepath, "./LetrasMusicas/%d.txt", i + 1);
        music_repo[i] = Music_from_file(filepath);
    }

    word_count_t *word_count = WordCount_new();
    WordCount_insert_music(word_count, music_repo[11]);
    // WordCount_print(word_count);

    ordered_vector_t *vector = OrderedVector_new();
    // printf("---------------------------------\n");
    for (int i = 0; i < word_count->words_inserted; i++) {
        // printf("%s\n", word_count->frequency[i]->word);
        OrderedVector_insert(vector, word_count->frequency[i]);
    }
    printf("---------------------------------\n");
    OrderedVector_print(vector);
    printf("ok\n");

    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        Music_delete(music_repo[i]);
    }

    WordCount_delete(word_count);
    OrderedVector_delete(vector);

    return 0;
}
