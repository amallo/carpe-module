#pragma once
#include <string>
#include <vector>
#include "core/transport/Screen.h"

class MockScreen : public Screen {
public:
    MockScreen();
    
    void displayPinCodeChallenge(const std::string& pinCode) override;
    
    bool wasDisplayedPinCodeChallenge(const std::string& pinCode) const;
    const std::vector<std::string>& getDisplayedPinCodes() const;
    void reset();
    
private:
    std::vector<std::string> displayedPinCodes;
};
