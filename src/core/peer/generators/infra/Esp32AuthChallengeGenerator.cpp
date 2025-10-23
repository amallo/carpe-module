#include "Esp32AuthChallengeGenerator.h"
#include "core/peer/model/AuthChallenge.h"
#include <sstream>

Esp32AuthChallengeGenerator::Esp32AuthChallengeGenerator(RandomProvider* randomProvider) 
    : randomProvider(randomProvider) {
}

AuthChallenge* Esp32AuthChallengeGenerator::generateChallenge() {
    // Générer un ID de challenge aléatoire
    std::string challengeId;
    for (int i = 0; i < 16; i++) {
        int randomChar = randomProvider->getRandomInt(0, 10);
        challengeId += std::to_string(randomChar);
    }
    
    // Générer un PIN code aléatoire
    std::string pinCode;
    for (int i = 0; i < 6; i++) {
        int randomDigit = randomProvider->getRandomInt(0, 10);
        pinCode += std::to_string(randomDigit);
    }
    
    return new AuthChallenge(challengeId, pinCode);
}
