cmake_minimum_required( VERSION 3.0 )

project( lab5 )

include_directories( src test include libs)

add_executable( test test/test.cpp src/matrix.cpp libs/sqlite3/sqlite3.c)