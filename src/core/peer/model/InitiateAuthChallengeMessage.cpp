#include "InitiateAuthChallengeMessage.h"

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(const InitiateAuthChallengePayload& payload, uint16_t nonce)
    : Message<InitiateAuthChallengePayload>("auth_request", nonce, payload) {
}

const std::string& InitiateAuthChallengeMessage::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> InitiateAuthChallengeMessage::encode() const {
    // Encodage simple sans dépendance externe
    std::vector<uint8_t> data;
    
    // Encoder le type
    const std::string& type = getType();
    if (!type.empty()) {
        data.push_back(static_cast<uint8_t>(type[0]));
    }
    
    // Encoder le nonce
    uint16_t nonce = getNonce();
    data.push_back((nonce >> 8) & 0xFF);
    data.push_back(nonce & 0xFF);
    
    // Encoder le challengeId
    for (char c : payload.challengeId) {
        data.push_back(static_cast<uint8_t>(c));
    }
    
    return data;
}

MessageInterface* InitiateAuthChallengeMessage::clone() const {
    return new InitiateAuthChallengeMessage(payload, getNonce());
}
