cmake_minimum_required(VERSION 3.21)
project(MyInterpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(MyInterpreter main.c SrcCodeListAbout.h CharListAbout.h)
