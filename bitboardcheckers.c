#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//  ----    GAME STRUCTURE  ----
typedef struct
{
    uint64_t red;
    uint64_t black;
    uint64_t redKings;
    uint64_t blackKings;
} gameBoard;

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

int isRedPiece(const gameBoard *g, int idx)
{
    return getBit(g->red, idx) || getBit(g->redKings, idx);
}

int isBlackPiece(const gameBoard *g, int idx)
{
    return getBit(g->black, idx) || getBit(g->blackKings, idx);
}

int isRedKing(const gameBoard *g, int idx)
{
    return getBit(g->redKings, idx);
}

int isBlackKing(const gameBoard *g, int idx)
{
    return getBit(g->blackKings, idx);
}
// converting the row and column format to binary index.
int rowColumnToIndex(int row, int col)
{
    return row * 8 + col;
}

// to print board
void printBoard(gameBoard board)
{
    printf("\n  0  1  2  3  4  5  6  7\n");
    for (int r = 7; r >= 0; r--)
    {
        printf("%d ", r);
        for (int c = 0; c < 8; c++)
        {
            int idx = rowColumnToIndex(r, c);
            if (getBit(board.redKings, idx))
                printf("R  ");
            else if (getBit(board.red, idx))
                printf("r  ");
            else if (getBit(board.blackKings, idx))
                printf("B  ");
            else if (getBit(board.black, idx))
                printf("b  ");
            else
            {
                if ((r + c) % 2 == 1)
                    printf(".  ");
                else
                    printf("   ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// //  ----    MOVING FUNCTIONS    ----
// this functions checks if a position is empty.
int isEmpty(gameBoard board, int position)
{
    return !(getBit(board.red, position) || getBit(board.black, position) ||
             getBit(board.redKings, position) || getBit(board.blackKings, position));
}

// function to move piece this assumes that the move has been validated
// player 0 is red player 1 is black
void movePiece(gameBoard *board, int fromPos, int toPos, int player)
{
    if (player == 0)
    {
        if (getBit(board->redKings, fromPos))
        {
            board->redKings = clearBit(board->redKings, fromPos);
            board->redKings = setBit(board->redKings, toPos);
        }
        else
        {
            board->red = clearBit(board->red, fromPos);
            board->red = setBit(board->red, toPos);
            if (toPos >= 56)
                board->redKings = setBit(board->redKings, toPos); // promotion to kings
        }
    }
    else
    {
        if (getBit(board->blackKings, fromPos))
        {
            board->blackKings = clearBit(board->blackKings, fromPos);
            board->blackKings = setBit(board->blackKings, toPos);
        }
        else
        {
            board->black = clearBit(board->black, fromPos);
            board->black = setBit(board->black, toPos);
            if (toPos <= 7)
                board->blackKings = setBit(board->blackKings, toPos); // promotes to king if on the last row.
        }
    }
}

// computing directions which a piece can move
int computeMoves(int row, int col, const char *dir)
{
    if (strcmp(dir, "UL") == 0)
        return rowColumnToIndex(row + 1, col - 1);
    if (strcmp(dir, "UR") == 0)
        return rowColumnToIndex(row + 1, col + 1);
    if (strcmp(dir, "LL") == 0)
        return rowColumnToIndex(row - 1, col - 1);
    if (strcmp(dir, "LR") == 0)
        return rowColumnToIndex(row - 1, col + 1);
    return -1;
}

// showing directions to user
void showMoves(gameBoard board, int row, int col, int player)
{
    int idx = rowColumnToIndex(row, col);
    int isKing = (player == 0) ? getBit(board.redKings, idx) : getBit(board.blackKings, idx);

    printf("Available Moves: \n");
    if (player == 0 || isKing)
    {
        if (row + 1 < 8 && col - 1 >= 0  && isEmpty(board, rowColumnToIndex(row + 1, col -1)))
            printf("UL (Upper Left)\n");
        if (row + 1 < 8 && col + 1 < 8 && isEmpty(board, rowColumnToIndex(row + 1, col + 1)))
            printf("UR (Upper Right) \n");
    }
    if (player == 1 || isKing)
    {
        if (row - 1 >= 0 && col - 1 >= 0 && isEmpty(board, rowColumnToIndex(row - 1, col - 1)))
            printf("LL (Lower Left)\n");
        if (row - 1 >= 0 && col + 1 < 8 && isEmpty(board, rowColumnToIndex(row - 1, col + 1)))
            printf("LR (Lower Right)\n");
    }
}
//  ----    CHECK WIN CONDITION ----
int checkWin(gameBoard board)
{
    if (board.red == 0 && board.redKings == 0)
        return 1; // black wins this game
    if (board.black == 0 && board.blackKings == 0)
        return 0; // red wins this game
    return -1;
}
