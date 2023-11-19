#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n) + O(n) => O(n)
    ///   memory: O(1)
    int lengthOfLastWord(std::string s) {
        int longestWordLength = 0;
        int i = s.size()-1;
        while (i>=0 && std::isspace(s[i]))
            i--;
        while (i>=0 && !std::isspace(s[i])) {
            longestWordLength++;
            i--;
        }

        return longestWordLength;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(lengthOfLastWord(data), result);
}

static auto testCases = testing::Values(
        Param("Hello World", 5),
        Param("   fly me   to   the moon  ", 4),
        Param("luffy is still joyboy", 6),
        Param("", 0)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
