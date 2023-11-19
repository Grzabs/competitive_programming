#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<std::string>, std::string>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(m*n), m - length of the first string (constant?), n - number of strings O(n)
    ///   memory: O(1)
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string prefix = "";
        for (int j=0;j<strs[0].size();++j) {
            const char ref = strs[0][j];
            for (int i = 1; i < strs.size(); ++i) {
                if (j >= strs[i].size() || ref != strs[i][j])
                    return prefix;
            }
            prefix += ref;
        }
        return prefix;
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    ///   time: O(nlong n) + O(n) => O(nlog n)
    ///   memory: O(1)
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::sort(strs.begin(), strs.end());
        std::string prefix = "";
        const int n = std::min(strs[0].size(), strs[strs.size()-1].size());
        for (int i=0;i<n;++i) {
            if (strs[0][i] != strs[strs.size()-1][i])
                break;
            prefix += strs[0][i];
        }
        return prefix;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(longestCommonPrefix(data), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(longestCommonPrefix(data), result);
}


static auto testCases = testing::Values(
        Param({{"dog", "racecar", "car"}}, ""),
        Param({{"flower","flow","flight"}}, "fl")
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
