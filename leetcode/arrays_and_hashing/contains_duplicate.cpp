#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, bool>;
class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(nlong n) + O(n) => O(nlog n)
    ///   memory: O(1)
    bool containsDuplicate(std::vector<int>& nums) {

        std::sort(nums.begin(), nums.end());
        for (int i=0;i<nums.size()-1;++i) {
            if (nums[i] == nums[i+1])
                return true;
        }
        return false;
    }
};

class Solution2 : public testing::TestWithParam<Param>  {
public:
    ///   time: O(n)
    ///   memory: O(n)
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_map<int, int> counts;
        for (int i=0;i<nums.size();++i) {
            counts[nums[i]]+=1;
            if (counts[nums[i]] > 1)
                return true;
        }
        return false;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(containsDuplicate(data), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(containsDuplicate(data), result);
}


static auto testCases = testing::Values(
        Param({1,2,3,1}, true),
        Param({1,2,3,4}, false),
        Param({1,1,1,3,3,4,3,2,4,2}, true)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
