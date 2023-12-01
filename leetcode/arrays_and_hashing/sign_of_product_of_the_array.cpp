#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)
    int arraySign(std::vector<int>& nums) {
        int negative = 0;
        for (int i=0;i<nums.size();++i) {
            if (nums[i] == 0)
                return 0;
            if (nums[i] < 0)
                negative++;
        }
        return negative % 2 != 0 ? -1 : 1;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, arraySign(nums));
}

static auto testCases = testing::Values(
        Param({-1,-2,-3,-4,3,2,1}, 1),
        Param({1,5,0,2,-3}, 0),
        Param({-1,1,-1,1,-1}, -1)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
