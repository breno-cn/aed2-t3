#include <stdio.h>

#include "music/music.h"
#include "music/word_count.h"

#include "vector/vector.h"

#include "words_repo/word_repository.h"

int main() {
    music_t *music_repo[MUSICS_AMMOUNT];
    for (int i = 0; i < MUSICS_AMMOUNT; i++)
        music_repo[i] = NULL;

    word_count_t *word_count = WordCount_new();
    word_repository_t *repo = WordRepository_new();

    while (1) {
        int option;
        printf("Voce deseja inserir os dados de uma musica (1) ou pesquisar uma palavra (2) ou sair do programa (3)? ");
        scanf("%d", &option);

        if (option == 1) {
            printf("Digite um numero de 1 a %d para escolher uma musica, ou 0 para encerrar o programa: ", MUSICS_AMMOUNT);
            scanf("%d", &option);

            if (option < 0 || option > MUSICS_AMMOUNT) {
                printf("Opcao invalida!\n");
                continue;
            } else if (option == 0) {
                break;
            } else {
                printf("Inserindo musica numero %d no repositorio...\n", option);
                if (music_repo[option]) {
                    printf("Essa musica ja foi inserida previamente...\n");
                    continue;
                }

                char filepath[64];
                sprintf(filepath, "./LetrasMusicas/%d.txt", option);
                music_repo[option - 1] = Music_from_file(filepath, option - 1);
                WordRepository_insert_music(repo, music_repo[option - 1]);
                // WordCount_insert_music(word_count, music_repo[option - 1]);
            }
        } else if (option == 2) {
            // pesquisas...
            char word[WORD_SIZE];
            printf("Digite a palavra: ");
            scanf("%s", word);

            frequency_t *found = WordRepository_search(repo, word);
            if (!found) {
                printf("Palavra %s nao encontrada!\n", word);
            } else {
                printf("musica: %s\n", found->music->title);
                printf("compositor: %s\n", found->music->writer);
                printf("frequencia: %d\n", found->count);
            }
        } else if (option == 3) {
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    WordCount_print(word_count);
    WordCount_delete(word_count);

    return 0;
}