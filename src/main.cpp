#include <Wire.h>
#include "core/Screen.h"
#include "core/OLEDScreen.h"
#include "core/config/NvsConfigManager.h"
#include "core/device/generators/RandomDeviceIdGenerator.h"
#include "core/transport/providers/BluetoothProvider.h"
#include "core/transport/providers/ESP32BluetoothProvider.h"
#include "core/services/arduino/ArduinoRandomService.h"
#include "core/services/arduino/ArduinoTimeService.h"
#include <Arduino.h>

// Configuration de l'écran OLED pour TTGO LoRa32 V1
#define OLED_SDA 21
#define OLED_SCL 22

Screen* screen = nullptr;
ConfigManager* configManager = nullptr;
ArduinoRandomService* randomService = nullptr;
ArduinoTimeService* timeService = nullptr;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("🚀 CARPE MODULE - ESP32 Production Build");
  Serial.println("=====================================");
  Serial.println("Architecture: Clean Architecture with Dependency Injection");
  Serial.println("Platform: ESP32 (Arduino Framework)");
  Serial.println();

  // Initialiser l'écran OLED
  screen = new OLEDScreen();
  if (!screen->init()) {
    Serial.println("❌ Erreur: Impossible d'initialiser l'écran OLED");
    return;
  }

  // Initialiser le gestionnaire de configuration
  configManager = new NvsConfigManager();
  
  // Vérifier si on a déjà un device ID
  std::string deviceId = configManager->getDeviceId();
  if (deviceId.empty()) {
    Serial.println("📝 Génération d'un nouvel ID device...");
    
    // Créer les services pour l'injection de dépendances
    randomService = new ArduinoRandomService();
    timeService = new ArduinoTimeService();
    
    // Créer le générateur avec injection de dépendances
    RandomDeviceIdGenerator* idGenerator = new RandomDeviceIdGenerator(randomService, timeService);
    deviceId = idGenerator->generate();
    configManager->setDeviceId(deviceId);
    
    Serial.print("✅ Nouvel ID généré: ");
    Serial.println(deviceId.c_str());
    
    delete idGenerator;
  } else {
    Serial.print("📋 ID device existant: ");
    Serial.println(deviceId.c_str());
  }

  // Afficher l'ID sur l'écran
  screen->showMessage(deviceId);

  // Initialiser le Bluetooth
  BLEServer* pServer = nullptr; // Sera créé dans ESP32BluetoothProvider::init()
  BluetoothProvider* bluetoothProvider = new ESP32BluetoothProvider(pServer);
  if (bluetoothProvider->init(deviceId)) {
    bluetoothProvider->start();
    Serial.println("✅ Bluetooth initialisé et démarré");
    screen->showStatus("BLE: Actif - " + deviceId.substr(6));
  } else {
    Serial.println("❌ Erreur: Impossible d'initialiser le Bluetooth");
    screen->showError("BLE: Erreur init");
  }

  Serial.println();
  Serial.println("🏁 Initialisation terminée !");
  Serial.println("=====================================");
}

void loop() {
  // Boucle principale
  delay(1000);
}
