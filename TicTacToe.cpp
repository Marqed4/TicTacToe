#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };

    // Variables
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;

    int r = -1, c = -1;

    // Board Display & Some Player Logic
    for (int i = 0; i < 9; i++) {
        cout << "    |  |    " << endl;
        cout << " " << board[0][0] << "  |  " << board[0][1] << " | " << board[0][2] << endl;
        cout << "____|___|____" << endl;
        cout << "    |  |    " << endl;
        cout << " " << board[1][0] << "  |  " << board[1][1] << " | " << board[1][2] << endl;
        cout << "____|___|____" << endl;
        cout << "    |  |    " << endl;
        cout << " " << board[2][0] << "  |  " << board[2][1] << " | " << board[2][2] << endl;
        cout << "    |  |    " << endl;

        cout << "Current Player is " << currentPlayer << endl;
        while (true) { 
            cout << "Please, suggest row/col to plot from 1-3 on the board. \n E.g., type: \"1 2\" or \"2 3\". \n Enter:";
            cin >> r >> c;

            if (r < 1 || r > 3 || c < 1 || c > 3 || !std::isdigit(r) || !std::isdigit(c)) {
                cout << "Invalid input for a plot, please try again." << endl;
            } else if (board[r][c] != ' ') {
                cout << "Plot taken, try another." << endl;
            } else {
                break;
            }
        }

        board[r - 1][c - 1] = currentPlayer;
        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
    }
}