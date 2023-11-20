#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, int, bool>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(n)
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
        int nPlaces = 0;
        std::vector<int> paddedFlowerbed{0, 0};
        paddedFlowerbed.insert(paddedFlowerbed.begin()+1, flowerbed.begin(), flowerbed.end());
        for (int i=1;i<paddedFlowerbed.size()-1;++i) {
            if (paddedFlowerbed[i-1] == 0 &&
                paddedFlowerbed[i] == 0 &&
                paddedFlowerbed[i+1] == 0) {
                nPlaces++;
                paddedFlowerbed[i] = 1;
            }
        }
        return n<=nPlaces;
    }
};

class Solution2 : public testing::TestWithParam<Param> {
public:
    // cpu: O(n)
    // memory: O(1)
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
        int nEmpty = flowerbed[0] == 1 ? 0 : 1;
        for (int i=0;i<flowerbed.size();++i) {
            if (flowerbed[i]) {
                n -= (nEmpty-1)/2;
                nEmpty = 0;
            } else {
                nEmpty++;
            }
        }
        n -= (nEmpty)/2;
        return n <= 0;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto nFlowers = std::get<1>(parameter);
    auto expected = std::get<2>(parameter);
    EXPECT_EQ(expected, canPlaceFlowers(nums, nFlowers));
}
TEST_P(Solution2, TestCase1) {
    auto parameter = GetParam();
    auto nums = std::get<0>(parameter);
    auto nFlowers = std::get<1>(parameter);
    auto expected = std::get<2>(parameter);
    EXPECT_EQ(expected, canPlaceFlowers(nums, nFlowers));
}

static auto testCases = testing::Values(
        Param({0}, 1, true),
        Param({0, 0}, 1, true),
        Param({0, 0}, 2, false),
        Param({1, 0, 1}, 1, false),
        Param({1,0,0,1}, 1, false),
        Param({1,0,0,0,1}, 1, true),
        Param({1,0,0,0,1}, 2, false),
        Param({0,0,0,1}, 1, true),
        Param({0,0,0,1}, 2, false),
        Param({1,0,0,0,0,0,1}, 2, true),
        Param({1,0,0,0,0,0,1}, 3, false)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);

