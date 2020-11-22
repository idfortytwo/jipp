cmake_minimum_required( VERSION 3.0 )

project( lab4 )

include_directories( ./src ./test)

add_executable( test ./test/test.cpp ./src/matrix.cpp )