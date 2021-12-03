#include <stdlib.h>
#include <stdint.h>
#include "Line.h"

int main(void) {
    size_t   length = 0;
    uint32_t gamma  = 0;
    {
        int32_t* ones = NULL;
        uint32_t n    = 0;
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
    return 0;
}
