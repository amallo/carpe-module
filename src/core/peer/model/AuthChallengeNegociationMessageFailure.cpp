#include "AuthChallengeNegociationMessageFailure.h"

AuthChallengeNegociationMessageFailure::AuthChallengeNegociationMessageFailure(const AuthChallengeNegociationFailurePayload& payload, MessageEncoder& encoder, uint16_t nonce)
    : Message<AuthChallengeNegociationFailurePayload>("auth_negotiation_failure", nonce, payload), encoder(encoder) {
}

const std::string& AuthChallengeNegociationMessageFailure::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationMessageFailure::getReason() const {
    return payload.reason;
}

std::vector<uint8_t> AuthChallengeNegociationMessageFailure::encode() const {
    // Le modèle dépend entièrement de l'encoder injecté
    return encoder.encode(*this);
}

bool AuthChallengeNegociationMessageFailure::operator==(const AuthChallengeNegociationMessageFailure& other) const {
    return payload.challengeId == other.payload.challengeId && 
           payload.reason == other.payload.reason &&
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
