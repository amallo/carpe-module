#pragma once
#include "core/peer/protocol/MessageHeader.h"
#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief Header spécifique pour USER_MESSAGE
 * Contient MessageHeader (TYPE + NONCE) + SENDER_ID + RECIPIENT_ID
 */
class UserMessageHeader {
public:
    /**
     * @brief Constructeur principal
     * @param senderId Identifiant de l'expéditeur (16 bytes, null-padded)
     * @param recipientId Identifiant du destinataire (16 bytes, null-padded, 0x00...00 pour public)
     * @param header Header de base (TYPE + NONCE)
     */
    UserMessageHeader(const std::vector<uint8_t>& senderId, 
                      const std::vector<uint8_t>& recipientId,
                      const MessageHeader& header);
    
    /**
     * @brief Destructeur
     */
    ~UserMessageHeader() = default;
    
    /**
     * @brief Constructeur de copie
     */
    UserMessageHeader(const UserMessageHeader& other) = default;
    
    /**
     * @brief Opérateur d'assignation
     */
    UserMessageHeader& operator=(const UserMessageHeader& other) = default;
    
    /**
     * @brief Accès au header de base
     */
    const MessageHeader& getHeader() const {
        return header;
    }
    
    /**
     * @brief Accès au type du message
     */
    uint8_t getType() const {
        return header.getType();
    }
    
    /**
     * @brief Accès au nonce du message
     */
    uint16_t getNonce() const {
        return header.getNonce();
    }
    
    /**
     * @brief Accès au SENDER_ID
     */
    const std::vector<uint8_t>& getSenderId() const {
        return senderId;
    }
    
    /**
     * @brief Accès au RECIPIENT_ID
     */
    const std::vector<uint8_t>& getRecipientId() const {
        return recipientId;
    }
    
    /**
     * @brief Encode le header en binaire (TYPE + NONCE + SENDER_ID + RECIPIENT_ID)
     * @return Vecteur de 35 bytes: [TYPE][NONCE_H][NONCE_L][SENDER_ID(16)][RECIPIENT_ID(16)]
     */
    std::vector<uint8_t> encode() const;
    
    bool operator==(const UserMessageHeader& other) const {
        return header == other.header && 
               senderId == other.senderId && 
               recipientId == other.recipientId;
    }
    
private:
    MessageHeader header;              // Header de base (TYPE + NONCE)
    std::vector<uint8_t> senderId;     // SENDER_ID (16 bytes)
    std::vector<uint8_t> recipientId;   // RECIPIENT_ID (16 bytes)
};

