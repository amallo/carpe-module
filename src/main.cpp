#include <Wire.h>
#include "core/Screen.h"
#include "core/OLEDScreen.h"
#include "core/ConfigManager.h"
#include "core/MacAddressDeviceIdGenerator.h"

#define OLED_SDA 21
#define OLED_SCL 22

Screen* screen = new OLEDScreen();
ConfigManager* configManager = new ConfigManager();

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  Serial.begin(115200);

  if (!screen->begin()) {
    screen->showError("(FATAL) Impossible d'initialiser l'écran OLED");
    while (true);
  }
  
  screen->showStatus("Chargement");
  delay(1000);
  if (!configManager->begin()){
    screen->showStatus("Erreur");
    screen->showError("(FATAL) Impossible de charger SPIFFS");
    while (true);
  }
  if (configManager->loadConfig()){
    screen->showStatus("PRET");
    screen->showMessage(configManager->getDeviceId());
    return;
  }
  screen->showStatus("Initialsation...");
  MacAddressDeviceIdGenerator* idGenerator = new MacAddressDeviceIdGenerator();
  String deviceId = idGenerator->generate();
  configManager->setDeviceId(deviceId);
  configManager->saveConfig();
  screen->showStatus("PRET");
  screen->showMessage(configManager->getDeviceId());
  return;

}

void loop() {
}
