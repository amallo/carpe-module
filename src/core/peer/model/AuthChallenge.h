#pragma once
#include <string>

class AuthChallenge {
public:
    AuthChallenge(const std::string& id, const std::string& pinCode);
    
    const std::string& getId() const;
    const std::string& getPinCode() const;
    
private:
    std::string id;
    std::string pinCode;
};
