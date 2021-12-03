#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool read_line(FILE* file, char** buffer, size_t* out_length) {
    int    character;
    size_t size = 256;
    size_t length = 0;
    char*  line;

    line = malloc(sizeof(char) * size);

    while (true) {
        character = fgetc(file);

        if (character == EOF) {
            if (length == 0) {
                *buffer = line;
                return false;
            }
            break;
        }
        if (character == '\n')
            break;
        
        line[length] = character;
        length++;

        if (length == size) {
            size *= 2;
            line = realloc(line, sizeof(char) * size);
        }
    }

    line[length] = '\0';
    line = realloc(line, sizeof(char) * (length + 1));
    
    *out_length = length;
    free(*buffer);
    *buffer     = line;
    return true;
}
