#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int, std::vector<int>>;


class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n^2) => O(n^2)
    ///   memory: O(1)

    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        for (int i=0;i<nums.size();++i) {
            for (int j=i+1;j<nums.size();++j) {
                if (target - nums[i] == nums[j]) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
class Solution2 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n) + O(n) => O(n)
    ///   memory: O(1)
    int binSearch(const std::vector<int>& vec, int i, int j, int what) {
        if (i>j)
            return -1;
        int midPoint = (i+j)/2;
        if (vec[midPoint] == what)
            return midPoint;
        if (what < vec[midPoint]) {
            return binSearch(vec, i, midPoint-1, what);
        }
        return binSearch(vec, midPoint+1, j, what);
    }
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> sortedNums(nums);
        std::sort(sortedNums.begin(), sortedNums.end());
        int i,j;
        for (i=0;i<sortedNums.size();++i) {
            j = binSearch(sortedNums, i+1, sortedNums.size()-1, target-sortedNums[i]);
            if (j != -1) {
                break;
            }
        }
        if (j == -1) {
            return {};
        }
        // idx are i and j
        std::vector<int> result;
        int k=0;
        while (k < nums.size() && result.size() < 2) {
            if (nums[k] == sortedNums[i] || nums[k] == sortedNums[j]) {
                result.push_back(k);
            }
            k++;
        }
        return result;
    }
};
class Solution3 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n) + O(n) => O(n)
    ///   memory: O(1)

    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        // in case of repeating numbers, newer will have greater index so this is OK
        // during search phase we will start from lower index, and if the searched number
        // is the same as start number nums[i] it will reference the latter index
        for (int i=0;i<nums.size();++i) {
            map[nums[i]] = i;
        }
        for (int i=0;i<nums.size();++i) {
            if (auto it = map.find(target-nums[i]); it != map.end() && it->second != i) {
                return {i, it->second};
            }
        }
        return {};
    }
};
class Solution4 : public testing::TestWithParam<Param> {
public:
    ///   time: O(nlog n) (linear search and log n find in every interation)
    ///   memory: O(1)
    // Search numbers before our current index i
    // 3,3
    //   3 : not found
    //   3 : 3 found at idx i-1
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        for (int i=0;i<nums.size();++i) {
            if (auto it = map.find(target-nums[i]); it != map.end())
                return {it->second, i};
            map[nums[i]] = i;
        }
        return {};
    }
};
// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto target = std::get<1>(parameter);
    auto idxs = std::get<2>(parameter);
    EXPECT_EQ(idxs, twoSum(nums, target));
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto target = std::get<1>(parameter);
    auto idxs = std::get<2>(parameter);
    EXPECT_EQ(twoSum(nums, target), idxs);
}
TEST_P(Solution3, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto target = std::get<1>(parameter);
    auto idxs = std::get<2>(parameter);
    EXPECT_EQ(twoSum(nums, target), idxs);
}
TEST_P(Solution4, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto target = std::get<1>(parameter);
    auto idxs = std::get<2>(parameter);
    EXPECT_EQ(twoSum(nums, target), idxs);
}


static auto testCases = testing::Values(
        Param({2,7,11,15}, 9, {0, 1}),
        Param({3, 2, 4}, 6, {1, 2}),
        Param({3, 3}, 6, {0, 1})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution3, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution4, testCases);