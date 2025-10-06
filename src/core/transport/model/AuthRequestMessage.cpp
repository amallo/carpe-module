#include "AuthRequestMessage.h"
#include <vector>
#include <cstring>

AuthRequestMessage::AuthRequestMessage(const std::string& challengeId, uint16_t nonce) 
    : Message("auth_request", nonce, std::vector<uint8_t>(challengeId.begin(), challengeId.end())),
      challengeId(challengeId) {
}

const std::string& AuthRequestMessage::getChallengeId() const {
    return challengeId;
}

bool AuthRequestMessage::operator==(const AuthRequestMessage& other) const {
    return challengeId == other.challengeId && 
           type == other.type && 
           nonce == other.nonce;
}
