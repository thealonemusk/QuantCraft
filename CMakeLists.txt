cmake_minimum_required(VERSION 3.10)
project(QuantCraftPP)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "core/*.cpp" "strategies/*.cpp" "data/*.cpp")

add_executable(quantcraft main.cpp ${SOURCES})
