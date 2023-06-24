#include <functional>
#include <map>
#include "GeneticAlgorithm.h"
#include "../util/Util.h"

std::vector<std::vector<int>> GeneticAlgorithm::getInitialPopulation(std::vector<int> items, int populationSize) {
    auto util = new Util();
    std::vector<std::vector<int>> population;
    for (int i = 0; i < populationSize; i++) {
        population.push_back(util->randomSolution(items));
    }

    return population;
}

double GeneticAlgorithm::calculateFitness(std::vector<int> solution){
    auto util = new Util();
    return 1.0 / (1 + (double) util->getBins(solution).size());
}

const auto ITERATION_COUNT_LIMIT = 10;

bool GeneticAlgorithm::endOnIterationCount() {
    return iterationCount++ >= ITERATION_COUNT_LIMIT;
}

bool GeneticAlgorithm::endOnSharedPopulationFitness(std::vector<std::vector<int>> &population) {
    std::map<double, int> numberOfSpecificFitnessSolution;

    auto specificSolutionCountPercentage = population.size() * 60 / 100;

    for (int i = 0; i < population.size(); i++) {

        auto fitness = calculateFitness(population[i]);

        if (numberOfSpecificFitnessSolution.count(fitness) != 0) {
            numberOfSpecificFitnessSolution[fitness] += 1;
        } else {
            numberOfSpecificFitnessSolution[fitness] = 1;
        }

        std::cout << "specificSolutionCountPercentage: " << specificSolutionCountPercentage;
        std::cout << " FITNESS: " << fitness;
        std::cout << " numberOfSpecificFitnessSolution: " << numberOfSpecificFitnessSolution[fitness] << std::endl;

        if (numberOfSpecificFitnessSolution[fitness] >= specificSolutionCountPercentage) {
            return true;
        }
    }

    return false;
}

bool GeneticAlgorithm::terminalCondition(int terminalConditionType, std::vector<std::vector<int>> &population) {
    switch (terminalConditionType) {
        case 1:
            return endOnSharedPopulationFitness(population);
        case 2:
            return endOnIterationCount();
        default:
            std::cout << "WRONG TERMINAL CONDITION TYPE ERROR" << std::endl;
            exit(0);
    }
}



std::vector<std::vector<int>> GeneticAlgorithm::selection(std::vector<std::vector<int>> population) {
    std::vector<int> fitnesses;

    for (int i = 0; i < population.size(); i++) {
        fitnesses.push_back(calculateFitness(population[i]));
    }

    std::vector<std::vector<int>> parents;
    auto dist = std::uniform_int_distribution<int>{0, (int)population.size() - 1};

    while (parents.size() < population.size()) {
        auto parentIndexA = dist(generator);
        auto parentIndexB = dist(generator);

        parents.push_back(
                fitnesses[parentIndexA] >= fitnesses[parentIndexB]
                ? population[parentIndexA] : population[parentIndexB]);
    }

    return parents;
}

std::map<int, int> getItemsNumberPerWeightCount(std::vector<int> &items) {
    std::map<int, int> availableItemsWeightCount;

    for (auto item : items) {
        if (availableItemsWeightCount[item] != 0) {
            availableItemsWeightCount[item] += 1;
        } else {
            availableItemsWeightCount[item] = 1;
        }
    }

    return availableItemsWeightCount;
}

