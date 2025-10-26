#include "AuthChallengeNegociationMessageSucceded.h"

AuthChallengeNegociationMessageSucceded::AuthChallengeNegociationMessageSucceded(const std::string& challengeId, MessageEncoder& encoder, uint16_t nonce)
    : Message<AuthChallengeNegociationSuccessPayload>("auth_negotiation_success", nonce, AuthChallengeNegociationSuccessPayload(challengeId)), encoder(encoder) {
}

const std::string& AuthChallengeNegociationMessageSucceded::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSucceded::encode() const {
    // Le modèle dépend entièrement de l'encoder injecté
    return encoder.encode(*this);
}

bool AuthChallengeNegociationMessageSucceded::operator==(const AuthChallengeNegociationMessageSucceded& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
