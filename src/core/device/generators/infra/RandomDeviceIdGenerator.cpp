#include "RandomDeviceIdGenerator.h"

RandomDeviceIdGenerator::RandomDeviceIdGenerator(RandomProvider* randomProvider, TimeProvider* timeProvider) 
    : randomProvider(randomProvider), timeProvider(timeProvider) {
    // Initialiser le seed avec le temps actuel
    randomProvider->setSeed(timeProvider->getMicros());
}

std::string RandomDeviceIdGenerator::generate() {
    // Créer l'ID de base
    std::string deviceId = "carpe-";
    
    // Caractères possibles : 0-9 et A-Z (36 caractères au total)
    const char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int numChars = 36;
    
    // Générer 6 caractères aléatoires
    for (int i = 0; i < 6; i++) {
        int randomIndex = randomProvider->getRandomInt(0, numChars);
        deviceId += chars[randomIndex];
    }
    
    return deviceId;
} 