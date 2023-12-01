#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>


class Solution1 : public ::testing::Test {
public:
    Solution1() : _elements(10000) {

    }
    void add(int key) {
        if (contains(key))
            return;
        auto& bucketRef = getBucket(key);
        bucketRef.push_back(key);
    }

    void remove(int key) {
        auto& bucketRef = getBucket(key);
        if (auto it = std::find(bucketRef.cbegin(), bucketRef.cend(), key); it != bucketRef.cend()) {
            bucketRef.erase(it);
        }

    }

    bool contains(int key) {
        const auto& bucketRef = getBucket(key);
        return std::find(bucketRef.cbegin(), bucketRef.cend(), key) != bucketRef.cend();
    }
protected:
    std::list<int>& getBucket(int key) {
        int bucket = key % 10000;
        return _elements[bucket];
    }
    std::vector<std::list<int>> _elements;
};


TEST_F(Solution1, Test1) {
    add(1);
    add(2);
    EXPECT_EQ(true, contains(1));
    EXPECT_EQ(true, contains(2));
    EXPECT_EQ(false, contains(3));
    add(2);
    EXPECT_EQ(true, contains(2));
    remove(2);
    EXPECT_EQ(false, contains(2));
}




