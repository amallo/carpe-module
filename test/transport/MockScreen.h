#pragma once
#include <string>
#include <vector>

class MockScreen {
public:
    MockScreen();
    
    void displayPinCodeChallenge(const std::string& pinCode);
    
    bool wasDisplayPinCodeChallengeCalledWithPinCode(const std::string& pinCode) const;
    const std::vector<std::string>& getDisplayedPinCodes() const;
    void reset();
    
private:
    std::vector<std::string> displayedPinCodes;
};
