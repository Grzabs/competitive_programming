#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    void sortColors(std::vector<int>& nums) {
        int nRed = 0;
        int nWhite = 0;
        for (int i=0;i<nums.size();++i) {
            if (nums[i] == 0)
                nRed++;
            if (nums[i] == 1)
                nWhite++;
        }
        for (int i=0;i<nums.size();++i) {
            if (nRed-- > 0)
                nums[i] = 0;
            else if (nWhite-->0)
                nums[i]= 1;
            else
                nums[i] = 2;
        }
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    void sortColors(std::vector<int>& nums) {
        if (nums.size() == 1)
            return;
       int l = 0;
       int r = nums.size()-1;
       int i = 0;
       while (i <= r) {
           if (nums[i] == 0)
               std::swap(nums[i], nums[l++]);
           if (nums[i] == 2) {
               std::swap(nums[i], nums[r--]);
               i -= 1;
           }
           i += 1;
       }
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    sortColors(data);
    EXPECT_EQ(result, data);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    sortColors(data);
    EXPECT_EQ(result, data);
}


static auto testCases = testing::Values(
        Param({2,0,2,1,1,0}, {0,0,1,1,2,2}),
        Param({2,0,1}, {0,1,2}),
        Param({2,1,2}, {1,2,2}),
        Param({2,0,2}, {0,2,2})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
