#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::string, std::string, bool>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(n)
    bool wordPattern(std::string pattern, std::string s) {
        std::vector<std::string> split;
        int i = 0;
        int prev = 0;
        while (i < s.size()) {
            if (s[i] == ' ') {
                split.push_back(s.substr(prev, i-prev));
                prev = i+1;
            }
            i++;
        }
        split.push_back(s.substr(prev, i-prev));
        if (split.size() != pattern.size())
            return false;

        std::unordered_map<char, std::string> mapPS;
        std::unordered_map<std::string, char> mapSP;
        for (int i=0;i<pattern.size();++i) {
            auto it1 = mapPS.find(pattern[i]);
            auto it2 = mapSP.find(split[i]);
            if (it1 != mapPS.end() && it1->second != split[i]
                || it2 != mapSP.end() && it2->second != pattern[i])
                return false;
            if (it1 == mapPS.end() && it2 == mapSP.end()) {
                mapPS[pattern[i]] = split[i];
                mapSP[split[i]] = pattern[i];
            }
        }
        return true;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto pattern = std::get<0>(parameter);
    auto s = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, wordPattern(pattern, s));
}

static auto testCases = testing::Values(
        Param("abba", "dog cat cat dog", true),
        Param("abba", "dog cat cat fish", false),
        Param("aaaa", "dog cat cat dog", false)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
//INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

