cmake_minimum_required(VERSION 3.24)
project(BinPackingProblem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinPackingProblem main.cpp util/Util.h hill-climbing/HillClimbing.cpp hill-climbing/HillClimbing.h tabu/Tabu.cpp tabu/Tabu.h Solution.cpp Solution.h simulated-annealing/SimulatedAnnealing.cpp simulated-annealing/SimulatedAnnealing.h genetic-algorithm/GeneticAlgorithm.cpp genetic-algorithm/GeneticAlgorithm.h util/Parameters.h)
