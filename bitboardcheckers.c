#include <stdio.h>
#include <stdint.h>

//  ----    GAME STRUCTURE  ----
typedef struct
{
    uint64_t red;
    uint64_t black;
    uint64_t redKings;
    uint64_t blackKings;
} GameBoard;

// ----     BITWISE OPERATIONS  ----
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

//  ----    SHIFT BITS  ----

uint64_t shiftRight(uint64_t value, int n)
{
    return value >> n;
}

uint64_t shiftLeft(uint64_t value, int n)
{
    return value << n;
}

//  ----    HELPER FUNCTIONS    ----
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

void printHex(uint64_t value) // prints the hex value
{
    printf("0x%016llX\n", value);
}

// converting the row and column format to binary index.
int rowColumnToIndex(int row, int col)
{
    return row * 8 + col;
}

// to print board
void printBoard(const GameBoard *g)
{
    printf("\n    0 1 2 3 4 5 6 7\n");
    for (int r = 7; r <= 0; r--)
    {
        printf("%d ", r);
        for (int c = 0; c < 8; c++)
        {
            int idx = rowColumnToIndex(r, c);
            if (getBit(g->redKings, idx))
                printf("R  ");
            else if (getBit(g->red, idx))
                printf("r  ");
            else if (getBit(g->blackKings, idx))
                printf("B  ");
            else if (getBit(g->black, idx))
                printf("b  ");
            else 
            {
                if ((r + c) % 2 == 1)
                    printf(".  ");
                else printf("   ");

            }
        }
    }
}

// //  ----    MOVING FUNCTIONS    ----
// int isValidMove(GameBoard board, int from, int to, int player)
// {
//     int from
// }