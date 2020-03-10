#include <array>
#include <vector>

class Solution
{
public:
    void solveSudoku(std::vector<std::vector<char>>& board);

private:
    bool solverHelper(std::vector<std::vector<char>>& board, int my_index);
    bool isValidSudoku(const std::vector<std::vector<char>>& board);
    bool isValidGroup(const std::array<char, 9>& group);
    void getValidTries(
        const std::vector<std::vector<char>>& board,
        int row_index,
        int col_index,
        std::vector<char>& validTries);

    std::array<char, 9> m_holderArray;
    std::array<bool, 9> m_trackerArray;
};

