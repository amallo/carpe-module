#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Payload pour les messages d'initiation de challenge d'authentification
 */
struct InitiateAuthChallengePayload {
    std::string challengeId;
    
    InitiateAuthChallengePayload(const std::string& challengeId) 
        : challengeId(challengeId) {}

    bool operator==(const InitiateAuthChallengePayload& other) const {
        return challengeId == other.challengeId;
    }
};

/**
 * @brief Message d'initiation de challenge d'authentification
 */
class InitiateAuthChallengeMessage : public Message<InitiateAuthChallengePayload> {
public:
    InitiateAuthChallengeMessage(const InitiateAuthChallengePayload& payload, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const override;
    
    MessageInterface* clone() const override;
};
