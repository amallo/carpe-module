#include <Wire.h>
#include "core/Screen.h"
#include "core/OLEDScreen.h"
#include "core/NvsConfigManager.h"
#include "core/RandomDeviceIdGenerator.h"
#include "core/BluetoothProvider.h"
#include "core/ESP32BluetoothProvider.h"


#define OLED_SDA 21
#define OLED_SCL 22

Screen* screen = new OLEDScreen();
NvsConfigManager* configManager = new NvsConfigManager();

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  Serial.begin(115200);

  if (!screen->begin()) {
    screen->showError("(FATAL) Impossible d'initialiser l'écran OLED");
    while (true);
  }
  
  screen->showStatus("Chargement");
  delay(1000);
  
  if (configManager->loadConfig()){
    screen->showStatus("PRET");
    screen->showMessage(configManager->getDeviceId());
    return;
  }
  screen->showStatus("Initialisation");
  RandomDeviceIdGenerator* idGenerator = new RandomDeviceIdGenerator();
  String deviceId = idGenerator->generate();
  configManager->setDeviceId(deviceId);
  configManager->saveConfig();
  screen->showStatus("PRET");
  screen->showMessage(configManager->getDeviceId());

  // Démarrage du fournisseur BLE
  BLEServer *pServer = BLEDevice::createServer();
  BluetoothProvider* bluetoothProvider = new ESP32BluetoothProvider(pServer);
  bluetoothProvider->init(deviceId);
  bluetoothProvider->start();

  return;

}

void loop() {
}
