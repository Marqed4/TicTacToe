#include <unordered_map>
#include <iostream>
#include <string>

#include "game.h"

// Empty Terminal
void BoardInteractionLogic::clear() {
    // https://stackoverflow.com/questions/6486289/
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H" << std::flush;
}

int BoardInteractionLogic::game_logic() {

    // Board Matrix
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };

    // Variables
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;
    auto r = -1, c = -1;
    char winner = ' ';
    bool quit = false;

    // Objects
    BoardSolutionLogic solver;

    // Player names map
    std::unordered_map<char, std::string> names;

    // Intake player names/identity & move to names map.
    auto setName = [&names](char c) {
        std::string name;
        if (c == 'X') {
            std::cout << "Who will have Noughts: ";
        } else {
            std::cout << "Who will have Crosses: ";
        }

        std::cin >> name;
        names[c] = name;
    };

    // Check Exit
    enum class InputStatus { Ok, Retry };

    auto checkExit = [&](const std::string& rowInput, const std::string& colInput) -> InputStatus {
        try {
            r = std::stoi(rowInput);
            c = std::stoi(colInput);
        } catch (...) {
            std::cerr << "Error: Please enter a integer, values: \"1-3\" or 'q' to exit." << std::endl;
            return InputStatus::Retry;
        }

        return InputStatus::Ok;
    };

    setName('O');
    setName('X');

    // Main game loop: draw board, get and validate player input, place move
    for (int i = 0; i < 9; i++) {

        // Empty Terminal
        clear();

        // Draw Board
        std::cout << "     |     |     " << std::endl;
        std::cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << std::endl;
        std::cout << "_____|_____|_____" << std::endl;
        std::cout << "     |     |     " << std::endl;
        std::cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << std::endl;
        std::cout << "_____|_____|_____" << std::endl;
        std::cout << "     |     |     " << std::endl;
        std::cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << std::endl;
        std::cout << "     |     |     " << std::endl;

        // Display Winner
        if (winner != ' ') {
            printf("\nPlayer: %s is the winner!", names[winner].c_str());
            break;
        }

        std::cout << "Current Player is " << currentPlayer << std::endl;

        // Prompt and validate player input
        while (true) {
            std::cout << "Enter q to quit." << std::endl;
            std::string rowInput, colInput;
            std::cout << "Enter Row: ";
            std::cin >> rowInput;
            if (rowInput == "q") {
                std::cout << "\nYou ended the game." << std::endl;
                quit = true;
                break;
            }

            std::cout << "Enter Column: ";
            std::cin >> colInput;
            // Exit Check
            if (colInput == "q") {
                std::cout << "\nYou ended the game." << std::endl;
                quit = true;
                break;
            }

            InputStatus status = checkExit(rowInput, colInput);
            if (status == InputStatus::Retry) {
                continue;
            }

            if (r < 1 || c < 1) { 
                std::cerr << "Error: Input too small, please try again." << std::endl;
            } else if (r > 3 || c > 3) {
                std::cerr << "Error: Input too large, please try again." << std::endl;
            } else if (board[r - 1][c - 1] != ' ') {
                std::cerr << "Error: Plot taken, try another." << std::endl;
            } else {
                break;
            }

            // Reset variables
            r = -1;
            c = -1;
            // Clear error flags
            std::cin.clear();
            /*
            Discards current 10,000 values. Remvoing and
            discarding characters from the input buffer.
            */
            std::cin.ignore(10000, '\n');
        }

        if (quit) break;

        // Apply move and switch turns
        board[r - 1][c - 1] = currentPlayer;
        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;

        winner = solver.find_winner(board);
    }
    
    return 0;
}