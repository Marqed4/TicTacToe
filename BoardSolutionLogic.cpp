#include "game.h"

char BoardSolutionLogic::find_winner(char board[3][3]) {

    char winner = ' ';

    // Check Horizontal
    for (int r = 0; r < 3; r++) {
        if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
            winner = board[r][0];
            break;
        }
    }
    if (winner != ' ') return winner;

    // Check Horizontal
    for (int c = 0; c < 3; c++) {
        if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
            winner = board[0][c];
            break;
        }
    }
    if (winner != ' ') return winner;

    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
    } else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
    }

    return winner;
}