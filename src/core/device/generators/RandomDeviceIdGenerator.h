#pragma once
#include <string>
#include "../DeviceIdGenerator.h"
#include "../../common/services/RandomService.h"
#include "../../common/services/TimeService.h"

/**
 * @brief Générateur d'ID de device aléatoire
 * Implémente DeviceIdGenerator avec une stratégie de génération aléatoire
 * Format: carpe-XXXXXX (6 caractères alphanumériques)
 * Utilise l'injection de dépendances pour RandomService et TimeService
 */
class RandomDeviceIdGenerator : public DeviceIdGenerator {
private:
    RandomService* randomService;
    TimeService* timeService;
    
public:
    /**
     * @brief Constructeur avec injection de dépendances
     * @param randomService service de génération aléatoire
     * @param timeService service de temps
     */
    RandomDeviceIdGenerator(RandomService* randomService, TimeService* timeService);
    
    /**
     * @brief Génère un ID aléatoire pour le device au format carpe-XXXXXX
     * @return std::string ID aléatoire avec 6 caractères alphanumériques
     */
    std::string generate() override;
}; 