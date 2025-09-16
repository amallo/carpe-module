#include "MockPinCodeGenerator.h"

MockPinCodeGenerator::MockPinCodeGenerator() : currentIndex(0) {
}

std::string MockPinCodeGenerator::generatePinCode() {
    if (currentIndex < scheduledPinCodes.size()) {
        std::string pinCode = scheduledPinCodes[currentIndex];
        currentIndex++;
        return pinCode;
    }
    
    // Code PIN par défaut si aucun n'est programmé
    return "0000";
}

void MockPinCodeGenerator::scheduleGeneratedPinCode(const std::string& pinCode) {
    scheduledPinCodes.clear();
    scheduledPinCodes.push_back(pinCode);
    currentIndex = 0;
}

void MockPinCodeGenerator::scheduleGeneratedPinCodes(const std::vector<std::string>& pinCodes) {
    scheduledPinCodes = pinCodes;
    currentIndex = 0;
}

void MockPinCodeGenerator::reset() {
    scheduledPinCodes.clear();
    currentIndex = 0;
}

bool MockPinCodeGenerator::wasGenerateCalled() const {
    return currentIndex > 0;
}

int MockPinCodeGenerator::getGenerateCallCount() const {
    return currentIndex;
}
