//
// Created by Dan on 22.06.2023.
//

#ifndef BINPACKINGPROBLEM_SIMULATEDANNEALING_H
#define BINPACKINGPROBLEM_SIMULATEDANNEALING_H

#include <vector>
#include <functional>
#include <map>

class SimulatedAnnealing {
public:
    static SimulatedAnnealing* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new SimulatedAnnealing();
    }

    void simulatedAnnealing(std::vector<int> items, int tp_type, int binSize, int iter);

private:
    int bestBinsCount;
    static SimulatedAnnealing* sInstance;
};


#endif //BINPACKINGPROBLEM_SIMULATEDANNEALING_H
