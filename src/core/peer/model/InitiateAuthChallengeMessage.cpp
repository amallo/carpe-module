#include "InitiateAuthChallengeMessage.h"

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(const std::string& challengeId, uint16_t nonce)
    : Message<InitiateAuthChallengePayload>("auth_request", nonce, InitiateAuthChallengePayload(challengeId)) {
}

const std::string& InitiateAuthChallengeMessage::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> InitiateAuthChallengeMessage::encode() const {
    std::vector<uint8_t> data;
    
    // Encoder le header
    data.insert(data.end(), header.type.begin(), header.type.end());
    data.push_back((header.nonce >> 8) & 0xFF);
    data.push_back(header.nonce & 0xFF);
    
    // Encoder le challengeId
    const std::string& challengeId = payload.challengeId;
    data.insert(data.end(), challengeId.begin(), challengeId.end());
    
    return data;
}

bool InitiateAuthChallengeMessage::operator==(const InitiateAuthChallengeMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
