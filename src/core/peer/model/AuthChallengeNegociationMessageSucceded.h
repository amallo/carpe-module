#pragma once
#include "Message.h"
#include "core/peer/model/MessageHeader.h"
#include "core/peer/encoders/MessageEncoder.h"
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

// Forward declaration
class AuthChallengeNegociationMessageSucceded;

/**
 * @brief Encoder pour AuthChallengeNegociationMessageSucceded (défini dans le .cpp)
 */
class AuthChallengeNegociationMessageSuccededEncoder : public MessageEncoder {
public:
    std::vector<uint8_t> encode(const MessageInterface& message) const override;
    
private:
    std::vector<uint8_t> encodePayload(const AuthChallengeNegociationMessageSucceded& msg) const;
};

/**
 * @brief Message de succès de négociation de challenge d'authentification
 */
class AuthChallengeNegociationMessageSucceded : public Message<AuthChallengeNegociationSuccessPayload> {
    AuthChallengeNegociationMessageSuccededEncoder* encoder;
    
public:
    AuthChallengeNegociationMessageSucceded(
        const AuthChallengeNegociationSuccessPayload& payload,
        const MessageHeader& header,
        AuthChallengeNegociationMessageSuccededEncoder* encoder
    );
    
    // Méthode factory pour créer le message simplement
    static AuthChallengeNegociationMessageSucceded create(const std::string& sessionId, const std::string& challengeId, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    const std::string& getSessionId() const;
    std::vector<uint8_t> encode() const override;
    
    bool operator==(const AuthChallengeNegociationMessageSucceded& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
