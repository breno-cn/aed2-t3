#include <stdio.h>

#include "music/music.h"

int main() {
    int option;
    printf("Escolha um arquivo (1 - 16) para carregar os dados da musica: ");
    scanf("%d", &option);
    char filepath[32];
    sprintf(filepath, "./LetrasMusicas/%d.txt", option);

    music_t *music = Music_from_file(filepath);

    printf("%s\n", music->title);
    printf("%s\n", music->writer);
    printf("%s\n", music->lyrics);

    Music_delete(music);

    return 0;
}
