#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>;


class Solution1 : public testing::TestWithParam<Param> {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> result;
        result.reserve(nums1.size());
        for (int i=0;i<nums1.size();++i) {
            for (int j=0;j<nums2.size();++j) {
                if (nums1[i] == nums2[j]) {
                    int biggerNumber = nums2[j];
                    for (int k=j+1;k<nums2.size();++k)
                    {
                        if (nums2[k] > biggerNumber) {
                            biggerNumber = nums2[k];
                            break;
                        }
                    }
                    result.push_back(biggerNumber == nums2[j] ? -1 : biggerNumber);
                }
            }
        }
        return result;
    }
};

class Solution2 : public testing::TestWithParam<Param> {
public:
    std::vector<int> nextGreaterElement( std::vector<int>& nums1,  std::vector<int>& nums2) {
        std::vector<int> result;
        result.reserve(nums1.size());
        std::unordered_map<int,int> n2idx;
        for (int i=0;i<nums2.size();++i) {
            n2idx[nums2[i]]=i;
        }
        for (int i=0;i<nums1.size();++i) {
            int idx = n2idx.find(nums1[i])->second;
            bool found = false;
            for (int j=idx+1;j<nums2.size();++j) {
                if (nums2[j]>nums1[i]) {
                    result.push_back(nums2[j]);
                    found = true;
                    break;
                }
            }
            if (!found)
                result.push_back(-1);
        }
        return result;
    }
};

class Solution3 : public testing::TestWithParam<Param> {
public:
    // time: O(n+m) memory: O(n)
    std::vector<int> nextGreaterElement( std::vector<int>& nums1,  std::vector<int>& nums2) {
        std::deque<int> unresolved;
        std::unordered_map<int,int> indexes;
        std::vector<int> result(nums1.size(), -1);
        for (int i=0;i<nums1.size();++i) {
            indexes[nums1[i]] = i;
        }
        // {4,1,2}, {1,3,4,2} {-1,3,-1}
        // {2,4}, {1,2,3,4}, {3,-1}
        for (int current : nums2) {
            // e.g 5,1,2 but found 4
            while (!unresolved.empty() && current > unresolved.back())
            {
                result[indexes[unresolved.back()]] = current;
                unresolved.pop_back();
            }
            if (auto it = indexes.find(current); it != indexes.end()) {
                unresolved.push_back(current);
            }
        }
        return result;
    }
};

// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, nextGreaterElement(data1, data2));
}

TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, nextGreaterElement(data1, data2));
}

TEST_P(Solution3, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto data2 = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, nextGreaterElement(data1, data2));
}


static auto testCases = testing::Values(
        Param({4,1,2}, {1,3,4,2}, {-1,3,-1}),
        Param({2,4}, {1,2,3,4}, {3,-1})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution3, testCases);