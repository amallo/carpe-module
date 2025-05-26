#pragma once
#include <Arduino.h>

class RandomDeviceIdGenerator {
public:
    /**
     * @brief Génère un ID aléatoire pour le device au format carpe-XXXXXX
     * @return String ID aléatoire avec 6 caractères alphanumériques
     */
    String generate();
}; 