#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "line.h"

uint32_t evil_global = 0;

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
    uint32_t  r_oxygen;
    uint32_t  r_scrubber;

    // oxygen generator rating
    start = bs;
    end   = bs + n;
    for (size_t i = 0; i < length; i++) {
        evil_global = 1 << length - 1 - i;
        qsort(start, end - start, sizeof(uint32_t), cmpui32asc);
        size_t   half = (end - start) / 2;
        if (start[half] & evil_global) {
            while (!(*start & evil_global))
                start++;
        } else {
            while (*(end - 1) & evil_global)
                end--;
        }
        if (end - start == 1) {
            r_oxygen = *start;
            break;
        }
    }

    // CO2 scrubber rating
    start = bs;
    end   = bs + n;
    for (size_t i = 0; i < length; i++) {
        evil_global = 1 << length - 1 - i;
        qsort(start, end - start, sizeof(uint32_t), cmpui32asc);
        size_t half = (end - start) / 2;
        if (start[half] & evil_global) {
            while (*(end - 1) & evil_global)
                end--;
        } else {
            while (!(*start & evil_global))
                start++;
        }
        if (end - start == 1) {
            r_scrubber = *start;
            break;
        }
    }

    free(bs);
    printf("%u\n", r_oxygen * r_scrubber);
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
