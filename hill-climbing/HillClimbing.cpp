#include "HillClimbing.h"
#include "../util/Util.h"

void HillClimbing::randomHillClimbing(std::vector<int> items) {
    // random hill climbing
    auto util = new Util();

    auto bestSolution = items;
    for (int i = 0; i < 5000; i++) {
        auto testSolution = util->getRandomNeighbour(bestSolution);
        bestBinsCount = util->getBins(bestSolution).size();
        if (util->getBins(testSolution).size() <= util->getBins(bestSolution).size()) {
            bestSolution = std::move(testSolution);
        }
    }
    std::cout << "Random Hill Climbing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}

void HillClimbing::deterministicHillClimbing(std::vector<int> items) {
    // with deterministic best-neighbour choice hill climbing
    auto util = new Util();
    auto bestSolution = items;

    for (int i = 0; i < 5000; i++) {
        auto testSolution = util->getBestNeighbour(bestSolution);
        bestBinsCount = util->getBins(bestSolution).size();
        if(util->getBins(testSolution).size() < util->getBins(bestSolution).size()) {
            bestSolution = std::move(testSolution);
        }
    }
    std::cout << "Deterministic Hill Climbing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}
