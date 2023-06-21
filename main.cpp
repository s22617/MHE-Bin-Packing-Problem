#include "hill-climbing/HillClimbing.h"

auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4, 4, 5, 7, 2, 6, 7, 8, 9, 3, 4, 6, 5, 7, 8, 1, 1, 1, 2, 2, 2};

HillClimbing* HillClimbing::sInstance = nullptr;

int main() {
    HillClimbing::getInstance()->randomHillClimbing(items);
    HillClimbing::getInstance()->deterministicHillClimbing(items);
    return 0;
}