#include <stdio.h>

#include "music/music.h"
#include "music/word_count.h"
#include "bstree/bstree.h"

#define MUSICS_AMMOUNT 16

int main() {
    char filepath[64];
    music_t *music_repo[MUSICS_AMMOUNT];

    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        sprintf(filepath, "./LetrasMusicas/%d.txt", i + 1);
        music_repo[i] = Music_from_file(filepath);
    }

    word_count_t *word_count = WordCount_new();
    // WordCount_insert_music(word_count, music_repo[11]);
    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        WordCount_insert_music(word_count, music_repo[i]);
    }

    BSTree *bst = bstree_new();

    for (int i = 0; i < word_count->words_inserted; i++) {
        int status = bstree_insert(bst, word_count->frequency[i]);
        if (status != 0) {
            printf("Falha ao inserir a palavra %s\n", word_count->frequency[i]->word);
        }
    }
    printf("Músicas adicionadas.\n");
    printf("Quantidade de palavras: %d\n", bstree_node_count(bst));

    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        Music_delete(music_repo[i]);
    }
    WordCount_delete(word_count);
    bstree_free(bst);

    return 0;
}
