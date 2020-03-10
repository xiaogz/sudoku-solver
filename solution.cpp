#include "solution.hpp"

namespace
{

constexpr const int k3x3GridSize = 3;
constexpr const int kBoardSize = 9;
constexpr const int kBoardGrids = 81;
constexpr const std::array<char, 9> kAllTryChars = {'1','2','3','4','5','6','7','8','9'};

void getGridGroup(
    const std::vector<std::vector<char>>& board,
    int row_index,
    int col_index,
    std::array<char, 9>& group)
{
    for (int i = 0; i < k3x3GridSize; i++) {
        // unrolling inner loop
        group[i * k3x3GridSize + 0] = board[row_index + i][col_index + 0];
        group[i * k3x3GridSize + 1] = board[row_index + i][col_index + 1];
        group[i * k3x3GridSize + 2] = board[row_index + i][col_index + 2];
    }
}

}

void Solution::getValidTries(
    const std::vector<std::vector<char>>& board,
    int row_index,
    int col_index,
    std::vector<char>& validTries)
{
    //clean up before use
    validTries.clear();
    validTries.reserve(9);
    for (auto& isFilled : m_trackerArray) {
        isFilled = false;
    }

    for (auto& row_num : board[row_index]) {
        if (row_num == '.')
            continue;

        m_trackerArray[static_cast<int>(row_num - '0') - 1] = true;
    }

    for (auto& row : board) {
        auto& col_num = row[col_index];

        if (col_num == '.')
            continue;

        m_trackerArray[static_cast<int>(col_num - '0') - 1] = true;
    }

    int gridRow_start = (row_index / k3x3GridSize) * k3x3GridSize;
    int gridCol_start = (col_index / k3x3GridSize) * k3x3GridSize;
    int gridRow_limit = gridRow_start + k3x3GridSize;
    int gridCol_limit = gridCol_start + k3x3GridSize;

    for (int gri = gridRow_start; gri < gridRow_limit; gri++) {
        for (int gci = gridCol_start; gci < gridCol_limit; gci++) {
            auto& grid_num = board[gri][gci];

            if (grid_num == '.')
                continue;

            m_trackerArray[static_cast<int>(grid_num - '0') - 1] = true;
        }
    }

    for (unsigned int i = 0; i < m_trackerArray.size(); i++) {
        const auto& isFilled = m_trackerArray[i];

        if (isFilled)
            continue;

        validTries.push_back(static_cast<char>(i + 1 + '0'));
    }
}

void Solution::solveSudoku(std::vector<std::vector<char>>& board)
{
    // call a helper function that does the actual filling in and starts the recursion
    solverHelper(board, 0);
}

bool Solution::solverHelper(std::vector<std::vector<char>>& board, int my_index)
{
    auto& currentCell = board[my_index / kBoardSize][my_index % kBoardSize];

    const bool isAtEnd = ((my_index + 1) >= kBoardGrids);
    const bool shouldGenerateTries = (currentCell == '.');

    if (!shouldGenerateTries) {
        if (isAtEnd) return isValidSudoku(board);

        return solverHelper(board, my_index + 1);
    }

    std::vector<char> validTries;
    getValidTries(board, my_index / kBoardSize, my_index % kBoardSize, validTries);

    if (validTries.empty()) {
        return false;
    }

    for (auto& tryChar : validTries) {
        currentCell = tryChar;

        if (isAtEnd) {
            if (isValidSudoku(board)) {
                return true;
            }
            continue;
        }

        if (solverHelper(board, my_index + 1)) {
            return true;
        }

        currentCell = '.';
    }

    return false;
}

bool Solution::isValidSudoku(const std::vector<std::vector<char>>& board)
{
    // use temp array and figure out ways to fill it up with rows, columns, and 3x3 grid
    // call helper function to verify that the temp array is valid
    // use 0 to represent dots/empty cell

    // check all the rows
    for (const auto& row : board) {
        for (int i = 0; i < kBoardSize; i++) {
            m_holderArray[i] = row[i];
        }

        if (!isValidGroup(m_holderArray)) {
            return false;
        }
    }

    // check all the columns
    for (int col_index = 0; col_index < kBoardSize; col_index++) {
        for (int i = 0; i < kBoardSize; i++) {
            m_holderArray[i] = board[i][col_index];
        }

        if (!isValidGroup(m_holderArray)) {
            return false;
        }
    }

    // check all the 3x3 grids
    for (int row_index = 0; row_index < kBoardSize; row_index += k3x3GridSize) {
        for (int col_index = 0; col_index < kBoardSize; col_index += k3x3GridSize) {
            getGridGroup(board, row_index, col_index, m_holderArray);

            if (!isValidGroup(m_holderArray)) {
                return false;
            }
        }
    }

    return true;
}

// 1-9 should be tested; 0 is empty and is skipped
bool Solution::isValidGroup(const std::array<char, 9>& group)
{
    // clean up before use
    for (auto& isFilled : m_trackerArray) {
        isFilled = false;
    }

    for (const auto& c : group) {
        if (c == '.') continue;

        auto& isFilled = m_trackerArray[static_cast<int>(c - '0') - 1];
        if (isFilled) {
            return false;
        }
        else {
            isFilled = true;
        }
    }

    return true;
}

