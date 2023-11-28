#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n) + O(n) => O(n)
    ///   memory: O(n)
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> nums2(nums.size());
        for (int i=0;i<nums.size();++i) {
            nums2[nums[i]-1]++;
        }
        std::vector<int> result;
        for (int i=0;i<nums2.size();++i) {
            if (nums2[i] == 0)
                result.push_back(i+1);
        }
        return result;
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)  => O(n)
    ///   memory: O(1)
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> result;
        // [4,6,3,4,1,2]
        // [-4,-6,-2,-4,1,-2]
        for (int i=0;i<nums.size();++i) {
            int idx = std::abs(nums[i]) - 1;
            nums[idx] = -std::abs(nums[idx]);
        }
        for (int i=0;i<nums.size();++i)
            if (nums[i] > 0)
                result.push_back(i+1);
        return result;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(findDisappearedNumbers(data), result);
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto result = std::get<1>(parameter);
    EXPECT_EQ(findDisappearedNumbers(data), result);
}

static auto testCases = testing::Values(
        Param({4,3,2,7,8,2,3,1}, {5,6}),
        Param({1,1}, {2})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

