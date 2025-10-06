#pragma once
#include "Message.h"
#include <string>

class AuthRequestMessage : public Message {
public:
    explicit AuthRequestMessage(const std::string& challengeId, uint16_t nonce = 0);
    
    const std::string& getChallengeId() const;
    
    bool operator==(const AuthRequestMessage& other) const;
    
private:
    std::string challengeId;
};
