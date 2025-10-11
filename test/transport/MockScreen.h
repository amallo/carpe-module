#pragma once
#include <string>
#include <vector>
#include "core/device/providers/Screen.h"

class MockScreen : public Screen {
public:
    MockScreen();
    
    // Implémentation de l'interface Screen
    bool init() override;
    void clear() override;
    void showMessage(const std::string& message) override;
    void showError(const std::string& error) override;
    void showStatus(const std::string& status) override;
    void update() override;
    void displayPinCodeChallenge(const std::string& pinCode) override;
    
    // Méthodes de test
    bool wasDisplayedPinCodeChallenge(const std::string& pinCode) const;
    bool wasShownMessage(const std::string& message) const;
    bool wasShownError(const std::string& error) const;
    bool wasShownStatus(const std::string& status) const;
    const std::vector<std::string>& getDisplayedPinCodes() const;
    const std::vector<std::string>& getShownMessages() const;
    const std::vector<std::string>& getShownErrors() const;
    const std::vector<std::string>& getShownStatuses() const;
    void reset();
    
private:
    std::vector<std::string> displayedPinCodes;
    std::vector<std::string> shownMessages;
    std::vector<std::string> shownErrors;
    std::vector<std::string> shownStatuses;
    bool initialized;
};
