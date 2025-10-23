#include "Challenge.h"

Challenge::Challenge(const std::string& id, const std::string& pinCode) 
    : id(id), pinCode(pinCode) {
}

const std::string& Challenge::getId() const {
    return id;
}

const std::string& Challenge::getPinCode() const {
    return pinCode;
}
