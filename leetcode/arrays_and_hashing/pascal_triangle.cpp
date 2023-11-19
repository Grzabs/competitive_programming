#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<int, std::vector<std::vector<int>>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n^2)
    ///   memory: O(n^2)
    std::vector<std::vector<int>> generate(int numRows) {
        std::vector<std::vector<int>> result(numRows);
        result[0]={1};
        for (int rowNr=1;rowNr<numRows;++rowNr) {
            const int rowElements = rowNr+1;
            const auto& prevRow = result[rowNr-1];
            auto& currentRow = result[rowNr];
            currentRow.reserve(rowElements);
            currentRow.push_back(1);
            for (int j=1;j<rowElements-1;++j) {
                currentRow.push_back(prevRow[j-1] + prevRow[j]);
            }
            currentRow.push_back(1);
        }
        return result;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(generate(data), result);
}

static auto testCases = testing::Values(
        Param(5, {{1}, {1,1}, {1,2,1},{1,3,3,1},{1,4,6,4,1}}),
        Param(1, {{1}})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

