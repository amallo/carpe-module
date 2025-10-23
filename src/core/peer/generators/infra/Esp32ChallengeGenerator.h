#pragma once
#include "core/transport/ChallengeGenerator.h"
#include "core/random/providers/RandomProvider.h"
#include <string>

/**
 * @brief Implémentation ESP32 du générateur de challenges
 * Génère des challenges avec PIN codes aléatoires pour l'authentification
 */
class Esp32ChallengeGenerator : public ChallengeGenerator {
public:
    explicit Esp32ChallengeGenerator(RandomProvider* randomProvider);
    
    Challenge* generateChallenge() override;
    
private:
    RandomProvider* randomProvider;
    std::string generateChallengeId();
    std::string generatePinCode();
};
