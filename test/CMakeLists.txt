cmake_minimum_required (VERSION 2.8.11)
project (avltree_test)

add_subdirectory(googletest ${CMAKE_BINARY_DIR}/googletest)

add_executable(set_test set_test.cpp)

add_library(avltree avltree.c)

target_link_libraries(set_test avltree gtest_main gtest)