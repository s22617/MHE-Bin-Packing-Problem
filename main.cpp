#include <iostream>
#include "hill-climbing/HillClimbing.h"
#include "tabu/Tabu.h"
#include "simulated-annealing/SimulatedAnnealing.h"
#include "genetic-algorithm/GeneticAlgorithm.h"
#include "util/Parameters.h"

auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4, 4, 5, 7, 2, 6, 7, 8, 9, 3, 4, 6, 5, 7, 8, 1, 1, 1, 2, 2, 2, 2};
//auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4, 4};
std::map<int, std::function<double(int)>> TP = {
        {1, [](int k) { return 1000.0 / k; }},
        {2, [](int k) { return 1.0 / std::log10(k); }},
        {3, [](int k) { return std::pow(0.5, k); }},
};

HillClimbing* HillClimbing::sInstance = nullptr;
Tabu* Tabu::sInstance = nullptr;
SimulatedAnnealing* SimulatedAnnealing::sInstance = nullptr;
GeneticAlgorithm* GeneticAlgorithm::sInstance = nullptr;

int main(int argc, char *argv[]) {

    int GA_PARAMETERS[] = {
            parameters::POPULATION_SIZE,
            parameters::TERMINAL_CONDITION,
            parameters::CROSSOVER_METHOD,
            parameters::MUTATION_METHOD};

    //HillClimbing::getInstance()->randomHillClimbing(items);
    //HillClimbing::getInstance()->deterministicHillClimbing(items);

    //Tabu::getInstance()->tabuSearch(items, INT_MAX);
    //SimulatedAnnealing::getInstance()->simulatedAnnealing(items, TP[1]);

    GeneticAlgorithm::getInstance()->geneticAlgorithm(items, GA_PARAMETERS);
    return 0;
}