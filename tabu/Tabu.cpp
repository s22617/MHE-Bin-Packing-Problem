#include <algorithm>
#include <list>
#include <set>
#include "Tabu.h"
#include "../util/Util.h"

void tabuSearch(std::vector<int> items) {
    auto util = new Util();

    std::list<std::vector<int>> tabuList;
    std::set<std::vector<int>> tabuSet;

    auto bestSolution = items;
    for (int i = 0; i < 5000; i++) {
        auto neighbours = util->getNeighbours(bestSolution);
        bestSolution = neighbours.at(0);

        for (auto solution : neighbours) {
            neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(),
                                            [&](std::vector<int> bin) { return tabuSet.contains(); }))
        }
    }
}