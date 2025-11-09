#include "MessageDecoder.h"
#include "core/peer/protocol/MessageHeader.h"
#include "core/peer/protocol/UserMessageHeader.h"
#include "core/peer/protocol/MessageTypes.h"
#include <vector>
#include <cstdint>
#include <memory>

/**
 * @brief Message minimal pour le décodage (header seulement)
 */
struct EmptyPayload {};

/**
 * @brief Message décodé pour USER_MESSAGE (avec SENDER_ID et RECIPIENT_ID)
 */
class DecodedUserMessage : public Message<EmptyPayload> {
    size_t payloadSize;
    UserMessageHeader userMessageHeader;
    
public:
    DecodedUserMessage(const UserMessageHeader& userHeader, size_t payloadSize)
        : Message<EmptyPayload>(userHeader.getHeader(), EmptyPayload()), 
          payloadSize(payloadSize),
          userMessageHeader(userHeader) {}
    
    size_t getPayloadSize() const override {
        return payloadSize;
    }
    
    std::vector<uint8_t> getSenderId() const override {
        return userMessageHeader.getSenderId();
    }
    
    std::vector<uint8_t> getRecipientId() const override {
        return userMessageHeader.getRecipientId();
    }
    
    const UserMessageHeader& getUserMessageHeader() const {
        return userMessageHeader;
    }
    
    std::vector<uint8_t> encode() const override {
        return userMessageHeader.encode();
    }
    
    MessageInterface* clone() const override {
        return new DecodedUserMessage(userMessageHeader, payloadSize);
    }
    
    bool operator==(const MessageInterface& other) const override {
        return getType() == other.getType() && getNonce() == other.getNonce();
    }
};

MessageInterface* MessageDecoder::decode(const std::vector<uint8_t>& data) const {
    // Vérifier la taille minimale (3 bytes pour le header standard)
    if (data.size() < 3) {
        return nullptr;
    }
    
    // Décoder le type
    uint8_t type = data[0];
    
    // Ne décoder que USER_MESSAGE, rejeter tous les autres types
    if (type != MessageType::USER_MESSAGE) {
        return nullptr;
    }
    
    // Header USER_MESSAGE: TYPE (1) + NONCE (2) + SENDER_ID (16) + RECIPIENT_ID (16) = 35 bytes
    size_t headerSize = 35;
    
    // Vérifier que les données sont suffisamment longues pour le header
    if (data.size() < headerSize) {
        return nullptr;
    }
    
    // Décoder le NONCE (toujours aux positions 1-2)
    uint16_t nonce = (static_cast<uint16_t>(data[1]) << 8) | data[2];  // Big-endian
    
    // Créer le header
    MessageHeader header(type, nonce);
    
    // Calculer la taille du payload (données totales - taille du header)
    size_t payloadSize = data.size() - headerSize;
    
    // Valider la taille du payload : doit être exactement 144 bytes (16 SESSION_ID + 128 CONTENT)
    constexpr size_t expectedPayloadSize = 144;
    if (payloadSize != expectedPayloadSize) {
        return nullptr;
    }
    
    // Extraire SENDER_ID et RECIPIENT_ID
    // SENDER_ID: positions 3-18 (16 bytes)
    std::vector<uint8_t> senderId(data.begin() + 3, data.begin() + 19);
    // RECIPIENT_ID: positions 19-34 (16 bytes)
    std::vector<uint8_t> recipientId(data.begin() + 19, data.begin() + 35);
    
    UserMessageHeader userHeader(senderId, recipientId, header);
    return new DecodedUserMessage(userHeader, payloadSize);
}

