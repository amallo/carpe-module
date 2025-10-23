#include "AuthChallenge.h"

AuthChallenge::AuthChallenge(const std::string& id, const std::string& pinCode) 
    : id(id), pinCode(pinCode) {
}

const std::string& AuthChallenge::getId() const {
    return id;
}

const std::string& AuthChallenge::getPinCode() const {
    return pinCode;
}
