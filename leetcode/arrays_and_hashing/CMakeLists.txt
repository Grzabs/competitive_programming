

function(add_test test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} PUBLIC GTest::gtest_main)

    gtest_discover_tests(${test_name})
endfunction()


file(GLOB SOURCES *.cpp)
foreach (file ${SOURCES})
    get_filename_component(test_name ${file} NAME_WE)
    add_test(${test_name})
endforeach ()

