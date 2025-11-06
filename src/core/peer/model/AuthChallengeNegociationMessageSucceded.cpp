#include "AuthChallengeNegociationMessageSucceded.h"
#include <algorithm>

// Implémentation de l'encoder dans le même fichier .cpp
std::vector<uint8_t> AuthChallengeNegociationMessageSuccededEncoder::encode(const MessageInterface& message) const {
    const AuthChallengeNegociationMessageSucceded& msg = 
        static_cast<const AuthChallengeNegociationMessageSucceded&>(message);
    
    // Encoder header (TYPE 0x05 + NONCE)
    auto data = encodeHeader(msg.getHeader());
    
    // Encoder payload (32 bytes: sessionId 16 bytes + challengeId 16 bytes)
    auto payload = encodePayload(msg);
    data.insert(data.end(), payload.begin(), payload.end());
    
    return data;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSuccededEncoder::encodePayload(const AuthChallengeNegociationMessageSucceded& msg) const {
    std::vector<uint8_t> payload;
    
    // Encoder sessionId (16 bytes fixe, null-padded)
    std::vector<uint8_t> sessionId(16, 0);
    const std::string& sessionIdStr = msg.getSessionId();
    size_t copyLength = std::min(sessionIdStr.size(), size_t(16));
    std::copy(sessionIdStr.begin(), sessionIdStr.begin() + copyLength, sessionId.begin());
    payload.insert(payload.end(), sessionId.begin(), sessionId.end());
    
    // Encoder challengeId (16 bytes fixe, null-padded)
    std::vector<uint8_t> challengeId(16, 0);
    const std::string& challengeIdStr = msg.getChallengeId();
    copyLength = std::min(challengeIdStr.size(), size_t(16));
    std::copy(challengeIdStr.begin(), challengeIdStr.begin() + copyLength, challengeId.begin());
    payload.insert(payload.end(), challengeId.begin(), challengeId.end());
    
    return payload;  // Total: 32 bytes
}

AuthChallengeNegociationMessageSucceded::AuthChallengeNegociationMessageSucceded(
    const AuthChallengeNegociationSuccessPayload& payload,
    const MessageHeader& header,
    AuthChallengeNegociationMessageSuccededEncoder* encoder
) : Message<AuthChallengeNegociationSuccessPayload>(header, payload),
    encoder(encoder) {
}

AuthChallengeNegociationMessageSucceded AuthChallengeNegociationMessageSucceded::create(const std::string& sessionId, const std::string& challengeId, uint16_t nonce) {
    AuthChallengeNegociationSuccessPayload payload(sessionId, challengeId);
    MessageHeader header(0x05, nonce);  // TYPE 0x05 selon protocol.md
    AuthChallengeNegociationMessageSuccededEncoder encoder;
    return AuthChallengeNegociationMessageSucceded(payload, header, &encoder);
}

const std::string& AuthChallengeNegociationMessageSucceded::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationMessageSucceded::getSessionId() const {
    return payload.sessionId;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSucceded::encode() const {
    return encoder->encode(*this);
}

bool AuthChallengeNegociationMessageSucceded::operator==(const AuthChallengeNegociationMessageSucceded& other) const {
    return payload.sessionId == other.payload.sessionId &&
           payload.challengeId == other.payload.challengeId && 
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}

bool AuthChallengeNegociationMessageSucceded::operator==(const MessageInterface& other) const {
    if (getType() != other.getType()) {
        return false;
    }
    const AuthChallengeNegociationMessageSucceded* otherMsg = static_cast<const AuthChallengeNegociationMessageSucceded*>(&other);
    return *this == *otherMsg;
}

MessageInterface* AuthChallengeNegociationMessageSucceded::clone() const {
    // Clone le message mais partage le même encoder
    return new AuthChallengeNegociationMessageSucceded(payload, header, encoder);
}
