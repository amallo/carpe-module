#pragma once
#include "core/transport/AuthMessageEncoder.h"
#include "ESP32MessageHeaderEncoder.h"
#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief Implémentation ESP32 de l'encodeur de messages d'authentification
 * Utilise ESP32MessageHeaderEncoder pour l'encodage commun et ajoute les champs spécifiques
 */
class Esp32AuthMessageEncoder : public AuthMessageEncoder {
public:
    Esp32AuthMessageEncoder();
    
    std::vector<uint8_t> encode(const AuthRequestMessage& message) const override;
    
private:
    ESP32MessageHeaderEncoder headerEncoder;
};
