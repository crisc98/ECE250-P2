cmake_minimum_required(VERSION 3.9)
project(ECE250_P2)

set(CMAKE_CXX_STANDARD 11)

add_executable(ECE250_P2
        ece250.h
        Exception.h
        Resizable_deque.h
        Resizable_deque_driver.cpp
        Resizable_deque_tester.h
        Tester.h)
