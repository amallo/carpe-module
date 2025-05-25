#include "OLEDScreen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

OLEDScreen::OLEDScreen() {
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

OLEDScreen::~OLEDScreen() {
    delete display;
}

bool OLEDScreen::begin() {
    if (!display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        return false;
    }
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->display();
    return true;
}

void OLEDScreen::clear() {
    display->clearDisplay();
}

void OLEDScreen::showMessage(const String& message) {
    clear();
    display->setCursor(0, 0);
    display->println("Message:");
    display->println(message);
    update();
}

void OLEDScreen::showError(const String& error) {
    clear();
    display->setCursor(0, 0);
    display->println("ERREUR:");
    display->setTextColor(SSD1306_WHITE);
    display->println(error);
    update();
}

void OLEDScreen::showStatus(const String& status) {
    clear();
    display->setCursor(0, 0);
    display->println("Status:");
    display->println(status);
    update();
}

void OLEDScreen::update() {
    display->display();
} 