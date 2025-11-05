#include "AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/model/MessageHeader.h"

AuthChallengeNegociationMessageSucceded::AuthChallengeNegociationMessageSucceded(const AuthChallengeNegociationSuccessPayload& payload, const MessageHeader& header)
    : Message<AuthChallengeNegociationSuccessPayload>(header, payload) {
}

AuthChallengeNegociationMessageSucceded AuthChallengeNegociationMessageSucceded::create(const std::string& sessionId, const std::string& challengeId, uint16_t nonce) {
    AuthChallengeNegociationSuccessPayload payload(sessionId, challengeId);
    MessageHeader header(0x00, nonce);  // TYPE temporaire, à définir dans le protocole
    return AuthChallengeNegociationMessageSucceded(payload, header);
}

const std::string& AuthChallengeNegociationMessageSucceded::getChallengeId() const {
    return payload.challengeId;
}

std::vector<uint8_t> AuthChallengeNegociationMessageSucceded::encode() const {
    // TODO: Implémenter avec encoder
    std::vector<uint8_t> data;
    data.push_back(header.getType());
    data.push_back((header.getNonce() >> 8) & 0xFF);
    data.push_back(header.getNonce() & 0xFF);
    // Encoder payload temporaire
    for (char c : payload.challengeId) {
        data.push_back(static_cast<uint8_t>(c));
    }
    return data;
}

bool AuthChallengeNegociationMessageSucceded::operator==(const AuthChallengeNegociationMessageSucceded& other) const {
    return payload.challengeId == other.payload.challengeId && 
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
    return new AuthChallengeNegociationMessageSucceded(payload, header);
}
