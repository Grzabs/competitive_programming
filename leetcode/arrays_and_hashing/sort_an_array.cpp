#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>


using Param = std::tuple<std::vector<int>, std::vector<int>>;

/*
 *          0
 *      1     2
 *   3    4  5  6
 *
 *
 *   0123456
 *
 *
 */



class MinHeap {
public:
    MinHeap(int limit) : _array(limit) {}
    void push(int num) {
        if (_n >= _array.size())
            return;
        _array[_n] = num;
        pushUp(_n++);
    }
    /*
     *          0
     *      1       0
     *   5    2   1
     */
    int pop() {
        int element = _array[0];
        _array[0] = _array[--_n];
        pushDown(0);
        return element;
    }
    bool empty() {
        return _n == 0;
    }
protected:
    void pushUp(int idx) {
        int parentIdx = (idx-1)/2;
        while ( (parentIdx=(idx-1)/2) >= 0 && _array[parentIdx] > _array[idx]) {
            std::swap(_array[parentIdx], _array[idx]);
            idx=parentIdx;
        }
    }
    void pushDown(int idx) {
        int switchIdx = idx;
        while (idx<_n) {
            int lParIdx = 2*idx+1;

            if (lParIdx < _n && _array[lParIdx] < _array[switchIdx])
                switchIdx = lParIdx;
            if (lParIdx+1 < _n && _array[lParIdx+1] < _array[switchIdx])
                switchIdx = lParIdx+1;
            if (switchIdx == idx) {
                break;
            }
            std::swap(_array[switchIdx], _array[idx]);
            idx = switchIdx;
        }
    }
    int _n{0};
    std::vector<int> _array;
};


/*
 *                  0
 *          1                2
 *      3       4        5       6
 *    7   8   9  10   11  12  13  14
 *
 *  starting from n/2 we are restoring heap order in subheaps like
 *  6 -> 13, 14; 5 -> 11,12 and so on, doing to the root element
 *
 * next, when the heap is built, we swap the first and last element (in place)
 * reducing the heap size. The last element is the greatest one.
 */

class HeapSort {
public:
    static void shiftDown(std::vector<int>& nums, int idx, int n) {
        int shiftIdx = 0;
        do {
            shiftIdx = idx;
            int lChildIdx = 2 * idx + 1;
            if (lChildIdx < n && nums[lChildIdx] > nums[shiftIdx])
                shiftIdx = lChildIdx;
            if (lChildIdx + 1 < n && nums[lChildIdx + 1] > nums[shiftIdx])
                shiftIdx = lChildIdx + 1;
            if (idx == shiftIdx)
                break;
            std::swap(nums[shiftIdx], nums[idx]);
            idx = shiftIdx;
        } while (true);
    }
    static void sort(std::vector<int>& nums) {
        // build heap
        for (int i=nums.size()/2;i>=0;--i) {
            shiftDown(nums, i, nums.size());
        }
        int n = nums.size()-1;
        while (n >= 1) {
            std::swap(nums[0], nums[n]);
            shiftDown(nums, 0, n--);
        }
    }
};


class Solution1 : public ::testing::TestWithParam<Param> {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
        HeapSort::sort(nums);
        return nums;
    }
};


//       5,1,32,8,4,-1
//   5,1,32      8,4,-1
//   5,1   32    8,4   -1
//  5  1   32   8  4   -1
//

class MergeSort {
public:
    static void sort(std::vector<int>& nums) {
        auto results = sortInternal(nums, 0, nums.size()-1);
        nums = std::move(results);
    }
protected:
    static std::vector<int> sortInternal(std::vector<int>& nums, int i, int k) {
        if (i>=k)
            return {nums[k]};
        int mid = (i+k)/2;
        auto left = sortInternal(nums, i, mid);
        auto right = sortInternal(nums, mid+1, k);
        std::vector<int> result;
        result.reserve(left.size() + right.size());
        int leftPtr = 0;
        int rightPtr = 0;
        while (leftPtr < left.size() && rightPtr < right.size()) {
            if (left[leftPtr] < right[rightPtr]) {
                result.push_back(left[leftPtr++]);
            } else {
                result.push_back(right[rightPtr++]);
            }
        }
        while (leftPtr < left.size())
            result.push_back(left[leftPtr++]);
        while (rightPtr < right.size())
            result.push_back(right[rightPtr++]);
        return result;
    }
};


class Solution2 : public ::testing::TestWithParam<Param> {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
        MergeSort::sort(nums);
        return nums;
    }
};


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto nums = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, sortArray(nums));
}

TEST_P(Solution2, Test1) {
    auto &params = GetParam();
    auto nums = std::get<0>(params);
    auto expected = std::get<1>(params);
    EXPECT_EQ(expected, sortArray(nums));
}

static auto testCases = testing::Values(
        Param({5,2,3,1}, {1,2,3,5}),
        Param({5,1,1,2,0,0}, {0,0,1,1,2,5}),
        Param({-4,0,7,4,9,-5,-1,0,-7,-1}, {-7,-5,-4,-1,-1,0,0,4,7,9})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);
INSTANTIATE_TEST_SUITE_P(TestSolution, Solution2, testCases);


