#pragma once
#include "../RandomService.h"
#include <random>

/**
 * @brief Implémentation native de RandomService utilisant std::random
 * Pour les tests sur desktop et environnements non-Arduino
 */
class NativeRandomService : public RandomService {
private:
    mutable std::mt19937 generator;
    
public:
    NativeRandomService() : generator(std::random_device{}()) {}
    
    int getRandomInt(int min, int max) override {
        std::uniform_int_distribution<int> distribution(min, max - 1);
        return distribution(generator);
    }
    
    void setSeed(unsigned long seed) override {
        generator.seed(seed);
    }
}; 