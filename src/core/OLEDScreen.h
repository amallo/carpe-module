#pragma once
#include "Screen.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

class OLEDScreen : public Screen {
private:
    Adafruit_SSD1306 display;
    
    // Pins pour I2C (renommées pour éviter conflits avec macros board)
    static const int I2C_SDA_PIN = 21;
    static const int I2C_SCL_PIN = 22;
    
    // Configuration écran
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int SCREEN_ADDRESS = 0x3C;

public:
    OLEDScreen();
    bool init() override;
    void showMessage(const std::string& message) override;
    void showStatus(const std::string& status) override;
    void showError(const std::string& error) override;
    void clear() override;
    void update() override;
}; 