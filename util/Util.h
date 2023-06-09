#ifndef BINPACKINGPROBLEM_UTIL_H
#define BINPACKINGPROBLEM_UTIL_H

#include <iostream>
#include <vector>
#include <random>

auto randomDevice = std::random_device{};
auto generator = std::mt19937{randomDevice()};

int binWeightLimit = 10;

class Util {
    public:
    std::vector<int> getRandomNeighbour(const std::vector<int>& items) {
        auto newNeighbour = items;

        auto distribution = std::uniform_int_distribution<int>{0, (int)items.size() - 1};
        int swapIndex1 = distribution(generator);
        int swapIndex2 = (swapIndex1 + 1) % items.size();
        std::swap(newNeighbour[swapIndex1], newNeighbour[swapIndex2]);

        return newNeighbour;
    }

    std::vector<std::vector<int>> getNeighbours(const std::vector<int>& items) {
        auto newNeighbour = items;
        auto neighbours = std::vector<std::vector<int>>{};

        for (int i = 0; i < items.size(); i++) {
            std::swap(newNeighbour[i], newNeighbour[(i + 1) % items.size()]);
            neighbours.push_back(newNeighbour);
        }
        return neighbours;
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