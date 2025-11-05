#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include "core/peer/model/MessageHeader.h"

/**
 * @brief Encodeur commun pour les headers de messages ESP32
 * Gère l'encodage des champs communs : type, nonce, et autres champs futurs
 */
class ESP32MessageHeaderEncoder {
public:
    ESP32MessageHeaderEncoder();
    
    /**
     * @brief Encode le header commun d'un message
     * @param header Header du message à encoder
     * @return Vecteur d'octets contenant le header encodé
     */
    std::vector<uint8_t> encodeHeader(const MessageHeader& header) const;
    
    
private:
    std::vector<uint8_t> encodeNonce(uint16_t nonce) const;
};
