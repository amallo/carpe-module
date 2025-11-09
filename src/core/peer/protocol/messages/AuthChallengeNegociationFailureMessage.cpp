#include "AuthChallengeNegociationFailureMessage.h"
#include "core/peer/protocol/MessageTypes.h"
#include <algorithm>

// Implémentation de l'encoder dans le même fichier .cpp
std::vector<uint8_t> AuthChallengeNegociationFailureMessageEncoder::encode(const MessageInterface& message) const {
    const AuthChallengeNegociationFailureMessage& msg = 
        static_cast<const AuthChallengeNegociationFailureMessage&>(message);
    
    // Encoder header (TYPE AUTH_CHALLENGE_NEGOTIATION_FAILURE + NONCE)
    auto data = encodeHeader(msg.getHeader());
    
    // Encoder payload (49 bytes: challengeId 16 bytes + reason 32 bytes + remainingAttempts 1 byte)
    auto payload = encodePayload(msg);
    data.insert(data.end(), payload.begin(), payload.end());
    
    return data;
}

std::vector<uint8_t> AuthChallengeNegociationFailureMessageEncoder::encodePayload(const AuthChallengeNegociationFailureMessage& msg) const {
    std::vector<uint8_t> payload;
    
    // Encoder challengeId (16 bytes fixe, null-padded)
    std::vector<uint8_t> challengeId(16, 0);
    const std::string& challengeIdStr = msg.getChallengeId();
    size_t copyLength = std::min(challengeIdStr.size(), size_t(16));
    std::copy(challengeIdStr.begin(), challengeIdStr.begin() + copyLength, challengeId.begin());
    payload.insert(payload.end(), challengeId.begin(), challengeId.end());
    
    // Encoder reason (32 bytes fixe, null-padded)
    std::vector<uint8_t> reason(32, 0);
    const std::string& reasonStr = msg.getReason();
    copyLength = std::min(reasonStr.size(), size_t(32));
    std::copy(reasonStr.begin(), reasonStr.begin() + copyLength, reason.begin());
    payload.insert(payload.end(), reason.begin(), reason.end());
    
    // Encoder remainingAttempts (1 byte)
    // Convert -1 to 255 (0xFF) for challenge ended, otherwise clamp to 0-255
    int attempts = msg.getRemainingAttempts();
    uint8_t attemptsByte = (attempts < 0) ? 0xFF : static_cast<uint8_t>(std::min(attempts, 255));
    payload.push_back(attemptsByte);
    
    return payload;  // Total: 49 bytes
}

AuthChallengeNegociationFailureMessage::AuthChallengeNegociationFailureMessage(
    const AuthChallengeNegociationFailurePayload& payload,
    const MessageHeader& header,
    AuthChallengeNegociationFailureMessageEncoder* encoder
) : Message<AuthChallengeNegociationFailurePayload>(header, payload),
    encoder(encoder) {
}

AuthChallengeNegociationFailureMessage AuthChallengeNegociationFailureMessage::create(const std::string& challengeId, const std::string& reason, int remainingAttempts, uint16_t nonce) {
    AuthChallengeNegociationFailurePayload payload(challengeId, reason, remainingAttempts);
    MessageHeader header(MessageType::AUTH_CHALLENGE_NEGOTIATION_FAILURE, nonce);
    AuthChallengeNegociationFailureMessageEncoder encoder;
    return AuthChallengeNegociationFailureMessage(payload, header, &encoder);
}

const std::string& AuthChallengeNegociationFailureMessage::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationFailureMessage::getReason() const {
    return payload.reason;
}

int AuthChallengeNegociationFailureMessage::getRemainingAttempts() const {
    return payload.remainingAttempts;
}

std::vector<uint8_t> AuthChallengeNegociationFailureMessage::encode() const {
    return encoder->encode(*this);
}

bool AuthChallengeNegociationFailureMessage::operator==(const AuthChallengeNegociationFailureMessage& other) const {
    return payload.challengeId == other.payload.challengeId && 
           payload.reason == other.payload.reason &&
           payload.remainingAttempts == other.payload.remainingAttempts &&
           getType() == other.getType() && 
           getNonce() == other.getNonce();
}

bool AuthChallengeNegociationFailureMessage::operator==(const MessageInterface& other) const {
    if (getType() != other.getType()) {
        return false;
    }
    const AuthChallengeNegociationFailureMessage* otherMsg = static_cast<const AuthChallengeNegociationFailureMessage*>(&other);
    return *this == *otherMsg;
}

MessageInterface* AuthChallengeNegociationFailureMessage::clone() const {
    // Clone le message mais partage le même encoder
    return new AuthChallengeNegociationFailureMessage(payload, header, encoder);
}
