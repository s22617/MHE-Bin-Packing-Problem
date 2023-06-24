//
// Created by Dan on 22.06.2023.
//


#include <functional>
#include "SimulatedAnnealing.h"
#include "../util/Util.h"

void SimulatedAnnealing::simulatedAnnealing(std::vector<int> items, std::function<double(int)> T) {
    auto util = new Util();

    auto bestSolution = items;
    auto s = items;

    for (int i = 1; i < 5000; i++) {
        auto newSolution = util->getRandomNeighbour(s);
        bestBinsCount = util->getBins(bestSolution).size();
        if (util->getBins(newSolution).size() <= util->getBins(s).size()) {
            s = newSolution;
            if (util->getBins(newSolution).size() <= util->getBins(bestSolution).size()) {
                bestSolution = s;
            }
        }
        else {
            std::uniform_real_distribution<double> u(0.0, 1.0);

            if (u(generator) < std::exp(-std::abs((double)(util->getBins(newSolution).size() - util->getBins(s).size())/T(i)))) {
                s = newSolution;
            }
        }
    }
    std::cout << "Simulated Annealing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}