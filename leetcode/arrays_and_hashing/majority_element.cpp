#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(n)
    int majorityElement(std::vector<int>& nums) {
        std::unordered_map<int /* val*/, int /* count*/ > vc;
        for (auto& num : nums) {
            vc[num]++;
            if (vc[num] > nums.size()/2)
                return num;
        }
        return -1;
    }
};

class Solution2 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(1)
    // 2,1,2,1,2
    // 1,2,3,2,1,2,2
    int majorityElement(std::vector<int>& nums) {
        int count = 1;
        int last = nums[0];
        for (int i=1;i<nums.size();++i) {
            count += nums[i] == last ? 1 : -1;
           if (count==0) {
                last=nums[i];
                count=1;
            }
        }
        return last;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, majorityElement(nums));
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, majorityElement(nums));
}

static auto testCases = testing::Values(
        Param({3,2,3}, 3),
        Param({2,2,1,1,1,2,2}, 2)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

