#pragma once
#include <core/device/PinCodeGenerator.h>
#include <string>
#include <vector>

class MockPinCodeGenerator : public PinCodeGenerator {
private:
    mutable std::vector<std::string> scheduledPinCodes;
    mutable int currentIndex;
    bool wasGeneratePinCodeCalledFlag;

public:
    MockPinCodeGenerator();

    std::string generatePinCode() override;

    // For testing purposes
    void scheduleGeneratedPinCode(const std::string& pinCode);
    void clearScheduledPinCodes();
    bool wasGeneratePinCodeCalled() const;
    void resetCallTracker();
};
