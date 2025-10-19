#include <stdio.h>
#include <stdint.h>
#include "bitboardcheckers.h"

int main()
{
    gameBoard game = {0, 0, 0, 0};
    // initializing game
    int turn = 0;
    int row, col;
    char dir[3];

    // black pieces set in their respective spots
    for (int r = 0; r < 3; r++)
    {
        for (int c = (r + 1) % 2; c < 8; c += 2)
        {
            game.black = setBit(game.black, rowColumnToIndex(r, c));
        }
    }

    // red pieces set in their respective spots
    for (int r = 5; r < 8; r++)
    {
        for (int c = (r + 1) % 2; c < 8; c += 2)
        {
            game.red = setBit(game.red, rowColumnToIndex(r, c));
        }
    }

    while (1)
    {
        printBoard(game);
        printf("%s's turn. Enter the piece row and column", turn == 0 ? "Red" : "Black");

        scanf("%d %d", &row, &col);

        int idx = rowColumnToIndex(row, col);
        if ((turn == 0 && !(getBit(game.red, idx) || getBit(game.redKings, idx))) ||
            (turn == 1 && !(getBit(game.black, idx) || getBit(game.blackKings, idx))))
        {
            printf("No piece there bucko. \n");
            continue;
        }

        showMoves(game, row, col, turn);
        printf("Enter direction (UL, UR, LL, LR): ");
        scanf("%2s", dir);

        int to = computeMoves(row, col, dir);
        if ((to == -1) || !isEmpty(game, to))
        {
            printf("Invalid direction or spot is taken.\n");
            continue;
        }

        movePiece(&game, idx, to, turn);

        int winner = checkWin(game);
        if (winner != 1)
        {
            printBoard(game);
            printf("%s wins!\n", winner == 0? "Red": "Black");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}