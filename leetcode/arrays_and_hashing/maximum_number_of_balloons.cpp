#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(n)
    int maxNumberOfBalloons(std::string text) {
        std::unordered_map<char,int> count;
        for (const auto& c : text) {
            count[c]++;
        }
        return std::min(count['b'], std::min(count['a'],
               std::min(count['l']/2, std::min(count['o']/2, count['n']))));
    }
};

class Solution2 : public testing::TestWithParam<Param> {
public:
    std::unordered_map<char,int> getCharCount(const std::string& word) {
        std::unordered_map<char,int> count;
        for (const auto& c : word) {
            count[c]++;
        }
        return count;
    }
    // cpu: O(n)
    // memory: O(n)
    int maxNumberOfBalloons(std::string text) {
        auto targetWordFrequency = getCharCount("balloon");
        auto thisWordFrequency = getCharCount(text);

        int res = text.size();
        for (const auto& [letter, count] : targetWordFrequency) {
            res = std::min(res,  thisWordFrequency[letter] / count);
        }
        return res;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, maxNumberOfBalloons(nums));
}

TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, maxNumberOfBalloons(nums));
}

static auto testCases = testing::Values(
        Param("nlaebolko", 1),
        Param("loonbalxballpoon", 2),
        Param("leetcode", 0),
        Param("bbaallloooonn", 1)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

