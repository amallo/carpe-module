#include "MacAddressDeviceIdGenerator.h"
#include <WiFi.h>

String MacAddressDeviceIdGenerator::generate() {
    // Obtenir l'adresse MAC de l'ESP32
    uint8_t mac[6];
    WiFi.macAddress(mac);
    
    // Créer un ID hexadécimal sur 6 chiffres à partir des 3 derniers octets de la MAC
    String deviceId = "carpe-";
    
    // Utiliser les 3 derniers octets de l'adresse MAC
    for (int i = 3; i < 6; i++) {
        if (mac[i] < 16) {
            deviceId += "0"; // Ajouter un zéro devant si nécessaire
        }
        deviceId += String(mac[i], HEX);
    }
    
    deviceId.toUpperCase(); // Convertir en majuscules
    return deviceId;
} 