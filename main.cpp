#include <iostream>
#include <fstream>
#include <cstring>
#include "hill-climbing/HillClimbing.h"
#include "tabu/Tabu.h"
#include "simulated-annealing/SimulatedAnnealing.h"
#include "genetic-algorithm/GeneticAlgorithm.h"
#include "util/Parameters.h"

auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4, 4, 5, 7, 2, 6, 7, 8, 9, 3, 4, 6, 5, 7, 8, 1, 1, 1, 2, 2, 2, 2};
//auto items = std::vector<int> {2, 5, 9, 1, 2, 5, 9, 1,2, 5, 9, 1,2, 5, 9, 1,2, 5, 9, 1,2, 5, 9, 1};
//auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4, 4};

HillClimbing* HillClimbing::sInstance = nullptr;
Tabu* Tabu::sInstance = nullptr;
SimulatedAnnealing* SimulatedAnnealing::sInstance = nullptr;
GeneticAlgorithm* GeneticAlgorithm::sInstance = nullptr;

void printHelp() {
    std::cout << "Genetic Algorithm\n"
                 "ga_s - Population Size\n"
                 "ga_t - Terminal Condition\n"
                 "\t1 - on shared population fitness\n"
                 "\t2 - on iteration count\n"
                 "ga_c - Crossover Method\n"
                 "\t1 - PMX\n"
                 "\t2 - item stripping\n"
                 "ga_m - Mutation Method\n"
                 "\t1 - shuffle random bins\n"
                 "\t2 - swap random\n"
                 "ga_i - iteration count\n"
                 "ga_f - shared population fitness\n\n"
                 "Tabu Search\n"
                 "tabu_s - Tabu Size\n\n"
                 "Simulated Annealing\n"
                 "sim_t - Temperature Type\n\n"
                 "bin - bin size"
                 "iter - iteration count"
                  << std::endl;
}

void handleArgc(int argc, char *argv[]) {

    std::vector<std::string> possibleArgList = {
            "ga_s",
            "ga_t",
            "ga_c",
            "ga_m",
            "ga_i",
            "ga_f",
            "tabu_s",
            "sim_t",
            "help",
            "bin",
            "iter"
    };

    for (int i = 1; i < argc; i++) {

        if (std::find(possibleArgList.begin(), possibleArgList.end(), argv[i]) != possibleArgList.end()) {
            if (strcmp(argv[i], "ga_s") == 0) {
                parameters::POPULATION_SIZE = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "ga_t") == 0) {
                parameters::TERMINAL_CONDITION = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "ga_c") == 0) {
                parameters::CROSSOVER_METHOD = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "ga_m") == 0) {
                parameters::MUTATION_METHOD = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "ga_i") == 0)  {
                parameters::ITERATION_COUNT_LIMIT = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "ga_f") == 0) {
                parameters::SHARED_POPULATION_FITNESS = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "tabu_s") == 0) {
                parameters::TABU_SIZE = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "sim_t") == 0) {
                parameters::SA_TYPE = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "help") == 0) {
                printHelp();
            } else if (strcmp(argv[i], "bin") == 0) {
                parameters::BIN_SIZE = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "iter") == 0) {
                parameters::ITER = std::stoi(argv[i + 1]);
            }
            else {
                std::cout << "WRONG ARG PASSED" << std::endl;
                exit(0);
            }
        }
    }
}

int main(int argc, char *argv[]) {

//    auto items = std::vector<int>{};
//    auto data = std::fstream{"data.txt", std::ios::in};
//
//    int weight;
//    while (data >> weight) {
//        items.push_back(weight);
//    }

    handleArgc(argc, argv);

    int BIN_SIZE = parameters::BIN_SIZE;
    int ITER = parameters::ITER;

    int GA_PARAMETERS[] = {
            parameters::POPULATION_SIZE,
            parameters::TERMINAL_CONDITION,
            parameters::CROSSOVER_METHOD,
            parameters::MUTATION_METHOD,
            parameters::ITERATION_COUNT_LIMIT,
            parameters::SHARED_POPULATION_FITNESS};

    int TABU_PARAMETERS[] = {parameters::TABU_SIZE};
    int SA_PARAMETERS = {parameters::SA_TYPE};

    //HillClimbing::getInstance()->randomHillClimbing(items, BIN_SIZE);
    //HillClimbing::getInstance()->deterministicHillClimbing(items, BIN_SIZE);
    //Tabu::getInstance()->tabuSearch(items, TABU_PARAMETERS[0], BIN_SIZE, ITER);
    //SimulatedAnnealing::getInstance()->simulatedAnnealing(items, SA_PARAMETERS, BIN_SIZE, ITER);

    GeneticAlgorithm::getInstance()->geneticAlgorithm(items, GA_PARAMETERS, BIN_SIZE);

    return 0;
}