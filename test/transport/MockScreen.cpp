#include "MockScreen.h"

MockScreen::MockScreen() {
}

void MockScreen::displayPinCodeChallenge(const std::string& pinCode) {
    displayedPinCodes.push_back(pinCode);
}

bool MockScreen::wasDisplayPinCodeChallengeCalledWithPinCode(const std::string& pinCode) const {
    for (const auto& displayedPin : displayedPinCodes) {
        if (displayedPin == pinCode) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string>& MockScreen::getDisplayedPinCodes() const {
    return displayedPinCodes;
}

void MockScreen::reset() {
    displayedPinCodes.clear();
}
