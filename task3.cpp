#include <iostream>
#include <vector>

// Function prototypes
void initializeBoard(std::vector<std::vector<char>> &board);
void displayBoard(const std::vector<std::vector<char>> &board);
bool makeMove(std::vector<std::vector<char>> &board, char currentPlayer);
bool checkWin(const std::vector<std::vector<char>> &board, char currentPlayer);
bool checkDraw(const std::vector<std::vector<char>> &board);
char switchPlayer(char currentPlayer);
bool playAgain();

int main() {
    char currentPlayer = 'X';
    bool gameWon = false;
    bool gameDraw = false;
    bool continuePlaying = true;

    do {
        std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));

        initializeBoard(board);
        displayBoard(board);

        do {
            gameWon = makeMove(board, currentPlayer);
            if (!gameWon) {
                gameDraw = checkDraw(board);
                currentPlayer = switchPlayer(currentPlayer);
            }
            displayBoard(board);
        } while (!gameWon && !gameDraw);

        if (gameWon) {
            std::cout << "Player " << currentPlayer << " wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }

        continuePlaying = playAgain();
    } while (continuePlaying);

    return 0;
}

void initializeBoard(std::vector<std::vector<char>> &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(const std::vector<std::vector<char>> &board) {
    std::cout << "  1 2 3\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
        if (i < 2) {
            std::cout << "  -----\n";
        }
    }
    std::cout << "\n";
}

bool makeMove(std::vector<std::vector<char>> &board, char currentPlayer) {
    int row, col;

    do {
        std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        std::cin >> row >> col;
        --row;
        --col;
    } while (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ');

    board[row][col] = currentPlayer;

    return checkWin(board, currentPlayer);
}

bool checkWin(const std::vector<std::vector<char>> &board, char currentPlayer) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }

    return false;
}

bool checkDraw(const std::vector<std::vector<char>> &board) {
    for (const auto &row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // If any cell is empty, the game is not a draw
            }
        }
    }
    return true; // All cells are filled, and no player has won, so it's a draw
}

char switchPlayer(char currentPlayer) {
    return (currentPlayer == 'X') ? 'O' : 'X';
}

bool playAgain() {
    char response;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}