void printItems(std::vector<int> child) {
    std::cout << "Printing items: " << std::endl;
    for (auto item : child) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void insertItemToChild_tab(int targetIndex, int itemWeight, int child[],
                       std::map<int, int> &child_ItemsWeightCount, std::map<int, int> &availableItemsWeightCount) {

    if (child_ItemsWeightCount.count(itemWeight) != 0 && child_ItemsWeightCount[itemWeight] == availableItemsWeightCount[itemWeight]) {
        //printItems(child);
        return;
    }

    if (child_ItemsWeightCount.count(itemWeight) != 0) {
        child_ItemsWeightCount[itemWeight] += 1;
    } else {
        child_ItemsWeightCount[itemWeight] = 1;
    }

    if (false) {
        //child.push_back(itemWeight);
    } else {
        child[targetIndex] = itemWeight;
    }

    //printItems(child);

    //std::cout << child.size() << std::endl;

}

void insertItemToChild(int targetIndex, int itemWeight, std::vector<int> &child,
                       std::map<int, int> &child_ItemsWeightCount, std::map<int, int> &availableItemsWeightCount) {

    if (child_ItemsWeightCount.count(itemWeight) != 0 && child_ItemsWeightCount[itemWeight] == availableItemsWeightCount[itemWeight]) {
        //printItems(child);
        return;
    }

    if (child_ItemsWeightCount.count(itemWeight) != 0) {
        child_ItemsWeightCount[itemWeight] += 1;
    } else {
        child_ItemsWeightCount[itemWeight] = 1;
    }

    if (targetIndex >= child.size() || targetIndex == -1) {
        child.push_back(itemWeight);
    } else {
        child.insert(child.begin() + targetIndex, itemWeight);
    }

    //printItems(child);

    //std::cout << child.size() << std::endl;

}

int findItemIndex(std::vector<int> &parent, int itemWeight) {
    for (int i = 0; i <= parent.size(); i++) {
        if (parent[i] == itemWeight) {
            return i;
        }
    }
    return -1;
}

int findAvailableIndex(int child[], int parentSize) {
    for (int i = 0; i < parentSize; i++) {
        if (child[i] < 0) {
            return i;
        }
    }
    return -1;
}

std::pair<std::vector<int>, std::vector<int>> crossoverPMX(std::vector<int> parentA , std::vector<int> parentB) {

//    parentA = {4, 4, 4, 1, 5, 8, 2, 5};
//    parentB = {1, 5, 5, 4, 8, 4, 4, 2};

    std::vector<int> childA;
    int *childA_tab = new int[parentA.size()];
    std::vector<int> childB;
    int *childB_tab = new int[parentB.size()];
    std::map<int, int> childA_ItemsWeightCount;
    std::map<int, int> childB_ItemsWeightCount;


//    std::cout << "Parent A: " << std::endl;
//    printItems(parentA);
//    std::cout << "Parent B: " << std::endl;
//    printItems(parentB);

    int sliceIndex1 = 2;
    int sliceIndex2 = 5;

    auto availableItemsWeightCount = getItemsNumberPerWeightCount(parentA);

    for (int i = sliceIndex1; i < sliceIndex2; i++) {
        insertItemToChild_tab(i, parentB[i], childA_tab, childA_ItemsWeightCount, availableItemsWeightCount);
        insertItemToChild_tab(i, parentA[i], childB_tab, childB_ItemsWeightCount, availableItemsWeightCount);
    }

    for (int i = 0; i < sliceIndex1; i++) {
        insertItemToChild_tab(i, parentA[i], childA_tab, childA_ItemsWeightCount, availableItemsWeightCount);
        insertItemToChild_tab(i, parentB[i], childB_tab, childB_ItemsWeightCount, availableItemsWeightCount);
    }

    for (int i = sliceIndex2; i < parentA.size(); i++) {
        insertItemToChild_tab(i, parentA[i], childA_tab, childA_ItemsWeightCount, availableItemsWeightCount);
        insertItemToChild_tab(i, parentB[i], childB_tab, childB_ItemsWeightCount, availableItemsWeightCount);
    }

    int itemIndexToBeInserted;
    for (auto [itemWeight, count] : availableItemsWeightCount) {
        while (childA_ItemsWeightCount.count(itemWeight) == 0 || childA_ItemsWeightCount[itemWeight] != count) {
            itemIndexToBeInserted = findAvailableIndex(childA_tab, parentA.size());
            childA_tab[itemIndexToBeInserted] = itemWeight;
            childA_ItemsWeightCount[itemWeight] += 1;
            //std::cout << childA_ItemsWeightCount[itemWeight] << std::endl;
            //insertItemToChild(itemIndexToBeInserted, itemWeight, child_testA, childA_ItemsWeightCount, availableItemsWeightCount);
        }
        while (childB_ItemsWeightCount.count(itemWeight) == 0 || childB_ItemsWeightCount[itemWeight] != count) {
            itemIndexToBeInserted = findAvailableIndex(childB_tab, parentA.size());
            childB_tab[itemIndexToBeInserted] = itemWeight;
            childB_ItemsWeightCount[itemWeight] += 1;

            //insertItemToChild(itemIndexToBeInserted, itemWeight, child_testB, childB_ItemsWeightCount, availableItemsWeightCount);
        }
    }


    std::vector<int> child_testA(parentA.size());

    for (int i = 0; i < parentA.size(); i++) {
        if (childA_tab[i] > -1) {
            child_testA[i] = childA_tab[i];
        }
    }

    std::vector<int> child_testB(parentA.size());

    for (int i = 0; i < parentA.size(); i++) {
        if (childB_tab[i] > -1) {
            child_testB[i] = childB_tab[i];
        }
    }

//    std::cout << "Child A: ";
//    for (auto item : child_testA) {
//        std::cout << item << " ";
//    }
//    std::cout << std::endl;
//
//    std::cout << "Child B: ";
//    for (auto item : child_testB) {
//        std::cout << item << " ";
//    }
//    std::cout << std::endl;


//    std::cout << "Child A: ";
//    for (int i = 0; i < parentA.size(); i++) {
//        std::cout << childA_tab[i] << " ";
//    }
//    std::cout << std::endl;
//
//    std::cout << "Child B: ";
//    for (int i = 0; i < parentA.size(); i++) {
//        std::cout << childB_tab[i] << " ";
//    }
//    std::cout << std::endl;

    delete[] childA_tab;
    delete[] childB_tab;

//    std::cout << "Child A: ";
//    for (auto item : childA_tab) {
//        std::cout << item << " ";
//    }
//    std::cout << std::endl;
//
//    std::cout << "Child B: ";
//    for (auto item : childB) {
//        std::cout << item << " ";
//    }
//    std::cout << std::endl;

    //exit(0);


    return {child_testA, child_testB};
}

std::pair<std::vector<int>, std::vector<int>> crossover(std::vector<int> parentA , std::vector<int> parentB) {
    std::vector<int> childA;
    std::vector<int> childB;
    std::map<int, int> childA_ItemsWeightCount;
    std::map<int, int> childB_ItemsWeightCount;

//    parentA = {4, 4, 4, 1, 5, 8, 2, 5};
//    parentB = {1, 5, 5, 4, 8, 4, 4, 2};

//    std::cout << "Parent A: " << std::endl;
//    printItems(parentA);
//    std::cout << "Parent B: " << std::endl;
//    printItems(parentB);

    // get global number of items per weight map from whatever parent
    auto availableItemsWeightCount = getItemsNumberPerWeightCount(parentA);

    for (int i = 0; i < parentA.size(); i++) {
        if (i % 2) {
            insertItemToChild(-1, parentA[i], childA, childA_ItemsWeightCount, availableItemsWeightCount);
            insertItemToChild(-1, parentB[i], childB, childB_ItemsWeightCount, availableItemsWeightCount);
        }
        else {
            insertItemToChild(-1, parentB[i], childA, childA_ItemsWeightCount, availableItemsWeightCount);
            insertItemToChild(-1, parentA[i], childB, childB_ItemsWeightCount, availableItemsWeightCount);
        }
    }

    //exit(0);
    //std::cout << "ADDING REST OF ITEMS" << std::endl;

    // add left items to children
    int itemIndexToBeInserted;
    for (auto [itemWeight, count] : availableItemsWeightCount) {
        while (childA_ItemsWeightCount.count(itemWeight) == 0 || childA_ItemsWeightCount[itemWeight] != count) {
            itemIndexToBeInserted = findItemIndex(parentA, itemWeight);
            insertItemToChild(itemIndexToBeInserted, itemWeight, childA, childA_ItemsWeightCount, availableItemsWeightCount);
        }
        while (childB_ItemsWeightCount.count(itemWeight) == 0 || childB_ItemsWeightCount[itemWeight] != count) {
            itemIndexToBeInserted = findItemIndex(parentB, itemWeight);
            insertItemToChild(itemIndexToBeInserted, itemWeight, childB, childB_ItemsWeightCount, availableItemsWeightCount);
        }
    }

    return {childA, childB};
}

auto getChildren(std::vector<std::vector<int>> parents) {
    std::vector<std::vector<int>> children;

    for (int i = 0; i < parents.size(); i++) {
        if (i % 2) {
            auto createdChildren = crossoverPMX(parents[i], parents[i - 1]);

            //std::cout << parents[i].size() << std::endl;

            //exit(0);

            children.push_back(createdChildren.first);
            children.push_back(createdChildren.second);

        } else if (i == parents.size() - 1) {
            auto createdChildren = crossoverPMX(parents[i], parents[i - 1]);

            children.push_back(createdChildren.first);
        }
    }

    return children;
}

// MUTATION 1

std::vector<int> shuffleRandomBins(std::vector<int> &child, Util *util) {
    return util->getRandomizedBinsOrder(child);
}

// MUTATION 2
std::vector<int> swapRandomItems(std::vector<int> &child, Util *util) {
    return util->getRandomNeighbour(child);
}

std::vector<int> GeneticAlgorithm::mutation(std::vector<int> child, int mutationType) {
    auto util = new Util();

    switch (mutationType) {
        case 1:
            return shuffleRandomBins(child, util);
        case 2:
            return swapRandomItems(child, util);
        default:
            std::cout << "WRONG MUTATION TYPE ERROR" << std::endl;
            exit(0);
    }

    return util->getRandomNeighbour(child);
}

void GeneticAlgorithm::geneticAlgorithm(std::vector<int> items, int parameters[4]) {
    auto population = getInitialPopulation(items, parameters[0]);

    while(!terminalCondition(parameters[1], population)) {
        auto parents = selection(population);
        auto children = getChildren(parents);

        std::vector<std::vector<int>> modifiedChildren;

        for (auto &child : children) {
            modifiedChildren.push_back(mutation(child, parameters[3]));
        }
//
        population = std::move(modifiedChildren);

//        for (int i = 0; i < children.size(); i++) {
//            for (auto item : children[i]) {
//                    std::cout << item << " ";
//            }
//            std::cout << std::endl;
//        }
    }

//        for (int i = 0; i < population.size(); i++) {
//            for (auto item : population[i]) {
//                    std::cout << item << " ";
//            }
//            std::cout << "FITNESS: " << calculateFitness(population[i]);
//            std::cout << std::endl;
//        }


    std::vector<int> bestSolution = *std::max_element(
            population.begin(),
            population.end(),
            [&](auto l, auto r) {
                return calculateFitness(l) < calculateFitness(r);
            });

    auto util = new Util();
    std::cout << util->getBins(bestSolution).size() << std::endl;

//    for (auto solution : population) {
//        for (auto item : solution) {
//            std::cout << item << " ";
//        }
//        std::cout << std::endl;
//    }

}
