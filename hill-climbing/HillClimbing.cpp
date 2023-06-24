#include "HillClimbing.h"
#include "../util/Util.h"

void HillClimbing::randomHillClimbing(std::vector<int> items, int binSize) {
    // random hill climbing
    auto util = new Util(binSize);
    std::cout << "BIN SIZE " << std::endl;
    std::cout << util->getBinSize() << std::endl;

    auto bestSolution = util->randomSolution(items);

    while(true) {
        auto nextSolution = util->getRandomNeighbour(bestSolution);
        //bestBinsCount = util->getBins(bestSolution).size();
        if (util->getBins(nextSolution).size() <= util->getBins(bestSolution).size()) {
            bestSolution = std::move(nextSolution);
        } else {
            break;
        }
    }

    std::cout << "Random Hill Climbing bins used: " << util->getBins(bestSolution).size() << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}

void HillClimbing::deterministicHillClimbing(std::vector<int> items, int binSize) {
    // with deterministic best-neighbour choice hill climbing
    auto util = new Util(binSize);
    auto bestSolution = items;

    while(true) {
        auto nextSolution = util->getBestNeighbour(bestSolution);
        if (util->getBins(nextSolution).size() < util->getBins(bestSolution).size()) {
            bestSolution = std::move(nextSolution);
        } else {
            break;
        }
    }
    std::cout << "Deterministic Hill Climbing bins used: " << util->getBins(bestSolution).size() << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}
