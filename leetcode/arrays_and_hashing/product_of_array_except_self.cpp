#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>


using Param = std::tuple<std::vector<int>, std::vector<int>>;

class Solution1 : public ::testing::TestWithParam<Param> {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        const int numsSize = nums.size();
        std::vector<int> leftProd(numsSize, 1);
        std::vector<int> rightProd(numsSize, 1);
        std::vector<int> result;
        result.reserve(numsSize);
        for (int i=1, j=numsSize-2;i<numsSize;++i,--j) {
            leftProd[i] = leftProd[i-1]*nums[i-1];
            rightProd[j] = rightProd[j+1]*nums[j+1];
        }
        for (int i=0;i<numsSize;++i) {
            result.push_back(leftProd[i] * rightProd[i]);
        }
        return result;
    }
};


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto nums = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, productExceptSelf(nums));
}


static auto testCases = testing::Values(
        Param({1,2,3,4}, {24,12,8,6}),
        Param({-1,1,0,-3,3}, {0,0,9,0,0})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);


