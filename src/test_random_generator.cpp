#include <Arduino.h>
#include "core/RandomDeviceGenerator.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("🎲 Test du RandomDeviceGenerator");
    Serial.println("================================");
    
    RandomDeviceGenerator* generator = new RandomDeviceGenerator();
    
    // Générer plusieurs IDs pour montrer la variété
    Serial.println("Génération de 10 IDs aléatoires :");
    for (int i = 0; i < 10; i++) {
        String deviceId = generator->generate();
        Serial.println("  " + String(i+1) + ". " + deviceId);
        delay(100); // Petit délai pour varier le seed
    }
    
    Serial.println("\n✅ Test terminé !");
    
    delete generator;
}

void loop() {
    // Rien à faire dans la boucle
} 