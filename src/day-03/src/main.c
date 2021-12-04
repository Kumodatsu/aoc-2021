#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAGIC_NUMBER        42
#define UNHELPFUL_ERROR_MSG "invalid arguments"

uint32_t evil_global;

int rdln(FILE* f, uint32_t* b, size_t* ol) {
    int c;
    size_t s = MAGIC_NUMBER, l = 0;
    char* ln = malloc(s * sizeof(char));
    while (1) {
        if ((c = fgetc(f)) == EOF)
            if (l == 0) { free(ln); return l; } else break;
        else if (c == '\n') break;
        ln[l++] = c;
        ln = l == s ? realloc(ln, (s *= 2) * sizeof(char)) : ln;
    }
    *ol = l;
    *b = strtoul(ln, 0, 2);
    free(ln);
    return 1;
}

int cmpui32asc(const void* a, const void* b) {
    return (*(uint32_t*) a & evil_global) - (*(uint32_t*) b & evil_global);
}

int main(int argc, char** argv) {
    uint32_t p = (argc == 2 ? strtoul(argv[1], 0, 10) : 0) - 1;
    if (p > 1) { printf(UNHELPFUL_ERROR_MSG); return -1; }
    size_t c = MAGIC_NUMBER, l = 0;
    uint32_t *a = malloc(c * sizeof(uint32_t)), n = 0, *o = 0, g = 0, b;
    while (rdln(stdin, &b, &l)) {
        o = o || p ? o : calloc(l, sizeof(int32_t));
        (a = ++n > c ? realloc(a, (c *= 2) * sizeof(uint32_t)) : a)[n - 1] = b;
        for (size_t i = 0; i < (1 - p) * l; i++) o[i] += (b & 1 << i) > 0;
    }
    uint32_t *s, *e, r[2];
    for (uint32_t v = 0; v < p * 2; v++) {
        e = (s = a) + n;
        for (size_t i = 0; i < l; i++) {
            evil_global = 1 << l - 1 - i;
            qsort(s, e - s, sizeof(uint32_t), cmpui32asc);
            if (v ^ (s[(e - s) / 2] & evil_global) > 0)
                while (!(*s & evil_global)) s++;
            else
                while (*(e - 1) & evil_global) e--;
            if (e - s == 1) { r[v] = *s; break; }
        }
    }
    for (size_t i = 0; i < (1 - p) * l; i++) g |= (o[i] > n / 2) * 1 << i;
    free(a);
    free(o);
    printf("%u\n", (1 - p) * (g * (~g & (1 << l) - 1)) + p * r[0] * r[1]);
    return 0;
}
