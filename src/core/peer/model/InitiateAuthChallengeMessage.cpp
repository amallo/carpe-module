#include "InitiateAuthChallengeMessage.h"

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(const InitiateAuthChallengePayload& payload, MessageEncoder& encoder, uint16_t nonce)
    : Message<InitiateAuthChallengePayload>("auth_request", nonce, payload), encoder(encoder) {
}

const std::string& InitiateAuthChallengeMessage::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> InitiateAuthChallengeMessage::encode() const {
    // Le modèle dépend entièrement de l'encoder injecté
    return encoder.encode(*this);
}

bool InitiateAuthChallengeMessage::operator==(const InitiateAuthChallengeMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
