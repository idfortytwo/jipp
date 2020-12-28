cmake_minimum_required(VERSION 3.0)

project(lab6)

include_directories(src test include)

add_executable(test test/test.cpp src/Employee.cpp src/HRMS.cpp)