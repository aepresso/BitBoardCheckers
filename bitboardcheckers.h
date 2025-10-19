#ifndef BITBOARDCHECKERS_H // header file for operations
#define BITBOARDCHECKERS_H

#include <stdint.h> 

typedef struct
{
    uint64_t red;
    uint64_t black;
    uint64_t redKings;
    uint64_t blackKings;
} gameBoard;

uint64_t setBit(uint64_t value, int position);
uint64_t clearBit(uint64_t value, int position);
uint64_t toggleBit(uint64_t value, int position);
uint64_t getBit(uint64_t value, int position);
void printBinary(uint64_t value);
void printHex(uint64_t value);
void printBoard(gameBoard board);
int isRedPiece(const gameBoard *g, int idx);
int isBlackPiece(const gameBoard *g, int idx);
int isRedKing(const gameBoard *g, int idx);
int isBlackKing(const gameBoard *g, int idx);
int rowColumnToIndex(int row, int col);
int isEmpty(gameBoard board, int position);
void movePiece(gameBoard *board, int fromPos, int toPos, int player);
int computeMoves(int row, int col, const char *dir);
void showMoves(gameBoard board, int row, int col, int player);
int checkWin(gameBoard board);

#endif
