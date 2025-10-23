#include "InitiateAuthChallengeMessage.h"
#include "core/transport/AuthMessageEncoder.h"
#include <stdexcept>

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(const std::string& challengeId, uint16_t nonce) 
    : Message("auth_request", nonce),
      challengeId(challengeId), encoder(nullptr) {
}

InitiateAuthChallengeMessage::InitiateAuthChallengeMessage(const std::string& challengeId, uint16_t nonce, AuthMessageEncoder& encoder) 
    : Message("auth_request", nonce),
      challengeId(challengeId), encoder(&encoder) {
}

const std::string& InitiateAuthChallengeMessage::getChallengeId() const {
    return challengeId;
}

std::vector<uint8_t> InitiateAuthChallengeMessage::encode() const {
    if (encoder == nullptr) {
        throw std::runtime_error("No encoder provided for InitiateAuthChallengeMessage");
    }
    return encoder->encode(*this);
}

bool InitiateAuthChallengeMessage::operator==(const InitiateAuthChallengeMessage& other) const {
    return challengeId == other.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}
