#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bitboardcheckers.h"

int main()
{
    gameBoard game = {0, 0, 0, 0};
    // initialiszing game
    int turn = 0;
    int row, col;
    char dir[3];

    initBoard(&game);

    while (1)
    {
        printBoard(game);
        printf("%s's turn.\nEnter the piece row and column (Type Num [SPACE] Num): ", turn == 0 ? "Red" : "Black");

        if (scanf("%d %d", &row, &col) != 2)
        {
            printf("You cannot do that try again.\n");
            while (getchar() != '\n')
                ; // clear buffer
            continue;
        }

        int idx = rowColumnToIndex(row, col);

        // checking if there is actually a piece that the player chooses.
        if ((turn == 0 && !(getBit(game.red, idx) || getBit(game.redKings, idx))) ||
            (turn == 1 && !(getBit(game.black, idx) || getBit(game.blackKings, idx))))
        {
            printf("No piece there bucko. \n");
            continue;
        }

        showMoves(game, row, col, turn);
        printf("Enter direction (UL, UR, LL, LR): ");
        scanf("%2s", dir);

        int to = computeMoves(row, col, dir, 1);
        if ((to == -1) || !isEmpty(game, to))
        {
            printf("Invalid direction or spot is taken.\n");
            continue;
        }

        int jumpTo = computeMoves(row, col, dir, 2);
        int midPiece = computeMoves(row, col, dir, 1);
        int canCapture = 0;
        int capturedIdx = -1; // default no capture yet

        if (jumpTo != -1 && isEmpty(game, jumpTo)) // if this is a valid move and is empty
        {
            int enemy = 0;
            if (turn == 0)
            {
                enemy = (getBit(game.black, midPiece) || getBit(game.blackKings, midPiece));
            }
            else
            {
                enemy = (getBit(game.red, midPiece) || getBit(game.redKings, midPiece));
            }
            if (enemy)
            {
                canCapture = 1;
            }

            if (canCapture)
            {
                capturedIdx = midPiece;
            }
        }

        if (capturedIdx != -1)
        {
            printf("Capture perfomed!\n");
            movePiece(&game, idx, jumpTo, turn, capturedIdx);
        }
        else
        {
            if (to == -1 || !isEmpty(game, to))
            {
                printf("Invalid direction or occupied\n");
            }
            movePiece(&game, idx, to, turn, -1);
        }

        int winner = checkWin(game);
        if (winner != -1)
        {
            printBoard(game);
            printf("%s wins!\n", winner == 0 ? "Red" : "Black");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}