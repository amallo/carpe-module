#pragma once
#include "core/device/generators/CommonIDGenerator.h"

/**
 * @brief Implémentation ESP32 du générateur d'identifiants communs
 * 
 * Utilise l'entropie hardware de l'ESP32 pour générer des identifiants
 * sécurisés compatibles avec les contraintes de l'embarqué.
 */
class ESP32CommonIDGenerator : public CommonIDGenerator {
public:
    /**
     * @brief Génère un identifiant unique (UUID v4 format)
     * @return Un UUID v4 sous forme de string
     */
    std::string generate() override;

private:
    /**
     * @brief Génère un UUID v4 compatible ESP32
     * @return Un UUID v4 sous forme de string
     */
    std::string generateUUID();
};