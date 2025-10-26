#pragma once
#include <string>

class AuthChallenge {
public:
    AuthChallenge(const std::string& id, const std::string& pinCode, int remainingAttempts = 3);
    
    const std::string& getId() const;
    const std::string& getPinCode() const;
    bool operator==(const AuthChallenge& other) const;
    
private:
    std::string id;
    std::string pinCode;
    int remainingAttempts;
};
