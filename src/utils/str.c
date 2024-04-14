#include "str.h"

/**
 * String functions since we've got nothing
*/

void strcpy(char *dest, char *src) {
    int idx = 0;

    while(*src != NULL_TERMINATOR) {
        dest[idx] = *src;
        src++;
        idx++;
    }
}

int strcmp(char *str1, char *str2) {
    while(*str1 != NULL_TERMINATOR) {
        if(*str1 != *str2) return 0;
        str1++;
        str2++;
    }

    if(*str2 != NULL_TERMINATOR)
        return 0;

    return 1;
}