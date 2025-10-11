#pragma once
#include <string>

class Screen {
public:
    virtual ~Screen() = default;
    virtual void displayPinCodeChallenge(const std::string& pinCode) = 0;
};
