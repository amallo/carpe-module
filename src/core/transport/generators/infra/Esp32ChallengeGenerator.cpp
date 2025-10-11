#include "Esp32ChallengeGenerator.h"
#include "core/transport/model/Challenge.h"
#include <sstream>
#include <iomanip>
#include <Arduino.h>

Esp32ChallengeGenerator::Esp32ChallengeGenerator(RandomProvider* randomProvider) 
    : randomProvider(randomProvider) {
}

Challenge* Esp32ChallengeGenerator::generateChallenge() {
    std::string challengeId = generateChallengeId();
    std::string pinCode = generatePinCode();
    
    return new Challenge(challengeId, pinCode);
}

std::string Esp32ChallengeGenerator::generateChallengeId() {
    // Générer un ID unique basé sur le timestamp et un nombre aléatoire
    std::stringstream ss;
    ss << "challenge-" << millis() << "-" << randomProvider->getRandomInt(1000, 9999);
    return ss.str();
}

std::string Esp32ChallengeGenerator::generatePinCode() {
    // Générer un PIN à 4 chiffres
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << randomProvider->getRandomInt(0, 9999);
    return ss.str();
}
