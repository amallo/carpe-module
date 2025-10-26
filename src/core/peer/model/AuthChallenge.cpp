#include "AuthChallenge.h"

AuthChallenge::AuthChallenge(const std::string& id, const std::string& pinCode, int remainingAttempts) 
    : id(id), pinCode(pinCode), remainingAttempts(remainingAttempts) {
}

const std::string& AuthChallenge::getId() const {
    return id;
}

const std::string& AuthChallenge::getPinCode() const {
    return pinCode;
}

bool AuthChallenge::matchPinCode(const std::string& pinCode) const {
    return this->pinCode == pinCode;
}
bool AuthChallenge::operator==(const AuthChallenge& other) const {
    return id == other.id && pinCode == other.pinCode;
}
int AuthChallenge::getRemainingAttempts() const {
    return remainingAttempts;
}
void AuthChallenge::decreaseRemainingAttempts() {
    remainingAttempts--;
}