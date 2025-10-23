#pragma once
#include "core/peer/AuthChallengeGenerator.h"
#include "core/random/providers/RandomProvider.h"
#include <string>

/**
 * @brief Implémentation ESP32 du générateur de challenges
 * Génère des challenges avec PIN codes aléatoires pour l'authentification
 */
class Esp32ChallengeGenerator : public AuthChallengeGenerator {
public:
    explicit Esp32ChallengeGenerator(RandomProvider* randomProvider);
    
    AuthChallenge* generateChallenge() override;
    
private:
    RandomProvider* randomProvider;
    std::string generateChallengeId();
    std::string generatePinCode();
};
