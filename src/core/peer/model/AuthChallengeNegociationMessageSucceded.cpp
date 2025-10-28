#include "AuthChallengeNegociationMessageSucceded.h"

AuthChallengeNegociationMessageSucceded::AuthChallengeNegociationMessageSucceded(const AuthChallengeNegociationSuccessPayload& payload, uint16_t nonce)
    : Message<AuthChallengeNegociationSuccessPayload>("auth_negotiation_success", nonce, payload) {
}

AuthChallengeNegociationMessageSucceded AuthChallengeNegociationMessageSucceded::create(const std::string& sessionId, const std::string& challengeId, uint16_t nonce) {
    AuthChallengeNegociationSuccessPayload payload(sessionId, challengeId);
    return AuthChallengeNegociationMessageSucceded(payload, nonce);
}

const std::string& AuthChallengeNegociationMessageSucceded::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSucceded::encode() const {
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

bool AuthChallengeNegociationMessageSucceded::operator==(const AuthChallengeNegociationMessageSucceded& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}

bool AuthChallengeNegociationMessageSucceded::operator==(const MessageInterface& other) const {
    const AuthChallengeNegociationMessageSucceded* otherMsg = dynamic_cast<const AuthChallengeNegociationMessageSucceded*>(&other);
    return otherMsg && *this == *otherMsg;
}

MessageInterface* AuthChallengeNegociationMessageSucceded::clone() const {
    return new AuthChallengeNegociationMessageSucceded(payload, getNonce());
}
