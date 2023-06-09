#include "HillClimbing.h"
#include "../util/Util.h"

void HillClimbing::runHillClimbing(std::vector<int> items) {
    // random hill climbing
    auto util = new Util();

    auto bestSolution = items;
    auto bestSolution2 = items;
    int bestBinsCount;
    while(true) {
        auto testSolution = util->getRandomNeighbour(bestSolution);
        bestBinsCount = util->getBins(bestSolution).size();
        if (util->getBins(testSolution).size() <= util->getBins(bestSolution).size()) {
            bestSolution = std::move(testSolution);
        }
        else {
            break;
        }
    }
    std::cout << "Random Hill Climbing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));

    // with deterministic best-neighbour choice hill climbing
    bestSolution = items;

    while(true) {
        auto testSolution = getBestNeighbour(bestSolution);
        bestBinsCount = util->getBins(bestSolution).size();
        if(util->getBins(testSolution).size() < util->getBins(bestSolution).size()) {
            bestSolution = std::move(testSolution);
        }
        else {
            break;
        }
    }

    std::cout << "Deterministic Hill Climbing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}

std::vector<int> HillClimbing::getBestNeighbour(const std::vector<int> &items) {
    auto util = new Util();

    auto neighbours = util->getNeighbours(items);
    auto bestNeighbour = std::vector<int>{};
    for (int i = 0; i < neighbours.size() - 1; i++) {
        if (util->getBins(neighbours.at(i)).size() < util->getBins(neighbours.at(i + 1)).size()) {
            bestNeighbour = neighbours.at(i);
        }
        else {
            bestNeighbour = neighbours.at(i+1);
        }
    }
    return bestNeighbour;
}
