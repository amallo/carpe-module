#pragma once
#include "Message.h"
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

/**
 * @brief Message d'échec de négociation de challenge d'authentification
 */
class AuthChallengeNegociationFailureMessage : public Message<AuthChallengeNegociationFailurePayload> {
public:
    AuthChallengeNegociationFailureMessage(const AuthChallengeNegociationFailurePayload& payload, const MessageHeader& header);
    
    // Méthode factory pour créer le message simplement
    static AuthChallengeNegociationFailureMessage create(const std::string& challengeId, const std::string& reason, int remainingAttempts, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    const std::string& getReason() const;
    std::vector<uint8_t> encode() const override;  // Temporaire, à remplacer par encoder
    
    bool operator==(const AuthChallengeNegociationFailureMessage& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
