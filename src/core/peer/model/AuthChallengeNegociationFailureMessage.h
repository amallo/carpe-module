#pragma once
#include "Message.h"
#include "core/peer/model/MessageHeader.h"
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

    bool operator==(const AuthChallengeNegociationFailurePayload& other) const {
        return challengeId == other.challengeId && reason == other.reason && remainingAttempts == other.remainingAttempts;
    }
};

// Forward declaration
class AuthChallengeNegociationFailureMessage;

/**
 * @brief Encoder pour AuthChallengeNegociationFailureMessage (défini dans le .cpp)
 */
class AuthChallengeNegociationFailureMessageEncoder : public MessageEncoder {
public:
    std::vector<uint8_t> encode(const MessageInterface& message) const override;
    
private:
    std::vector<uint8_t> encodePayload(const AuthChallengeNegociationFailureMessage& msg) const;
};

/**
 * @brief Message d'échec de négociation de challenge d'authentification
 */
class AuthChallengeNegociationFailureMessage : public Message<AuthChallengeNegociationFailurePayload> {
    AuthChallengeNegociationFailureMessageEncoder* encoder;
    
public:
    AuthChallengeNegociationFailureMessage(
        const AuthChallengeNegociationFailurePayload& payload,
        const MessageHeader& header,
        AuthChallengeNegociationFailureMessageEncoder* encoder
    );
    
    // Méthode factory pour créer le message simplement
    static AuthChallengeNegociationFailureMessage create(const std::string& challengeId, const std::string& reason, int remainingAttempts, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    const std::string& getReason() const;
    int getRemainingAttempts() const;
    std::vector<uint8_t> encode() const override;
    
    bool operator==(const AuthChallengeNegociationFailureMessage& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
