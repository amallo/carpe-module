#pragma once
#include <Arduino.h>
#include "../DeviceIdGenerator.h"

/**
 * @brief Générateur d'ID de device aléatoire
 * Implémente DeviceIdGenerator avec une stratégie de génération aléatoire
 * Format: carpe-XXXXXX (6 caractères alphanumériques)
 */
class RandomDeviceIdGenerator : public DeviceIdGenerator {
public:
    /**
     * @brief Génère un ID aléatoire pour le device au format carpe-XXXXXX
     * @return String ID aléatoire avec 6 caractères alphanumériques
     */
    String generate() override;
}; 