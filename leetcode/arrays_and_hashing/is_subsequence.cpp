#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, std::string, bool>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)
    bool isSubsequence(std::string s, std::string t) {
        if (!s.size())
            return true;
        if (!t.size())
            return false;
        int expectedIdx = 0;
        char expectedChar = s[expectedIdx];
        for (int i=0;i<t.size();++i) {
            if (expectedChar == t[i]) {
                if (++expectedIdx >= s.size())
                    return true;
                expectedChar = s[expectedIdx];
            }
        }
        return expectedIdx == s.size();
    }
};
class Solution2: public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)
    bool isSubsequence(std::string s, std::string t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j])
                i++;
            j++;
        }
        return i == s.size();
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(isSubsequence(data1, data2), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(isSubsequence(data1, data2), result);
}

static auto testCases = testing::Values(
        Param("abc", "ahbgdc", true),
        Param("axc", "ahbgdc", false),
        Param("", "abc", true),
        Param("as","ass", true)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
