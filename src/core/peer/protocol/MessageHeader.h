#pragma once
#include <vector>
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
    
    /**
     * @brief Encode le header en binaire (TYPE + NONCE)
     * @return Vecteur de 3 bytes: [TYPE][NONCE_H][NONCE_L] (big-endian)
     */
    std::vector<uint8_t> encode() const {
        std::vector<uint8_t> data;
        data.push_back(type);
        data.push_back((nonce >> 8) & 0xFF);  // Big-endian
        data.push_back(nonce & 0xFF);
        return data;
    }

    bool operator==(const MessageHeader& other) const {
        return type == other.type && nonce == other.nonce;
    }
};
