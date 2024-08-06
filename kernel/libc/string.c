#include <stddef.h>

size_t strlen(char *string) {
    size_t length = 0;
    while (string[length]) {
        length++;
    }
    return length;
}

