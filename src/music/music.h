#pragma once

#define TITLE_SIZE 32
#define WRITER_SIZE 32
#define LYRICS_SIZE 2048

#define MUSICS_AMMOUNT 16

typedef struct music_t {
    char title[TITLE_SIZE];
    char writer[WRITER_SIZE];
    char lyrics[LYRICS_SIZE];
    int index;
} music_t;

music_t *Music_from_file(char *filepath, int music_index);
void Music_delete(music_t *music);
