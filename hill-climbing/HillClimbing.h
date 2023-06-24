#ifndef BINPACKINGPROBLEM_HILLCLIMBING_H
#define BINPACKINGPROBLEM_HILLCLIMBING_H

#include <vector>

class HillClimbing {
    public:
    static HillClimbing* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new HillClimbing();
    }

    void randomHillClimbing(std::vector<int> items, int binSize);
    void deterministicHillClimbing(std::vector<int> items, int binSize);

    private:
    int bestBinsCount;
    static HillClimbing* sInstance;
};


#endif //BINPACKINGPROBLEM_HILLCLIMBING_H
