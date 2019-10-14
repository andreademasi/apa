cmake_minimum_required(VERSION 3.15)
project(apa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Lab_0)
include_directories(Lab_01)
include_directories(Lab_02)

add_executable(apa

        Lab_02/lab_2_es_3.c)
