#ifndef BINPACKINGPROBLEM_GENETICALGORITHM_H
#define BINPACKINGPROBLEM_GENETICALGORITHM_H


#include <vector>
#include <random>

class GeneticAlgorithm {
public:
    static GeneticAlgorithm* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new GeneticAlgorithm();
    }

    void geneticAlgorithm(std::vector<int> items, int parameters[5], int binSize);

private:
    int iterationCount = 0;
    static GeneticAlgorithm* sInstance;

    bool terminalCondition(int terminalConditionType, std::vector<std::vector<int>> &population, int iterationCount, int sharedPopulationFitness, int binSize);
    bool endOnIterationCount(int iterationCount);
    bool endOnSharedPopulationFitness(std::vector<std::vector<int>> &population, int sharedPopulationFitness, int binSize);

    std::vector<std::vector<int>> getInitialPopulation(std::vector<int> items, int populationSize, int binSize);
    double calculateFitness(std::vector<int>, int binSize);
    std::vector<std::vector<int>> selection(std::vector<std::vector<int>> population, int binSize);
    std::vector<std::vector<int>> crossover(int crossoverMethod, std::vector<std::vector<int>> );
    std::vector<int> mutation(std::vector<int> child, int mutationType, int binSize);

    std::vector<int> randomSolution(std::vector<int>, std::mt19937 &rgen);

    //std::vector<std::vector<int>> getPopulation(std::vector<int> items);

};

#endif //BINPACKINGPROBLEM_GENETICALGORITHM_H
