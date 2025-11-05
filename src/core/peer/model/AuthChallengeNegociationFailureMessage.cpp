#include "AuthChallengeNegociationFailureMessage.h"
#include "core/peer/model/MessageHeader.h"

AuthChallengeNegociationFailureMessage::AuthChallengeNegociationFailureMessage(const AuthChallengeNegociationFailurePayload& payload, const MessageHeader& header)
    : Message<AuthChallengeNegociationFailurePayload>(header, payload) {
}

AuthChallengeNegociationFailureMessage AuthChallengeNegociationFailureMessage::create(const std::string& challengeId, const std::string& reason, int remainingAttempts, uint16_t nonce) {
    AuthChallengeNegociationFailurePayload payload(challengeId, reason, remainingAttempts);
    MessageHeader header(0x00, nonce);  // TYPE temporaire, à définir dans le protocole
    return AuthChallengeNegociationFailureMessage(payload, header);
}

const std::string& AuthChallengeNegociationFailureMessage::getChallengeId() const {
    return payload.challengeId;
}

const std::string& AuthChallengeNegociationFailureMessage::getReason() const {
    return payload.reason;
}

std::vector<uint8_t> AuthChallengeNegociationFailureMessage::encode() const {
    // TODO: Implémenter avec encoder
    std::vector<uint8_t> data;
    data.push_back(header.getType());
    data.push_back((header.getNonce() >> 8) & 0xFF);
    data.push_back(header.getNonce() & 0xFF);
    // Encoder payload temporaire
    for (char c : payload.challengeId) {
        data.push_back(static_cast<uint8_t>(c));
    }
    for (char c : payload.reason) {
        data.push_back(static_cast<uint8_t>(c));
    }
    data.push_back(static_cast<uint8_t>(payload.remainingAttempts));
    return data;
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
    return new AuthChallengeNegociationFailureMessage(payload, header);
}
