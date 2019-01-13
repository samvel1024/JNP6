cmake_minimum_required(VERSION 3.10)
project(JNP5)

set(CMAKE_CXX_STANDARD 17)

#add_definitions(-DDEBUG)
#add_definitions(-DINPUTFILE="../std.in")
add_executable(official_example starwars2_example.cc)
add_executable(sandbox sandbox.cpp)
add_executable(test1 test.cpp)