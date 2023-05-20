#include <stdio.h>

#include "music/music.h"

#define MUSICS_AMMOUNT 16

int main() {
    char filepath[64];
    music_t *music_repo[MUSICS_AMMOUNT];

    for (int i = 1; i <= MUSICS_AMMOUNT; i++) {
        sprintf(filepath, "./LetrasMusicas/%d.txt", i);
        music_repo[i] = Music_from_file(filepath);
    }

    for (int i = 0; i < MUSICS_AMMOUNT; i++) {
        Music_delete(music_repo[i]);
    }

    return 0;
}
