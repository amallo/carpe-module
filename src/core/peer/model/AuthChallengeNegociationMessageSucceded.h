#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Payload pour les messages de succès de négociation de challenge
 */
struct AuthChallengeNegociationSuccessPayload {
    std::string challengeId;
    
    AuthChallengeNegociationSuccessPayload(const std::string& challengeId) 
        : challengeId(challengeId) {}

    bool operator==(const AuthChallengeNegociationSuccessPayload& other) const {
        return challengeId == other.challengeId;
    }
};

/**
 * @brief Message de succès de négociation de challenge d'authentification
 */
class AuthChallengeNegociationMessageSucceded : public Message<AuthChallengeNegociationSuccessPayload> {
public:
    AuthChallengeNegociationMessageSucceded(const AuthChallengeNegociationSuccessPayload& payload, uint16_t nonce = 0);
    
    // Méthode factory pour créer le message simplement
    static AuthChallengeNegociationMessageSucceded create(const std::string& challengeId, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const override;
    
    bool operator==(const AuthChallengeNegociationMessageSucceded& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
