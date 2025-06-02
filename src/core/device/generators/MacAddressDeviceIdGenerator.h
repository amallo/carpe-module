#pragma once
#include <Arduino.h>
#include "../DeviceIdGenerator.h"

/**
 * @brief Générateur d'ID de device basé sur l'adresse MAC
 * Implémente DeviceIdGenerator avec une stratégie basée sur l'adresse MAC WiFi
 * Format: carpe-XXXXXX (basé sur les derniers octets de l'adresse MAC)
 */
class MacAddressDeviceIdGenerator : public DeviceIdGenerator {
public:
    /**
     * @brief Génère un ID unique pour le device au format carpe-XXXXXX
     * @return String ID unique basé sur l'adresse MAC
     */
    String generate() override;
}; 