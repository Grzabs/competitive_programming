#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, std::string, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n*m)
    ///   memory: O(1)
    int strStr(std::string haystack, std::string needle) {
        for (int i=0;i<haystack.size();i++) {
            int j = 0;
            for (;j<needle.size();++j) {
                if (i+j >= haystack.size())
                    return -1;
                if (haystack[i+j] != needle[j]) {
                    break;
                }
            }
            if (j == needle.size())
                return i;
        }
        return -1;
    }
};
// KMP
class Solution2: public testing::TestWithParam<Param> {
public:
    ///   time: O(n+m)
    ///   memory: O(1)
    bool strStr(std::string haystack, std::string needle) {

    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto haystack = std::get<0>(parameter);
    auto needle = std::get<1>(parameter);
    auto position = std::get<2>(parameter);
    EXPECT_EQ(position, strStr(haystack, needle));
}
/*
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto haystack = std::get<0>(parameter);
    auto needle = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, strStr(haystack, needle));
}
*/
static auto testCases = testing::Values(
        Param("sadbutsad", "sad", 0),
        Param("leetcode", "leeto", -1),
        Param("mississippi", "issip", 4),
        Param("mississippi", "issi", 1)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
//INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
