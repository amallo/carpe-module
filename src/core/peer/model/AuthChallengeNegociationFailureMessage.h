#pragma once
#include "Message.h"
#include "core/peer/encoders/MessageEncoder.h"
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Payload pour les messages d'échec de négociation de challenge
 */
struct AuthChallengeNegociationFailurePayload {
    std::string challengeId;
    std::string reason;
    int remainingAttempts;
    
    AuthChallengeNegociationFailurePayload(const std::string& challengeId, const std::string& reason, int remainingAttempts) 
        : challengeId(challengeId), reason(reason), remainingAttempts(remainingAttempts) {}
};

/**
 * @brief Message d'échec de négociation de challenge d'authentification
 */
class AuthChallengeNegociationFailureMessage : public Message<AuthChallengeNegociationFailurePayload> {
public:
    AuthChallengeNegociationFailureMessage(const AuthChallengeNegociationFailurePayload& payload, MessageEncoder& encoder, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    const std::string& getReason() const;
    std::vector<uint8_t> encode() const override;
    
    bool operator==(const AuthChallengeNegociationFailureMessage& other) const;
    
private:
    MessageEncoder& encoder;
};
