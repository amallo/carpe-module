#include "AuthChallengeNegociationFailureMessage.h"

AuthChallengeNegociationFailureMessage::AuthChallengeNegociationFailureMessage(const AuthChallengeNegociationFailurePayload& payload, uint16_t nonce)
    : Message<AuthChallengeNegociationFailurePayload>("auth_negotiation_failure", nonce, payload) {
}

AuthChallengeNegociationFailureMessage AuthChallengeNegociationFailureMessage::create(const std::string& challengeId, const std::string& reason, int remainingAttempts, uint16_t nonce) {
    AuthChallengeNegociationFailurePayload payload(challengeId, reason, remainingAttempts);
    return AuthChallengeNegociationFailureMessage(payload, nonce);
}

const std::string& AuthChallengeNegociationFailureMessage::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationFailureMessage::getReason() const {
    return payload.reason;
}

std::vector<uint8_t> AuthChallengeNegociationFailureMessage::encode() const {
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
    
    // Encoder le reason
    for (char c : payload.reason) {
        data.push_back(static_cast<uint8_t>(c));
    }
    
    // Encoder le remainingAttempts
    data.push_back(static_cast<uint8_t>(payload.remainingAttempts));
    
    return data;
}

bool AuthChallengeNegociationFailureMessage::operator==(const AuthChallengeNegociationFailureMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           payload.reason == other.payload.reason &&
           payload.remainingAttempts == other.payload.remainingAttempts &&
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}

bool AuthChallengeNegociationFailureMessage::operator==(const MessageInterface& other) const {
    // Vérifier le type sans RTTI (getType() retourne "auth_negotiation_failure")
    if (getType() != other.getType()) {
        return false;
    }
    // Type vérifié, on peut utiliser static_cast en toute sécurité
    const AuthChallengeNegociationFailureMessage* otherMsg = static_cast<const AuthChallengeNegociationFailureMessage*>(&other);
    return *this == *otherMsg;
}

MessageInterface* AuthChallengeNegociationFailureMessage::clone() const {
    return new AuthChallengeNegociationFailureMessage(payload, getNonce());
}
