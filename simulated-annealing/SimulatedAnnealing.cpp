#include <functional>
#include "SimulatedAnnealing.h"
#include "../util/Util.h"

void SimulatedAnnealing::simulatedAnnealing(std::vector<int> items, int sa_type, int binSize, int iter) {
    auto util = new Util(binSize);

    auto bestSolution = util->randomSolution(items);
    auto s = bestSolution;

    for (int i = 1; i < iter; i++) {
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
            std::function<double(int)> tp_function;
            switch(sa_type) {
                case 1:
                    tp_function = [](int k) { return 1000.0 / k; };
                    break;
                case 2:
                    tp_function = [](int k) { return 1.0 / std::log10(k); };
                    break;
                case 3:
                    tp_function = [](int k) { return std::pow(0.5, k); };
                    break;
                default:
                    std::cout << "WRONG TEMPERATURE METHOD TYPE ERROR" << std::endl;
                    exit(0);

            }
            if (u(generator) < std::exp(-std::abs((double)(util->getBins(newSolution).size() - util->getBins(s).size())/tp_function(i)))) {
                s = newSolution;
            }
        }
    }
    std::cout << "Simulated Annealing bins used: " << bestBinsCount << std::endl;
    std::cout << "Following bins content: " << std::endl;
    util->printBins(util->getBins(bestSolution));
}