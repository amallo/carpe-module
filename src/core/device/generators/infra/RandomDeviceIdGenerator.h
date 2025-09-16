#pragma once
#include <string>
#include <core/device/generators/DeviceIdGenerator.h>
#include <core/random/providers/RandomProvider.h>
#include <core/time/providers/TimeProvider.h>

/**
 * @brief Générateur d'ID de device aléatoire
 * Implémente DeviceIdGenerator avec une stratégie de génération aléatoire
 * Format: carpe-XXXXXX (6 caractères alphanumériques)
 * Utilise l'injection de dépendances pour RandomService et TimeService
 */
class RandomDeviceIdGenerator : public DeviceIdGenerator {
private:
    RandomProvider* randomProvider;
    TimeProvider* timeProvider;
    
public:
    /**
     * @brief Constructeur avec injection de dépendances
     * @param randomProvider service de génération aléatoire
     * @param timeProvider service de temps
     */
    RandomDeviceIdGenerator(RandomProvider* randomProvider, TimeProvider* timeProvider);
    
    /**
     * @brief Génère un ID aléatoire pour le device au format carpe-XXXXXX
     * @return std::string ID aléatoire avec 6 caractères alphanumériques
     */
    std::string generate() override;
}; 