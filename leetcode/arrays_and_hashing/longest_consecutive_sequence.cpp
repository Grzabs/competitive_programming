#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <gtest/gtest.h>



using Param = std::tuple<std::vector<int>, int>;

class Solution1 : public ::testing::TestWithParam<Param> {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        int longestSequence = 0;
        while (!nums_set.empty()) {
            auto number = *nums_set.begin();
            int sequence_length = 1;
            auto prevNumber = number;
            // loop backwards
            nums_set.erase(prevNumber);
            while (nums_set.find(prevNumber-1) != nums_set.end()) {
                sequence_length++;
                prevNumber = prevNumber-1;
                nums_set.erase(prevNumber);
            }
            // loop forwards
            auto nextNumber = number;
            nums_set.erase(nextNumber);
            while (nums_set.find(nextNumber+1) != nums_set.end()) {
                sequence_length++;
                nextNumber = nextNumber+1;
                nums_set.erase(nextNumber);
            }
            if (sequence_length > longestSequence)
                longestSequence = sequence_length;
        }
        return longestSequence;
    }


};

class Solution2: public ::testing::TestWithParam<Param> {
public:
    /*
     *      x1 2 3 4         x100     x200
     * -------------------------------------
     */
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> numsSet(nums.begin(), nums.end());
        int maxSequenceLength = 0;
        for (int i=0;i<nums.size();++i) {
            // Start of a sequence
            if (numsSet.find(nums[i]-1) == numsSet.end()) {
                int sequenceLength = 1;
                int sequenceVal = nums[i];
                while (numsSet.find(sequenceVal+1) != numsSet.end()) {
                    sequenceVal += 1;
                    sequenceLength++;
                }
                if (sequenceLength > maxSequenceLength)
                    maxSequenceLength = sequenceLength;
            }
        }
        return maxSequenceLength;
    }

};


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto prices = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, longestConsecutive(prices));
}

TEST_P(Solution2, Test1) {
    auto &params = GetParam();
    auto prices = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, longestConsecutive(prices));
}



static auto testCases = testing::Values(
        Param({100,4,200,1,3,2}, 4),
        Param({0,3,7,2,5,8,4,6,0,1}, 9)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);


