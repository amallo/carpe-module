#include "AuthRequestMessage.h"
#include "../AuthMessageEncoder.h"
#include <stdexcept>

AuthRequestMessage::AuthRequestMessage(const std::string& challengeId, uint16_t nonce) 
    : Message("auth_request", nonce),
      challengeId(challengeId), encoder(nullptr) {
}

AuthRequestMessage::AuthRequestMessage(const std::string& challengeId, uint16_t nonce, AuthMessageEncoder& encoder) 
    : Message("auth_request", nonce),
      challengeId(challengeId), encoder(&encoder) {
}

const std::string& AuthRequestMessage::getChallengeId() const {
    return challengeId;
}

std::vector<uint8_t> AuthRequestMessage::encode() const {
    if (encoder == nullptr) {
        throw std::runtime_error("No encoder provided for AuthRequestMessage");
    }
    return encoder->encode(*this);
}

bool AuthRequestMessage::operator==(const AuthRequestMessage& other) const {
    return challengeId == other.challengeId && 
           type == other.type && 
           nonce == other.nonce;
}
