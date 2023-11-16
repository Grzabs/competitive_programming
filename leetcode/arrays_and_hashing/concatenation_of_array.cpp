#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n) + O(n) => O(n)
    ///   memory: O(n)
    std::vector<int> getConcatenation(std::vector<int>& nums) {
        std::vector<int> result;
        result.insert(result.end(), nums.begin(), nums.end());
        result.insert(result.end(), nums.begin(), nums.end());
        return result;
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)  => O(n)
    ///   memory: O(n)
    std::vector<int> getConcatenation(std::vector<int>& nums) {
        std::vector<int> result;
        const int n = nums.size();
        result.reserve(n * 2);
        for (int i=0;i<n * 2;++i) {
            result.push_back(nums[i % n]);
        }
        return result;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(getConcatenation(data), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(getConcatenation(data), result);
}

static auto testCases = testing::Values(
        Param({1,2,1}, {1,2,1,1,2,1}),
        Param({1,3,2,1}, {1,3,2,1,1,3,2,1})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

