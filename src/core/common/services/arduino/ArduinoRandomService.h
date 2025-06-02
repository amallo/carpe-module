#pragma once
#include "../RandomService.h"
#include <Arduino.h>

/**
 * @brief Implémentation Arduino de RandomService utilisant random() et randomSeed()
 * Pour le hardware ESP32 et environnements Arduino
 */
class ArduinoRandomService : public RandomService {
public:
    int getRandomInt(int min, int max) override {
        return random(min, max);
    }
    
    void setSeed(unsigned long seed) override {
        randomSeed(seed);
    }
}; 