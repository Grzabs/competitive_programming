#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Param = std::tuple<std::vector<int>, std::vector<int>>;

class Solution1 : public testing::TestWithParam<Param> {
public:
    ///   time: O(n)
    ///   memory: O(1)
    std::vector<int> replaceElements(std::vector<int>& arr) {
        int nSize = arr.size();
        int maxFound = arr[nSize-1];
        arr[nSize-1] = -1;
        for (int i=nSize-2;i>=0;i--) {
            int tmp = arr[i];
            arr[i] = maxFound;
            if (tmp>maxFound)
                maxFound = tmp;
        }
        return arr;
    }
};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto data1 = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, replaceElements(data1));
}


static auto testCases = testing::Values(
        Param({17,18,5,4,6,1}, {18,6,6,6,1,-1}),
        Param({400}, {-1})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);


