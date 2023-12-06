#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>


using Param = std::tuple<std::vector<int>, int, std::vector<int>>;


template<typename Comp>
class Heap {
public:
    Heap(Comp comparator) : _comparator{std::move(comparator)} {
        _elements.reserve(100000);
    }
    int pop() {
        int element = _elements[0];
        std::swap(_elements[0], _elements.back());
        _elements.pop_back();
        shiftDown(0);
        return element;
    }
    int size() const {
        return _elements.size();
    }
    void push(int k) {
        _elements.push_back(k);
        shiftUp(_elements.size()-1);
    }
protected:
    void shiftUp(int n) {
        int idx = n;
        int parent = 0;
        while ((parent = (idx-1)/2) >= 0 && parent!=idx && !_comparator(_elements[parent], _elements[idx])) {
            std::swap(_elements[parent], _elements[idx]);
            idx = parent;
        }
    }
    void shiftDown(int n) {
        while (true) {
            int shiftIdx = n;
            int lChild = 2*shiftIdx + 1;
            if (lChild < _elements.size() && _comparator(_elements[lChild], _elements[n]))
                shiftIdx = lChild;
            if (lChild+1 < _elements.size() && _comparator(_elements[lChild+1], _elements[shiftIdx]))
                shiftIdx = lChild+1;
            if (shiftIdx == n)
                break;
            std::swap(_elements[shiftIdx], _elements[n]);
            n = shiftIdx;
        }
    }
    Comp _comparator;
    std::vector<int> _elements;
};

class Solution1 : public ::testing::TestWithParam<Param> {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        if (nums.size() == k) {
            return nums;
        }
        // Get element -> frequency
        std::unordered_map<int, int> count;
        for (auto& num : nums) {
            count[num] += 1;
        }
        auto comparator = [&count](int n1, int n2) {
            return count[n1] < count[n2];
        };
        Heap<decltype(comparator)> heap(comparator);
        // Keep heap size equal to k, ops will take log k
        // instead of log n
        for (const auto& [number, freq] : count) {
            heap.push(number);
            if (heap.size() > k) heap.pop();
        }
        // takes O(k log k)
        std::vector<int> result(k);
        for (int i = k - 1; i>=0;--i) {
            result[i] = heap.pop();
        }

        return result;
    }
};

/*
 * Add: QuickSelect
 * Add: Lomuto's Partition Scheme
 */


TEST_P(Solution1, Test1) {
    auto &params = GetParam();
    auto nums = std::get<0>(params);
    auto k = std::get<1>(params);
    auto expected = std::get<2>(params);
    EXPECT_EQ(expected, topKFrequent(nums, k));
}


static auto testCases = testing::Values(
        Param({1,1,1,2,2,3}, 2, {1, 2}),
        Param({1}, 1, {1})
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);


