#include <iostream>

#include "solution.hpp"

std::ostream& operator<<(std::ostream& out, std::vector<std::vector<char>>& board)
{
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board.size(); j++) {
            out << board[i][j];
            if (j + 1 < board.size()) out << " ";
        }
        out << '\n';
    }

    return out;
}

int main()
{
    Solution sol;
    std::vector<std::vector<char>> board;
    board.resize(9);

    char temp;

    for (auto& row : board) {
        row.resize(9);
        for (auto& col : row) {
            std::cin >> temp;
            col = temp;
        }
    }

    std::cout << "Before solving:\n";
    std::cout << board;

    sol.solveSudoku(board);

    std::cout << "After solving:\n";
    std::cout << board;

    std::vector<std::vector<char>> test(9, std::vector<char>(9));
    for (auto& row : test) {
        for (auto& col : row) {
            std::cin >> col;
        }
    }

    if (board == test) {
        std::cout << "Solver is correct.\n";
    }
    else {
        std::cout << "Solver is wrong.\n";
    }
}

