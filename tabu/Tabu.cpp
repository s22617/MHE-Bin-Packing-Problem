#include <algorithm>
#include <list>
#include <set>
#include "Tabu.h"
#include "../util/Util.h"


void Tabu::tabuSearch(std::vector<int> items, int tabuSize, int binSize, int iter) {
    auto util = new Util(binSize);

    auto shuffledItems = util->randomSolution(items);

    std::list<std::vector<int>> tabuList;
    tabuList.push_back(shuffledItems);

    std::set<std::vector<int>> tabuSet;
    tabuSet.insert(shuffledItems);

    auto bestSolution = shuffledItems;
        for (int i = 0; i < iter; i++) {
            for (auto item : bestSolution) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
            if (tabuSet.size() < tabuSize) {
                auto neighbours = util->getNeighbours(tabuList.back());

                neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(),
                                                [&](std::vector<int> bin) {
                                                    return tabuSet.find(bin) != tabuSet.end();
                                                }),
                                 neighbours.end());

                //std::cout << tabuSet.begin()->at(0) << std::endl;
                if (neighbours.size() == 0) {
                    //add backtracking
                    std::cout << "Ate my tail" << std::endl;
                    continue;
                }

                //auto nextSolution = util->getBestNeighbour(bestSolution);

                auto nextSolution = *std::max_element(
                        neighbours.begin(),
                        neighbours.end(),
                        [&](auto l, auto r) {
                            return util->getBins(l).size() > util->getBins(r).size();
                        });
                int a = util->getBins(nextSolution).size();
                int b = util->getBins(bestSolution).size();

                if (util->getBins(nextSolution).size() < util->getBins(bestSolution).size()) {
                    bestSolution = nextSolution;
                }

                tabuList.push_back(nextSolution);
                tabuSet.insert(nextSolution);
            }
            else {
                break;
            }
        }

        std::cout << "Tabu algorithm bins used: " << util->getBins(bestSolution).size() << std::endl;
        std::cout << "Following bins content: " << std::endl;
        util->printBins(util->getBins(bestSolution));
};
