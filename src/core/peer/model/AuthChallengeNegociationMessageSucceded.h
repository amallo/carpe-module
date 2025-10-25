#pragma once
#include "Message.h"
#include <string>

class AuthChallengeNegociationMessageSucceded : public Message {
public:
    explicit AuthChallengeNegociationMessageSucceded(const std::string& challengeId);
    
    const std::string& getChallengeId() const;
    
    bool operator==(const AuthChallengeNegociationMessageSucceded& other) const;
    
private:
    std::string challengeId;
};
