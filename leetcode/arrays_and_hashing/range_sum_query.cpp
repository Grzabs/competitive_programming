#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::pair<int,int>,int>;

class NumArray {
public:
    // O(n) + mem: O(n)
    NumArray(std::vector<int>& nums) : _nums{nums} {
        _prefixes.reserve(nums.size());
        _prefixes.push_back(nums[0]);
        for (int i=1;i<_nums.size();++i) {
            _prefixes.push_back(
                    _prefixes.back()+_nums[i]
            );
        }
    }
    // O(1)
    int sumRange(int left, int right) {
        return _prefixes[right]-_prefixes[left]+_nums[left];
    }

protected:
    std::vector<int> _nums;
    std::vector<int> _prefixes;

};

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)

    int test(std::vector<int>& nums, int l, int r) {
        return NumArray{nums}.sumRange(l, r);
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data = std::get<0>(parameter);
    auto [l, r] = std::get<1>(parameter);
    auto result = std::get<2>(parameter);
    EXPECT_EQ(result, test(data, l, r));
}

static auto testCases = testing::Values(
        Param({-2, 0, 3, -5, 2, -1}, {0, 2}, 1),
        Param({-2, 0, 3, -5, 2, -1}, {2, 5}, -1),
        Param({-2, 0, 3, -5, 2, -1}, {0, 5}, -3)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

