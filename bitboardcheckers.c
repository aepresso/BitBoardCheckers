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
