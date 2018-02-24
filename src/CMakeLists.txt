add_subdirectory(prompt)
aux_source_directory(. dir_srcs)
add_library(lib ${dir_srcs})
target_link_libraries(lib prompt)