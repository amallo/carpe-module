#include "OLEDScreen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

OLEDScreen::OLEDScreen() 
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
    // Initialiser I2C
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
}

bool OLEDScreen::begin() {
    // Initialiser l'écran OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        return false;
    }
    
    clear();
    return true;
}

void OLEDScreen::showMessage(const String& message) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(message);
    display.display();
}

void OLEDScreen::showStatus(const String& status) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("STATUS:");
    display.setCursor(0, 10);
    display.println(status);
    display.display();
}

void OLEDScreen::showError(const String& error) {
    clear();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ERREUR:");
    display.setCursor(0, 10);
    display.println(error);
    display.display();
}

void OLEDScreen::clear() {
    display.clearDisplay();
    display.display();
}

void OLEDScreen::update() {
    display.display();
} 