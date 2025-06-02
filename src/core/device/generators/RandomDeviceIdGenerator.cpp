#include "RandomDeviceIdGenerator.h"

RandomDeviceIdGenerator::RandomDeviceIdGenerator(RandomService* randomService, TimeService* timeService) 
    : randomService(randomService), timeService(timeService) {
    // Initialiser le seed avec le temps actuel
    randomService->setSeed(timeService->getMicros());
}

std::string RandomDeviceIdGenerator::generate() {
    // Créer l'ID de base
    std::string deviceId = "carpe-";
    
    // Caractères possibles : 0-9 et A-Z (36 caractères au total)
    const char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int numChars = 36;
    
    // Générer 6 caractères aléatoires
    for (int i = 0; i < 6; i++) {
        int randomIndex = randomService->getRandomInt(0, numChars);
        deviceId += chars[randomIndex];
    }
    
    return deviceId;
} 