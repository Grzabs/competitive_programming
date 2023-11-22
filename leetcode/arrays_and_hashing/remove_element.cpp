#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(1)
    int removeElement(std::vector<int>& nums, int val) {
        int i = 0, j = 0; // i -where to insert value not equal to val
        int nSwaps = 0;
        while (j < nums.size()) {
            if (nums[j] != val) {
                std::swap(nums[j], nums[i++]);
                nSwaps++;
            }
            j++;
        }
        return nSwaps;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto val = std::get<1>(parameter);
    auto expected = std::get<2>(parameter);
    EXPECT_EQ(expected, removeElement(nums, val));
}

static auto testCases = testing::Values(
        Param({3,2,2,3}, 3, 2),
        Param({0,1,2,2,3,0,4,2}, 2, 5),
        Param({}, 0, 0)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

