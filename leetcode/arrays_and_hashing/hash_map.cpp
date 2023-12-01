#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>


class Solution1 : public ::testing::Test {
public:
    Solution1() : _container(10001) {

    }

    void put(int key, int value) {
        auto& bucketRef = getBucket(key);
        auto it = getElementIt(bucketRef, key);
        if (it != bucketRef.end()) {
            it->second = value;
        } else {
            bucketRef.emplace_back(key, value);
        }
    }

    int get(int key) {
        auto& bucketRef = getBucket(key);
        auto it = getElementIt(bucketRef, key);
        if (it != bucketRef.end()) {
            return it->second;
        }
        return -1;
    }

    void remove(int key) {
        auto& bucketRef = getBucket(key);
        auto it = getElementIt(bucketRef, key);
        if (it != bucketRef.end()) {
            bucketRef.erase(it);
        }
    }
protected:
    using element_t = std::pair<int,int>;
    using bucket_t = std::list<element_t>;
    std::vector<bucket_t> _container;

    bucket_t::iterator getElementIt(bucket_t& bucketRef, int key) {
        return std::find_if(bucketRef.begin(), bucketRef.end(), [&](auto& element) {
            return element.first == key;
        });
    }
    bucket_t& getBucket(int key) {
        int idx = key % 10000;
        return _container[idx];
    }
};


TEST_F(Solution1, Test1) {
    put(1, 1);
    put(2, 2);
    EXPECT_EQ(1, get(1));
    EXPECT_EQ(-1, get(3));
    put(2, 1);
    EXPECT_EQ(1, get(2));
    remove(2);
    EXPECT_EQ(-1, get(2));
}




