#ifndef BINPACKINGPROBLEM_UTIL_H
#define BINPACKINGPROBLEM_UTIL_H

#include <iostream>
#include <vector>
#include <random>

namespace {
auto randomDevice = std::random_device{};
auto generator = std::mt19937{randomDevice()};

//int binWeightLimit = 12;
int binWeightLimit = 10;
}

class Util {
    public:
    std::vector<int> randomSolution(std::vector<int> items) {
        auto randomizedItems = items;
        std::shuffle(randomizedItems.begin(), randomizedItems.end(), generator);
        return randomizedItems;
    }

    auto getBins(const std::vector<int>& a) {
        auto bins = std::vector<std::vector<int>>{{}};
        int lastBinWeight = 0;

        for (int i : a) {
            if ((lastBinWeight + i) > binWeightLimit) {
                bins.push_back({i});
                lastBinWeight = i;
            }
            else {
                bins.back().push_back(i);
                lastBinWeight += i;
            }
        }
        return bins;
    }

    std::vector<int> getBestNeighbour(const std::vector<int> &items) {

        auto neighbours = getNeighbours(items);

        auto util = new Util();

        auto bestNeighbour = *std::max_element(
                neighbours.begin(),
                neighbours.end(),
                [util](auto l, auto r) {
                    return util->getBins(l).size() > util->getBins(r).size();
                });

//        for (int i = 0; i < neighbours.size() - 1; i++) {
//            if (getBins(neighbours.at(i)).size() < getBins(neighbours.at(i + 1)).size()) {
//                bestNeighbour = neighbours.at(i);
//            }
//            else {
//                bestNeighbour = neighbours.at(i+1);
//            }
//        }

        return bestNeighbour;
    }

    std::vector<int> getRandomizedBinsOrder(std::vector<int> items) {
        auto itemsBins = getBins(items);
        std::shuffle(itemsBins.begin(), itemsBins.end(), generator);

        std::vector<int> shuffledBins;
        for (auto bin : itemsBins) {
            for (auto item : bin) {
                shuffledBins.push_back(item);
            }
        }
        return shuffledBins;
    }

    std::vector<int> getRandomNeighbour(std::vector<int> items) {
        auto newNeighbour = items;

        auto distribution = std::uniform_int_distribution<int>{0, (int)items.size() - 1};
        int randomIndex = distribution(generator);
        int nextIndex = (randomIndex + 1) % items.size();
        std::swap(newNeighbour[randomIndex], newNeighbour[nextIndex]);

        return newNeighbour;
    }

    std::vector<std::vector<int>> getNeighbours(std::vector<int> items) {
        auto newNeighbour = items;
        auto neighbours = std::vector<std::vector<int>>{};

        for (int i = 0; i < items.size(); i++) {
            std::swap(newNeighbour[i], newNeighbour[(i + 1) % items.size()]);
            neighbours.push_back(newNeighbour);
        }
        return neighbours;
    }

    void printBins(const std::vector<std::vector<int>>& bins) {
        for (auto bin : bins) {
            for (auto item : bin) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }

};

#endif //BINPACKINGPROBLEM_UTIL_H
