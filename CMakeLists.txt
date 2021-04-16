cmake_minimum_required(VERSION 3.10)

project(std_promise_future)
set(CXX_STANDARD 14)
add_executable(std_promise_future promise_future.cpp)

find_package(Threads REQUIRED)
target_link_libraries(std_promise_future Threads::Threads)