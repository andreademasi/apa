cmake_minimum_required(VERSION 3.15)
project(apa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Lab_0)
include_directories(Lab_01)

add_executable(apa

        Lab_0/lab_0_es_2.c)
