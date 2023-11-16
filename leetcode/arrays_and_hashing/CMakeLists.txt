



add_executable(contains_duplicate contains_duplicate.cpp)
target_link_libraries(contains_duplicate PUBLIC GTest::gtest_main)

add_executable(valid_anagram valid_anagram.cpp)
target_link_libraries(valid_anagram PUBLIC GTest::gtest_main)

gtest_discover_tests(contains_duplicate)
gtest_discover_tests(valid_anagram)