#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 5; // Size of the grid (dots)

class ConnectTheDots {
private:
    vector<vector<char>> horizontal; // Horizontal connections
    vector<vector<char>> vertical;   // Vertical connections
    vector<vector<char>> boxes;      // Completed boxes
    int player;

public:
    ConnectTheDots() : horizontal(SIZE, vector<char>(SIZE - 1, ' ')),
                       vertical(SIZE - 1, vector<char>(SIZE, ' ')),
                       boxes(SIZE - 1, vector<char>(SIZE - 1, ' ')),
                       player(1) {}

    void printBoard() {
        for (int i = 0; i < SIZE; ++i) {
            // Print horizontal lines
            for (int j = 0; j < SIZE; ++j) {
                cout << (j == 0 ? " " : "|") << " ";
                if (j < SIZE - 1) {
                    cout << horizontal[i][j] << " ";
                }
            }
            cout << endl;

            // Print vertical lines for boxes
            if (i < SIZE - 1) {
                for (int j = 0; j < SIZE; ++j) {
                    cout << " " << vertical[i][j] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    bool makeMove(int x, int y, char orientation) {
        if (orientation == 'H' && y < SIZE - 1 && horizontal[x][y] == ' ') {
            horizontal[x][y] = (player == 1 ? '-' : '=');
            return true;
        } else if (orientation == 'V' && x < SIZE - 1 && vertical[x][y] == ' ') {
            vertical[x][y] = (player == 1 ? '|' : '/');
            return true;
        }
        return false;
    }

    void checkBoxes() {
        for (int i = 0; i < SIZE - 1; ++i) {
            for (int j = 0; j < SIZE - 1; ++j) {
                if (horizontal[i][j] != ' ' && horizontal[i + 1][j] != ' ' &&
                    vertical[i][j] != ' ' && vertical[i][j + 1] != ' ') {
                    boxes[i][j] = (player == 1 ? 'X' : 'O');
                }
            }
        }
    }

    bool isGameOver() {
        for (int i = 0; i < SIZE - 1; ++i) {
            for (int j = 0; j < SIZE - 1; ++j) {
                if (boxes[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer() {
        player = (player == 1) ? 2 : 1;
    }

    void play() {
        while (true) {
            printBoard();
            cout << "Player " << player << ", enter your move (row, column, orientation [H/V]): ";
            int x, y;
            char orientation;
            cin >> x >> y >> orientation;

            if (makeMove(x, y, orientation)) {
                checkBoxes();
                if (isGameOver()) {
                    printBoard();
                    cout << "Game over! Player " << (player == 1 ? 1 : 2) << " wins!\n";
                    break;
                }
                switchPlayer();
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }
};

int main() {
    ConnectTheDots game;
    game.play();
    return 0;
}
