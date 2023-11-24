#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)
    int pivotIndex(std::vector<int>& nums) {
        int totalSum = 0;
        for (int i=0;i<nums.size();++i) {
            totalSum += nums[i];
        }
        int leftSum = 0;
        for (int j=0;j<nums.size();++j) {
            if (totalSum - nums[j] == 2*leftSum)
                return j;
            leftSum += nums[j];
        }
        return -1;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(pivotIndex(data), result);
}

static auto testCases = testing::Values(
        Param({1,7,3,6,5,6}, 3),
        Param({1,2,3}, -1),
        Param({2,1,-1}, 0)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

