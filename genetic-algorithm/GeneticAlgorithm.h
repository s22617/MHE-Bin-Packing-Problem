#ifndef BINPACKINGPROBLEM_GENETICALGORITHM_H
#define BINPACKINGPROBLEM_GENETICALGORITHM_H


#include <vector>
#include <random>

class GeneticAlgorithm {
public:
    static GeneticAlgorithm* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new GeneticAlgorithm();
    }

    void geneticAlgorithm(std::vector<int> items, int parameters[4]);

private:
    // int bestBinsCount;
    int iterationCount = 0;
    static GeneticAlgorithm* sInstance;

    bool terminalCondition(int terminalConditionType, std::vector<std::vector<int>> &population);
    bool endOnIterationCount();
    bool endOnSharedPopulationFitness(std::vector<std::vector<int>> &population);

    std::vector<std::vector<int>> getInitialPopulation(std::vector<int> items, int populationSize);
    double calculateFitness(std::vector<int>);
    std::vector<std::vector<int>> selection(std::vector<std::vector<int>> population);
    std::vector<std::vector<int>> crossover(std::vector<int> parentA, std::vector<int> parentB);
    std::vector<int> mutation(std::vector<int> child, int mutationType);

    std::vector<int> randomSolution(std::vector<int>, std::mt19937 &rgen);

    //std::vector<std::vector<int>> getPopulation(std::vector<int> items);

};

#endif //BINPACKINGPROBLEM_GENETICALGORITHM_H
