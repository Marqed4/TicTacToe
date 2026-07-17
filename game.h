#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>

class BoardInteractionLogic {
public:
    int game_logic();

private:
    void clear();
};

class BoardSolutionLogic {
public:
    char find_winner(char board[3][3]);
};

#endif