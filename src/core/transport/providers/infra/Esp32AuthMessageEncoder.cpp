#include "Esp32AuthMessageEncoder.h"
#include "core/transport/model/AuthRequestMessage.h"

Esp32AuthMessageEncoder::Esp32AuthMessageEncoder() {
}

std::vector<uint8_t> Esp32AuthMessageEncoder::encode(const AuthRequestMessage& message) const {
    // 1. Encoder le header (type + nonce)
    std::vector<uint8_t> encoded = headerEncoder.encodeHeader(message.header);
    
    // 2. Ajouter le payload (challengeId)
    std::string challengeId = message.getChallengeId();
    encoded.insert(encoded.end(), challengeId.begin(), challengeId.end());
    
    return encoded;
}
