cmake_minimum_required(VERSION 3.25)
project(BinPackingProblem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinPackingProblem main.cpp util/Util.h hill-climbing/HillClimbing.cpp hill-climbing/HillClimbing.h)
