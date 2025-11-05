#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Payload pour les messages de succès de négociation de challenge
 */
struct AuthChallengeNegociationSuccessPayload {
    std::string sessionId;
    std::string challengeId;
    
    AuthChallengeNegociationSuccessPayload(const std::string& sessionId, const std::string& challengeId) 
        : sessionId(sessionId), challengeId(challengeId) {}

    bool operator==(const AuthChallengeNegociationSuccessPayload& other) const {
        return sessionId == other.sessionId && challengeId == other.challengeId;
    }
};

/**
 * @brief Message de succès de négociation de challenge d'authentification
 */
class AuthChallengeNegociationMessageSucceded : public Message<AuthChallengeNegociationSuccessPayload> {
public:
    AuthChallengeNegociationMessageSucceded(const AuthChallengeNegociationSuccessPayload& payload, const MessageHeader& header);
    
    // Méthode factory pour créer le message simplement
    static AuthChallengeNegociationMessageSucceded create(const std::string& sessionId, const std::string& challengeId, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const override;  // Temporaire, à remplacer par encoder
    
    bool operator==(const AuthChallengeNegociationMessageSucceded& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
