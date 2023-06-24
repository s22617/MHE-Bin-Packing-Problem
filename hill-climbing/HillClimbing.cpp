#include "HillClimbing.h"
#include "../util/Util.h"

void HillClimbing::randomHillClimbing(std::vector<int> items) {
    // random hill climbing
    auto util = new Util();

    auto bestSolution = items;

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

void HillClimbing::deterministicHillClimbing(std::vector<int> items) {
    // with deterministic best-neighbour choice hill climbing
    auto util = new Util();
    auto bestSolution = items;

    while(true) {
        auto nextSolution = util->getBestNeighbour(bestSolution);
        if(util->getBins(nextSolution).size() < util->getBins(bestSolution).size()) {
            bestSolution = std::move(nextSolution);
        } else {
            break;
        }
    }
    std::cout << "Deterministic Hill Climbing bins used: " << util->getBins(bestSolution).size() << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}
