#include "MockPinCodeGenerator.h"

MockPinCodeGenerator::MockPinCodeGenerator() : currentIndex(0), wasGeneratePinCodeCalledFlag(false) {}

std::string MockPinCodeGenerator::generatePinCode() {
    wasGeneratePinCodeCalledFlag = true;
    if (currentIndex < scheduledPinCodes.size()) {
        return scheduledPinCodes[currentIndex++];
    }
    return "1234"; // Default mock value
}

void MockPinCodeGenerator::scheduleGeneratedPinCode(const std::string& pinCode) {
    scheduledPinCodes.push_back(pinCode);
}

void MockPinCodeGenerator::clearScheduledPinCodes() {
    scheduledPinCodes.clear();
    currentIndex = 0;
}

bool MockPinCodeGenerator::wasGeneratePinCodeCalled() const {
    return wasGeneratePinCodeCalledFlag;
}

void MockPinCodeGenerator::resetCallTracker() {
    wasGeneratePinCodeCalledFlag = false;
}
