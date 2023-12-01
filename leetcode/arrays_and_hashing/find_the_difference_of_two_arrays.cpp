#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>, std::vector<std::vector<int>>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n+m)
    ///   memory: O(n+m)
    std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> nums1set;
        std::unordered_set<int> nums2set;
        for (auto i : nums1) {
            nums1set.insert(i);
        }
        for (auto i : nums2) {
            nums2set.insert(i);
        }
        std::vector<std::vector<int>> result(2);
        for (auto i : nums1set) {
            if (nums2set.find(i) == nums2set.end()) {
                result[0].push_back(i);
            }
        }
        for (auto i : nums2set) {
            if (nums1set.find(i) == nums1set.end()) {
                result[1].push_back(i);
            }
        }
        return result;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums1 = std::get<0>(parameter);
    auto nums2 = std::get<1>(parameter);
    auto expected = std::get<2>(parameter);
    EXPECT_EQ(expected, findDifference(nums1, nums2));
}

static auto testCases = testing::Values(
        Param({1,2,3},{2,4,6}, {{3,1}, {6,4}}),
        Param({1,2,3,3},{1,1,2,2}, {{3}, {}})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
