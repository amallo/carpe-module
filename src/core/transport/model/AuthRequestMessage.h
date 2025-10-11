#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <cstdint>

// Forward declaration
class AuthMessageEncoder;

class AuthRequestMessage : public Message {
public:
    explicit AuthRequestMessage(const std::string& challengeId, uint16_t nonce = 0);
    AuthRequestMessage(const std::string& challengeId, uint16_t nonce, AuthMessageEncoder& encoder);
    
    const std::string& getChallengeId() const;
    std::vector<uint8_t> encode() const;
    
    bool operator==(const AuthRequestMessage& other) const;
    
private:
    std::string challengeId;
    AuthMessageEncoder* encoder;
};
