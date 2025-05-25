#include <Wire.h>
#include "core/Screen.h"
#include "core/OLEDScreen.h"

#define OLED_SDA 21
#define OLED_SCL 22

Screen* screen = new OLEDScreen();

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  Serial.begin(115200);

  if (!screen->begin()) {
    Serial.println(F("Erreur d'initialisation OLED"));
    while (true);
  }
  
  screen->showStatus("Hello MONCUL");
  delay(2000);
  screen->showMessage("Hello World!");
}

void loop() {
}
