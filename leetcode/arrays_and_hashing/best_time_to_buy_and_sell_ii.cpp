#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <gtest/gtest.h>
#include <queue>
#include <stack>


using Param = std::tuple<std::vector<int>, int>;

class Solution1 : public ::testing::TestWithParam<Param> {
public:
    /*
     *     7   1   5   3   6    4
     *  7  0   -6  -2  -4  -1  -3
     *  1      0   4   2   5    3
     *  5          0  -2   1   -1
     *  3              0   3   -1
     *  6                  0   -2
     *  4                       0
     *
     */
    int _maxProfit(std::vector<int>& prices, int buyDay) {
        int maxProfit = 0;
        for (int i=buyDay;i<prices.size();++i) {
            int profit = prices[i] - prices[buyDay];
            if (profit >= 0) {
                profit += _maxProfit(prices, i+1);
                if (profit > maxProfit)
                    maxProfit = profit;
            }
        }
        return maxProfit;
    }

    int maxProfit(std::vector<int>& prices) {
        return _maxProfit(prices, 0);
    }

};

class Solution2: public ::testing::TestWithParam<Param> {
public:
    // 7   1   5   3   6    4
    int maxProfit(std::vector<int>& prices) {
        int profit = 0;
        for (int i=0;i<prices.size()-1;++i) {
            int delta = prices[i+1]-prices[i];
            if (delta > 0) {
                profit += delta;
            }
        }
        return profit;
    }

};


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto prices = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, maxProfit(prices));
}
TEST_P(Solution2, Test1) {
    auto &params = GetParam();
    auto prices = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, maxProfit(prices));
}



static auto testCases = testing::Values(
        Param({7,1,5,3,6,4}, 7),
        Param({1,2,3,4,5} ,4),
        Param({7,6,4,3,1} ,0)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);


