#include "MessageDecoder.h"
#include "core/peer/protocol/MessageHeader.h"
#include "core/peer/protocol/MessageTypes.h"
#include <vector>
#include <cstdint>

/**
 * @brief Message minimal pour le décodage (header seulement)
 */
struct EmptyPayload {};

class DecodedMessage : public Message<EmptyPayload> {
    size_t payloadSize;
    
public:
    DecodedMessage(const MessageHeader& header, size_t payloadSize) 
        : Message<EmptyPayload>(header, EmptyPayload()), payloadSize(payloadSize) {}
    
    size_t getPayloadSize() const override {
        return payloadSize;
    }
    
    std::vector<uint8_t> encode() const override {
        return header.encode();
    }
    
    MessageInterface* clone() const override {
        return new DecodedMessage(header, payloadSize);
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
    
    // Valider le type
    if (!MessageType::isValid(type)) {
        return nullptr;
    }
    
    // Déterminer la taille du header selon le type
    size_t headerSize = 3;  // Header standard: TYPE (1) + NONCE (2)
    if (type == MessageType::USER_MESSAGE) {
        headerSize = 19;  // Header USER_MESSAGE: TYPE (1) + NONCE (2) + RECIPIENT_ID (16)
    }
    
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
    
    // Créer un message minimal avec le header et la taille du payload
    return new DecodedMessage(header, payloadSize);
}

