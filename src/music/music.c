#include <stdio.h>
#include <stdlib.h>

#include "music.h"

#define BUFFER_SIZE 2048

music_t *Music_from_file(char *filepath) {
    music_t *music = malloc(sizeof(music_t));
    if (!music)
        return NULL;

    FILE *file = fopen(filepath, "r");

    fgets(music->title, TITLE_SIZE, file);
    fgets(music->writer, WRITER_SIZE, file);
    fread(music->lyrics, sizeof(char), LYRICS_SIZE, file);

    fclose(file);

    return music;
}

void Music_delete(music_t *music) {
    if (!music)
        return;

    free(music);
}
