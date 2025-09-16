#include "MacAddressDeviceIdGenerator.h"

#ifdef NATIVE_BUILD
#include "../../../test/native_stubs.h"
#else
#include <WiFi.h>
#endif

#include <iomanip>
#include <sstream>
#include <algorithm>

std::string MacAddressDeviceIdGenerator::generate() {
    // Obtenir l'adresse MAC de l'ESP32
    uint8_t mac[6];
    WiFi.macAddress(mac);
    
    // Créer un ID hexadécimal sur 6 chiffres à partir des 3 derniers octets de la MAC
    std::string deviceId = "carpe-";
    
    // Utiliser un stringstream pour formatter en hexadécimal
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    
    // Utiliser les 3 derniers octets de l'adresse MAC
    for (int i = 3; i < 6; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(mac[i]);
    }
    
    deviceId += ss.str();
    return deviceId;
} 