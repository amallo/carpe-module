#include "RandomDeviceIdGenerator.h"

String RandomDeviceIdGenerator::generate() {
    // Initialiser le générateur aléatoire avec un seed basé sur le temps de démarrage
    randomSeed(micros());
    
    // Créer l'ID de base
    String deviceId = "carpe-";
    
    // Caractères possibles : 0-9 et A-Z (36 caractères au total)
    const char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int numChars = sizeof(chars) - 1; // -1 pour exclure le \0
    
    // Générer 6 caractères aléatoires
    for (int i = 0; i < 6; i++) {
        int randomIndex = random(0, numChars);
        deviceId += chars[randomIndex];
    }
    
    return deviceId;
} 