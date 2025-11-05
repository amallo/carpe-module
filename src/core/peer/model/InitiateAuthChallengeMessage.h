#pragma once
#include "Message.h"
#include "core/peer/model/MessageHeader.h"
#include "core/peer/encoders/MessageEncoder.h"
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

// Forward declaration
class InitiateAuthChallengeMessage;

/**
 * @brief Encoder pour InitiateAuthChallengeMessage (défini dans le .cpp)
 */
class InitiateAuthChallengeMessageEncoder : public MessageEncoder {
public:
    std::vector<uint8_t> encode(const MessageInterface& message) const override;
    
private:
    std::vector<uint8_t> encodePayload(const InitiateAuthChallengeMessage& msg) const;
};

/**
 * @brief Message d'initiation de challenge d'authentification
 */
class InitiateAuthChallengeMessage : public Message<InitiateAuthChallengePayload> {
    InitiateAuthChallengeMessageEncoder* encoder;
    
public:
    InitiateAuthChallengeMessage(
        const InitiateAuthChallengePayload& payload,
        const MessageHeader& header,
        InitiateAuthChallengeMessageEncoder* encoder
    );
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const override;
    
    bool operator==(const InitiateAuthChallengeMessage& other) const;
    bool operator==(const MessageInterface& other) const override;
    MessageInterface* clone() const override;
};
