#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "line.h"

uint32_t evil_global;

int cmpui32asc(const void* a, const void* b) {
    return (*(uint32_t*) a & evil_global) - (*(uint32_t*) b & evil_global);
}

void part1(void) {
    size_t   length = 0;
    uint32_t gamma  = 0;
    {
        uint32_t* ones = NULL;
        uint32_t  n    = 0;
        {
            char* line = NULL;
            while (read_line(stdin, &line, &length)) {
                uint32_t b = strtoul(line, NULL, 2);
                if (!ones)
                    ones = calloc(length, sizeof(int32_t));
                for (size_t i = 0; i < length; i++)
                    ones[i] += (b & 1 << i) > 0;
                n++;
            }
            free(line);
        }
        for (size_t i = 0; i < length; i++)
            if (ones[i] > n / 2)
                gamma |= 1 << i;
        free(ones);
    }
    uint32_t epsilon     = ~gamma & (1 << length) - 1;
    uint32_t consumption = gamma * epsilon;
    printf("%u\n", consumption);
}

void part2(void) {
    size_t    bs_cap = 64;
    uint32_t* bs     = malloc(bs_cap * sizeof(uint32_t));
    size_t    length = 0;
    uint32_t  n      = 0;

    {
        char* line = NULL;
        while (read_line(stdin, &line, &length)) {
            uint32_t b = strtoul(line, NULL, 2);
            n++;
            if (n > bs_cap) {
                bs_cap *= 2;
                bs = realloc(bs, bs_cap * sizeof(uint32_t));
            }
            bs[n - 1] = b;
        }
        free(line);
    }

    uint32_t* start;
    uint32_t* end;
    uint32_t  r[2];
    for (uint32_t b = 0; b < 2; b++) {
        start = bs;
        end   = bs + n;
        for (size_t i = 0; i < length; i++) {
            evil_global = 1 << length - 1 - i;
            qsort(start, end - start, sizeof(uint32_t), cmpui32asc);
            if (b ^ (start[(end - start) / 2] & evil_global) > 0) {
                while (!(*start & evil_global))
                    start++;
            } else {
                while (*(end - 1) & evil_global)
                    end--;
            }
            if (end - start == 1) {
                r[b] = *start;
                break;
            }
        }
    }

    free(bs);
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
