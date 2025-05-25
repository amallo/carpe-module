#pragma once
#include "Screen.h"

class Adafruit_SSD1306; // Forward declaration

class OLEDScreen : public Screen {
private:
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int OLED_RESET = -1;
    static const uint8_t OLED_ADDRESS = 0x3C;
    
    Adafruit_SSD1306* display; // Pointeur pour éviter l'include
    
public:
    OLEDScreen();
    ~OLEDScreen();
    
    bool begin() override;
    void clear() override;
    void showMessage(const String& message) override;
    void showError(const String& error) override;
    void showStatus(const String& status) override;
    void update() override;
}; 