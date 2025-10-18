#include <stdio.h>
#include <stdint.h>

uint64_t setBit(uint64_t value, int position)
{
    if (position < 0 || position >= 64)
        return value;                  // ensures that the position is valid
    return value | (1ULL << position); // sets value of that position
};

uint64_t clearBit(uint64_t value, int position)
{
    if (position < 0 || position >= 64) // checks valid position
        return value;
    return value & ~(1ULL << position); // clears bit that doesn't have valid True for AND operator
};

uint64_t toggleBit(uint64_t value, int position)
{
    if (position < 0 || position >= 64)
        return value;
    return value ^ (1ULL << position); // uses XOR to make flip the big or toggle
}

uint64_t getBit(uint64_t value, int position)
{
    if (position < 0 || position >= 64)
        return value;
    return (value >> position) & 1;
}

uint64_t countBits(uint64_t value) // iterates the integer untill all bits have been shifted right to 0
{                                  // while checkings for one

    int count = 0;
    while (value)
    {
        count += value & 1ULL;
        value = value >> 1;
    }
}

// shift operations

uint64_t shiftRight(uint64_t value, int n)
{
    return value >> n;
}

uint64_t shiftLeft(uint64_t value, int n)
{
    return value << n;
}

void printBinary(uint64_t value) // prints the 64 bit integer as binary for debugging.
{
    for (int i = 63; i >= 0; i--)
    {
        printf("%d", (int)((value >> i) & 1));
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

void printHex(uint64_t value) //prints the hex value
{
    printf("0x%016llX\n", value);
}
