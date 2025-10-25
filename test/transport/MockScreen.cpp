#include "MockScreen.h"

MockScreen::MockScreen() : initialized(false) {
}

bool MockScreen::init() {
    initialized = true;
    return true;
}

void MockScreen::clear() {
    // Mock implementation - no-op
}

void MockScreen::showMessage(const std::string& message) {
    shownMessages.push_back(message);
}

void MockScreen::showError(const std::string& error) {
    shownErrors.push_back(error);
}

void MockScreen::showStatus(const std::string& status) {
    shownStatuses.push_back(status);
}

void MockScreen::update() {
    // Mock implementation - no-op
}

void MockScreen::displayPinCodeChallenge(const std::string& pinCode) {
    displayedPinCodes.push_back(pinCode);
}

void MockScreen::displaySuccessMessage(const std::string& message) {
    successMessages.push_back(message);
}

void MockScreen::displayFailureMessage(const std::string& message) {
    failureMessages.push_back(message);
}

void MockScreen::displayTimeoutMessage(const std::string& message) {
    timeoutMessages.push_back(message);
}

bool MockScreen::wasDisplayedPinCodeChallenge(const std::string& pinCode) const {
    for (const auto& displayedPin : displayedPinCodes) {
        if (displayedPin == pinCode) {
            return true;
        }
    }
    return false;
}

bool MockScreen::wasDisplayedSuccessMessage() const {
    return !successMessages.empty();
}

bool MockScreen::wasDisplayedFailureMessage() const {
    return !failureMessages.empty();
}

bool MockScreen::wasDisplayedTimeoutMessage() const {
    return !timeoutMessages.empty();
}

bool MockScreen::wasShownMessage(const std::string& message) const {
    for (const auto& shownMessage : shownMessages) {
        if (shownMessage == message) {
            return true;
        }
    }
    return false;
}

bool MockScreen::wasShownError(const std::string& error) const {
    for (const auto& shownError : shownErrors) {
        if (shownError == error) {
            return true;
        }
    }
    return false;
}

bool MockScreen::wasShownStatus(const std::string& status) const {
    for (const auto& shownStatus : shownStatuses) {
        if (shownStatus == status) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string>& MockScreen::getDisplayedPinCodes() const {
    return displayedPinCodes;
}

const std::vector<std::string>& MockScreen::getShownMessages() const {
    return shownMessages;
}

const std::vector<std::string>& MockScreen::getShownErrors() const {
    return shownErrors;
}

const std::vector<std::string>& MockScreen::getShownStatuses() const {
    return shownStatuses;
}

void MockScreen::reset() {
    displayedPinCodes.clear();
    shownMessages.clear();
    shownErrors.clear();
    shownStatuses.clear();
    successMessages.clear();
    failureMessages.clear();
    timeoutMessages.clear();
    initialized = false;
}
