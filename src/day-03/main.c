#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "line.h"

#define MAGIC_NUMBER 64

uint32_t evil_global;

int cmpui32asc(const void* a, const void* b) {
    return (*(uint32_t*) a & evil_global) - (*(uint32_t*) b & evil_global);
}

void part1(void) {
    size_t l;
    uint32_t g = 0, *o = 0, n = 0;
    char* ln = 0;
    while (read_line(stdin, &ln, &l)) {
        n++;
        o = o ? o : calloc(l, sizeof(int32_t));
        for (size_t i = 0; i < l; i++)
            o[i] += (strtoul(ln, 0, 2) & 1 << i) > 0;
    }
    for (size_t i = 0; i < l; i++)
        g |= (o[i] > n / 2) * 1 << i;
    free(ln);
    free(o);
    printf("%u\n", g * (~g & (1 << l) - 1));
}

void part2(void) {
    size_t c = MAGIC_NUMBER, l = 0;
    uint32_t *a = malloc(c * sizeof(uint32_t)), n = 0;
    char* ln = 0;
    while (read_line(stdin, &ln, &l)) (a = ++n > c ? realloc(a, (c *= 2) * sizeof(uint32_t)) : a)[n - 1] = strtoul(ln, NULL, 2);
    uint32_t *s, *e, r[2];
    for (uint32_t b = 0; b < 2; b++) {
        e = (s = a) + n;
        for (size_t i = 0; i < l; i++) {
            evil_global = 1 << l - 1 - i;
            qsort(s, e - s, sizeof(uint32_t), cmpui32asc);
            if (b ^ (s[(e - s) / 2] & evil_global) > 0) while (!(*s & evil_global)) s++; else while (*(e - 1) & evil_global) e--;
            if (e - s == 1) { r[b] = *s; break; }
        }
    }
    free(ln);
    free(a);
    printf("%u\n", r[0] * r[1]);
}

int main(int argc, char** argv) {
    if (argc == 2 && !strcmp(argv[1], "1"))
        part1();
    else if (argc == 2 && !strcmp(argv[1], "2"))
        part2();
    else {
        printf("Invalid arguments.");
        return -1;
    }
    return 0;
}
