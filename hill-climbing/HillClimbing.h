#ifndef BINPACKINGPROBLEM_HILLCLIMBING_H
#define BINPACKINGPROBLEM_HILLCLIMBING_H

#include <vector>

class HillClimbing {
    public:
    static HillClimbing* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new HillClimbing();
    }

    void HillClimbing::runHillClimbing(std::vector<int> items);

    private:
    std::vector<int> getBestNeighbour(const std::vector<int>& items);
    static HillClimbing* sInstance;
};


#endif //BINPACKINGPROBLEM_HILLCLIMBING_H
