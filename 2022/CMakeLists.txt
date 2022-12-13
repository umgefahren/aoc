cmake_minimum_required(VERSION 3.10)

project(2022)

include_directories(utils)


add_executable(ex-1 ex-1/solution.c)
add_executable(ex-2 ex-2/solution.c)

target_link_libraries(ex-1 )
target_link_libraries(ex-2 )
