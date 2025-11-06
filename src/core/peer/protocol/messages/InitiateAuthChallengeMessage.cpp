#include "InitiateAuthChallengeMessage.h"
#include <algorithm>

// Implémentation de l'encoder dans le même fichier .cpp
std::vector<uint8_t> InitiateAuthChallengeMessageEncoder::encode(const MessageInterface& message) const {
    const InitiateAuthChallengeMessage& msg = 
        static_cast<const InitiateAuthChallengeMessage&>(message);
    
    // Encoder header (TYPE 0x04 + NONCE)
    auto data = encodeHeader(msg.getHeader());
    
    // Encoder payload (16 bytes challengeId)
    auto payload = encodePayload(msg);
    data.insert(data.end(), payload.begin(), payload.end());
    
    return data;
}

std::vector<uint8_t> InitiateAuthChallengeMessageEncoder::encodePayload(const InitiateAuthChallengeMessage& msg) const {
    // Encoder le challengeId avec taille fixe de 16 bytes (null-padded)
    std::vector<uint8_t> payload(16, 0);  // Initialisé à 0
    const std::string& challengeId = msg.getChallengeId();
    size_t copyLength = std::min(challengeId.size(), size_t(16));
    std::copy(challengeId.begin(), challengeId.begin() + copyLength, payload.begin());
    return payload;
}

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(
    const InitiateAuthChallengePayload& payload,
    const MessageHeader& header,
    InitiateAuthChallengeMessageEncoder* encoder
) : Message<InitiateAuthChallengePayload>(header, payload),
    encoder(encoder) {
}

const std::string& InitiateAuthChallengeMessage::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> InitiateAuthChallengeMessage::encode() const {
    return encoder->encode(*this);
}

MessageInterface* InitiateAuthChallengeMessage::clone() const {
    // Clone le message mais partage le même encoder
    return new InitiateAuthChallengeMessage(payload, header, encoder);
}

bool InitiateAuthChallengeMessage::operator==(const InitiateAuthChallengeMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}

bool InitiateAuthChallengeMessage::operator==(const MessageInterface& other) const {
    if (getType() != other.getType()) {
        return false;
    }
    const InitiateAuthChallengeMessage* otherMsg = static_cast<const InitiateAuthChallengeMessage*>(&other);
    return *this == *otherMsg;
}
