#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <cstdint>

// Forward declaration
class AuthMessageEncoder;

class InitiateAuthChallengeMessage : public Message {
public:
    explicit InitiateAuthChallengeMessage(const std::string& challengeId, uint16_t nonce = 0);
    InitiateAuthChallengeMessage(const std::string& challengeId, uint16_t nonce, AuthMessageEncoder& encoder);
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const;
    
    bool operator==(const InitiateAuthChallengeMessage& other) const;
    
private:
    std::string challengeId;
    AuthMessageEncoder* encoder;
};
