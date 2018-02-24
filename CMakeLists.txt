cmake_minimum_required(VERSION 3.9)

project(DS_Curriculum_Disign)

add_subdirectory(src)
aux_source_directory(. dir_main)
add_executable(py_manager ${dir_main})
target_link_libraries(py_manager lib)