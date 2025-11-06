#pragma once
#include <cstdint>

/**
 * @brief Header commun à tous les messages du protocole CARPE
 * Contient les champs obligatoires : type (byte) et nonce
 */
class MessageHeader {
public:
    uint8_t type;   // TYPE byte du protocole (0x04, etc.)
    uint16_t nonce; // Valeur anti-replay (2 bytes)
    
    /**
     * @brief Constructeur principal
     * @param type TYPE byte du protocole (0x04, etc.)
     * @param nonce Valeur anti-replay 16-bit
     */
    MessageHeader(uint8_t type, uint16_t nonce);
    
    /**
     * @brief Constructeur par défaut
     */
    MessageHeader() = delete;
    
    /**
     * @brief Destructeur
     */
    ~MessageHeader() = default;
    
    /**
     * @brief Constructeur de copie
     */
    MessageHeader(const MessageHeader& other) = default;
    
    /**
     * @brief Opérateur d'assignation
     */
    MessageHeader& operator=(const MessageHeader& other) = default;
    
    /**
     * @brief Accès au type du message
     */
    uint8_t getType() const {
        return type;
    }
    
    /**
     * @brief Accès au nonce du message
     */
    uint16_t getNonce() const {
        return nonce;
    }

    bool operator==(const MessageHeader& other) const {
        return type == other.type && nonce == other.nonce;
    }
};
