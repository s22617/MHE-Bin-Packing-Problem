#include "hill-climbing/HillClimbing.h"

auto items = std::vector<int> {2, 5, 8, 5, 4, 1, 4};

HillClimbing* HillClimbing::sInstance = nullptr;

int main() {
    HillClimbing::getInstance()->runHillClimbing(items);
    return 0;
}