#include <algorithm>
#include <list>
#include <set>
#include "Tabu.h"
#include "../util/Util.h"


//add tabu size
void Tabu::tabuSearch(std::vector<int> items, int tabuSize) {
    auto util = new Util();

    std::list<std::vector<int>> tabuList;
    tabuList.push_back(items);

    std::set<std::vector<int>> tabuSet;
    tabuSet.insert(items);

    auto bestSolution = items;
        for (int i = 0; i < 5000; i++) {
            if (tabuSet.size() < tabuSize) {
                auto neighbours = util->getNeighbours(tabuList.back());

                bestBinsCount = util->getBins(bestSolution).size();
                neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(),
                                                [&](std::vector<int> bin) {
                                                    return tabuSet.find(bin) != tabuSet.end();
                                                }),
                                 neighbours.end());

                std::cout << tabuSet.begin()->at(0) << std::endl;
                if (neighbours.size() == 0) {
                    std::cout << "Ate my tail" << std::endl;
                    continue;
                }

                auto nextSolution = util->getBestNeighbour(bestSolution);

                if (util->getBins(nextSolution).size() <= util->getBins(bestSolution).size()) {
                    bestSolution = nextSolution;
                }

                tabuList.push_back(nextSolution);
                tabuSet.insert(nextSolution);
            }
            else {
                break;
            }
        }

        std::cout << "Tabu algorithm bins used: " << bestBinsCount << std::endl;
        std::cout << "Following bins content: " << std::endl;
        util->printBins(util->getBins(bestSolution));
};
