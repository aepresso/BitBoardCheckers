#include <stdio.h>
#include <stdint.h>
#include "bitboardcheckers.h"

int main()
{
    uint64_t board = 0;

    board = setBit(board, 5);
    printf("bit 5 set: %11u\n", board);

    printBinary(board);
    printHex(board);
    return 0;
}