#include "AuthChallengeNegociationFailureMessage.h"

AuthChallengeNegociationFailureMessage::AuthChallengeNegociationFailureMessage(const AuthChallengeNegociationFailurePayload& payload, MessageEncoder& encoder, uint16_t nonce)
    : Message<AuthChallengeNegociationFailurePayload>("auth_negotiation_failure", nonce, payload), encoder(encoder) {
}

const std::string& AuthChallengeNegociationFailureMessage::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationFailureMessage::getReason() const {
    return payload.reason;
}

std::vector<uint8_t> AuthChallengeNegociationFailureMessage::encode() const {
    // Le modèle dépend entièrement de l'encoder injecté
    return encoder.encode(*this);
}

bool AuthChallengeNegociationFailureMessage::operator==(const AuthChallengeNegociationFailureMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           payload.reason == other.payload.reason &&
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
