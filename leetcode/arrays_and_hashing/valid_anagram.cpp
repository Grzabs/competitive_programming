#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, std::string, bool>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(nlong n) + O(nlg n) => O(nlog n)
    ///   memory: O(1)
    bool isAnagram(std::string s, std::string t) {
        if (!s.size() || !t.size() || s.size() != t.size()) {
            return false;
        }
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        return s == t;
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(n)
    bool isAnagram(std::string s, std::string t) {
        if (!s.size() || !t.size() || s.size() != t.size()) {
            return false;
        }
        std::unordered_map<char, int> c;
        for (int i=0;i<s.size();++i) {
            c[s[i]]++;
        }
        for (int i=0;i<t.size();++i) {
            c[t[i]]--;
        }
        for (auto& [key, val] : c) {
            if (val != 0)
                return false;
        }
        return true;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(isAnagram(data1, data2), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(isAnagram(data1, data2), result);
}

static auto testCases = testing::Values(
        Param("anagram", "nagaram", true),
        Param("rat", "car", false)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

