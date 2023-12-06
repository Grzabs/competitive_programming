#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <gtest/gtest.h>


using Param = std::tuple<std::vector<std::vector<char>>, bool>;

class Solution1 : public ::testing::TestWithParam<Param> {
public:
    uint8_t charToDec(char x) const {
        return int(x)-int('0');
    }
    bool isLineValid(const std::vector<char>& line) {
        std::array<bool, 10> counts = {false};
        for (auto c : line) {
            if (c == '.')
                continue;
            auto& cellRef = counts[charToDec(c)];
            if (cellRef) {
                return false;
            }
            cellRef = true;
        }
        return true;
    }
    bool validateLines(std::vector<std::vector<char>>& board) {
        for (const auto& line : board) {
            if (!isLineValid(line))
                return false;
        }
        return true;
    }
    bool isColumnValid(std::vector<std::vector<char>>& board, int i) {
        if (i<0 || i >= board[0].size())
            return false;
        std::array<bool, 10> counts = {false};
        for (const auto& line : board) {
            const auto& character = line[i];
            if (character == '.')
                continue;
            auto& cellRef = counts[charToDec(character)];
            if (cellRef)
                return false;
            cellRef = true;
        }
        return true;
    }
    bool validateColumns(std::vector<std::vector<char>>& board) {
        for (int i=0;i<board[0].size();++i)
            if (!isColumnValid(board, i))
                return false;
        return true;
    }
    bool isGridValid(std::vector<std::vector<char>>& board, int i, int j)
    {
        std::array<bool, 10> counts = {0};
        constexpr unsigned gridStride = 3;
        for (int l=0;l<3;++l) {
            const auto& refLine = board[i*gridStride + l];
            for (int c=0;c<3;++c) {
                const auto& character = refLine[c + j*gridStride];
                if (character == '.')
                    continue;
                auto& cellRef = counts[charToDec(character)];
                if (cellRef)
                    return false;
                cellRef = true;
            }
        }
        return true;
    }
    bool validateGrids(std::vector<std::vector<char>>& board) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (!isGridValid(board, row, col))
                    return false;
            }
        }
        return true;
    }
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        // validate lines
        return validateLines(board) && validateColumns(board) && validateGrids(board);
    }
};

class Solution2 : public testing::TestWithParam<Param> {
public:
    uint8_t hashMapKey(int i, int j) {
        return (i & 0xF) << 4 | (j & 0xF);
    }
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::unordered_map<uint8_t ,std::unordered_set<uint8_t>> rows;
        std::unordered_map<uint8_t ,std::unordered_set<uint8_t>> cols;
        std::unordered_map<uint8_t, std::unordered_set<uint8_t>> grids;

        for (int row=0;row<9;row++) {
            for (int col=0;col<9;++col) {
                const auto& elementAt = board[row][col];
                if (elementAt == '.')
                    continue;
                auto& rowHashSet = rows[row];
                auto& colHashSet = cols[col];
                auto& gridHashSet = grids[hashMapKey(row / 3, col /3)];
                if (rowHashSet.find(elementAt) != rowHashSet.end() ||
                        colHashSet.find(elementAt) != colHashSet.end() ||
                        gridHashSet.find(elementAt) != gridHashSet.end()) {
                    return false;
                }

                rowHashSet.insert(elementAt);
                colHashSet.insert(elementAt);
                gridHashSet.insert(elementAt);
            }
        }
        return true;
    }
};


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto board = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, isValidSudoku(board));
}
TEST_P(Solution2, Test1) {
    auto &params = GetParam();
    auto board = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, isValidSudoku(board));
}


static auto testCases = testing::Values(
        Param({
              {'5','3','.','.','7','.','.','.','.'},
              {'6','.','.','1','9','5','.','.','.'},
              {'.','9','8','.','.','.','.','6','.'},
              {'8','.','.','.','6','.','.','.','3'},
              {'4','.','.','8','.','3','.','.','1'},
              {'7','.','.','.','2','.','.','.','6'},
              {'.','6','.','.','.','.','2','8','.'},
              {'.','.','.','4','1','9','.','.','5'},
              {'.','.','.','.','8','.','.','7','9'}
              }, true),
        Param({
                {'8','3','.','.','7','.','.','.','.'},
                {'6','.','.','1','9','5','.','.','.'},
                {'.','9','8','.','.','.','.','6','.'},
                {'8','.','.','.','6','.','.','.','3'},
                {'4','.','.','8','.','3','.','.','1'},
                {'7','.','.','.','2','.','.','.','6'},
                {'.','6','.','.','.','.','2','8','.'},
                {'.','.','.','4','1','9','.','.','5'},
                {'.','.','.','.','8','.','.','7','9'}
               } ,false)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

