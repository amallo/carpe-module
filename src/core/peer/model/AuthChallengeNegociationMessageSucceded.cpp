#include "AuthChallengeNegociationMessageSucceded.h"

AuthChallengeNegociationMessageSucceded::AuthChallengeNegociationMessageSucceded(const std::string& challengeId, uint16_t nonce)
    : Message<AuthChallengeNegociationSuccessPayload>("auth_negotiation_success", nonce, AuthChallengeNegociationSuccessPayload(challengeId)) {
}

const std::string& AuthChallengeNegociationMessageSucceded::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSucceded::encode() const {
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

bool AuthChallengeNegociationMessageSucceded::operator==(const AuthChallengeNegociationMessageSucceded& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
