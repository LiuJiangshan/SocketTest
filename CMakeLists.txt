cmake_minimum_required(VERSION 3.10)
project(ddosByC)

set(CMAKE_CXX_STANDARD 11)

add_executable(ddos jni/ddos.cpp)