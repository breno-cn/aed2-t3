#include <ctype.h>
#include <string.h>

#include "utils.h"

int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c<= 'Z');
}

void str_lowercase(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        str[i] = tolower(str[i]);
    }
}

void str_clean(char *str) {
    int length = strlen(str);
    int i = 0;

    while (i < length && is_letter(str[i]))
        i++;

    str[i] = '\0';
}
