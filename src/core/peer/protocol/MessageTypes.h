#pragma once
#include <cstdint>

/**
 * @brief Types de messages du protocole CARPE
 * 
 * Ces constantes définissent les types de messages supportés.
 * Voir protocol.md pour la spécification complète.
 */
namespace MessageType {
    constexpr uint8_t INITIATE_AUTH_CHALLENGE = 0x04;
    constexpr uint8_t AUTH_CHALLENGE_NEGOTIATION_SUCCESS = 0x05;
    constexpr uint8_t AUTH_CHALLENGE_NEGOTIATION_FAILURE = 0x06;
    constexpr uint8_t USER_MESSAGE = 0x07;
    
    /**
     * @brief Vérifie si un type est valide
     * @param type Type à vérifier
     * @return true si le type est connu, false sinon
     */
    inline bool isValid(uint8_t type) {
        return type == INITIATE_AUTH_CHALLENGE ||
               type == AUTH_CHALLENGE_NEGOTIATION_SUCCESS ||
               type == AUTH_CHALLENGE_NEGOTIATION_FAILURE ||
               type == USER_MESSAGE;
    }
}

