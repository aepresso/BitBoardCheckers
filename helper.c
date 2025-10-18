#include <stdio.h>
#include <stdint.h>

void PrintBinary(uint64_t value) // prints the 64 bit integer as binary for debugging.
{
    for (int i = 63; i >= 0; i--)
    {
        printf("%d", (int)((value >> i) & 1));
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

