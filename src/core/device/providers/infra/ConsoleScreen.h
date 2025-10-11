#pragma once
#include "../Screen.h"
#include <iostream>

class ConsoleScreen : public Screen {
public:
    bool init() override {
        return true;
    }

    void showMessage(const std::string& message) override {
        std::cout << "[SCREEN] " << message << std::endl;
    }

    void showError(const std::string& error) override {
        std::cout << "[SCREEN][ERROR] " << error << std::endl;
    }

    void showStatus(const std::string& status) override {
        std::cout << "[SCREEN][STATUS] " << status << std::endl;
    }

    void clear() override {
        // No-op for console
    }

    void update() override {
        // No-op for console
    }
};


