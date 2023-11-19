#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<std::string>, std::vector<std::vector<std::string>>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time:
    ///   memory: O(1)
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (auto& anagram : strs) {
            std::string key{anagram};
            std::sort(key.begin(), key.end());
            map[key].push_back(std::move(anagram));
        }
        std::vector<std::vector<std::string>> result;
        result.reserve(map.size());
        for (auto& [key, value] : map) {
            result.push_back(std::move(value));
        }
        return result;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(groupAnagrams(data), result);
}

static auto testCases = testing::Values(
        Param({{"eat","tea","tan","ate","nat","bat"}}, {{"bat"},{"nat","tan"},{"ate","eat","tea"}}),
        Param({{""}}, {{""}}),
        Param({{"a"}}, {{"a"}})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

