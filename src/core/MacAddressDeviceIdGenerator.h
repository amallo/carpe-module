#pragma once
#include <Arduino.h>

class MacAddressDeviceIdGenerator {
public:
    /**
     * @brief Génère un ID unique pour le device au format carpe-XXXXXX
     * @return String ID unique basé sur l'adresse MAC
     */
    String generate();
}; 