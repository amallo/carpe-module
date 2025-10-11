#include "OLEDScreen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Arduino.h>

OLEDScreen::OLEDScreen() 
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
    // Initialiser I2C
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
}

bool OLEDScreen::init() {
    // Initialiser l'écran OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        return false;
    }
    
    clear();
    return true;
}

void OLEDScreen::showMessage(const std::string& message) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(message.c_str());
    update();
}

void OLEDScreen::showStatus(const std::string& status) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("STATUS:");
    display.setCursor(0, 10);
    display.println(status.c_str());
    update();
}

void OLEDScreen::showError(const std::string& error) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ERREUR:");
    display.setCursor(0, 10);
    display.println(error.c_str());
    update();
}

void OLEDScreen::clear() {
    display.clearDisplay();
}

void OLEDScreen::update() {
    display.display();
}

void OLEDScreen::displayPinCodeChallenge(const std::string& pinCode) {
    clear();
    display.setTextSize(2);  // Plus gros pour le PIN
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println("PIN:");
    display.setCursor(0, 35);
    display.println(pinCode.c_str());
    update();
} 