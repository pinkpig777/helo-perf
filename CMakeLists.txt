cmake_minimum_required(VERSION 3.28)
project(hello_perf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_executable(fib_bench bench/fib_bench.cpp)
target_link_libraries(fib_bench benchmark::benchmark)

add_executable(fib_test tests/fib_test.cpp)
target_link_libraries(fib_test GTest::gtest_main)

enable_testing()
add_test(NAME FibTest COMMAND fib_test)
