#ifndef BINPACKINGPROBLEM_TABU_H
#define BINPACKINGPROBLEM_TABU_H


#include <vector>

class Tabu {
public:
    static Tabu* getInstance() {
        return sInstance = (sInstance != nullptr) ? sInstance : new Tabu();
    }

    void tabuSearch(std::vector<int> items);

private:
    int bestBinsCount;
    static Tabu* sInstance;
};


#endif //BINPACKINGPROBLEM_TABU_H
