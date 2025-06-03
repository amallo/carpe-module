#include <Wire.h>
#include <core/Screen.h>
#include <core/OLEDScreen.h>
#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/nvs/NvsConfigProvider.h>
#include <core/device/generators/RandomDeviceIdGenerator.h>
#include <core/transport/providers/BluetoothProvider.h>
#include <core/transport/providers/ESP32BluetoothProvider.h>
#include <core/random/providers/arduino/ArduinoRandomProvider.h>
#include <core/time/providers/arduino/ArduinoTimeProvider.h>
#include <core/logging/providers/arduino/SerialLogger.h>
#include <Arduino.h>

// Configuration de l'écran OLED pour TTGO LoRa32 V1
#define OLED_SDA 21
#define OLED_SCL 22

Screen* screen = nullptr;
ConfigProvider* configProvider = nullptr;
ArduinoRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;
SerialLogger* logger = nullptr;

void setup() {
  // Initialiser le logger
  logger = new SerialLogger(true);  // avec timestamp
  logger->begin(115200);
  logger->setLevel(LogLevel::INFO);
  
  logger->info("🚀 CARPE MODULE - ESP32 Production Build");
  logger->info("=====================================");
  logger->info("Architecture: Clean Architecture with Dependency Injection");
  logger->info("Platform: ESP32 (Arduino Framework)");
  logger->info("");

  // Initialiser l'écran OLED
  screen = new OLEDScreen();
  if (!screen->init()) {
    logger->error("❌ Erreur: Impossible d'initialiser l'écran OLED");
    return;
  }

  // Initialiser le gestionnaire de configuration
  configProvider = new NvsConfigProvider();
  
  // Vérifier si on a déjà un device ID
  std::string deviceId = configProvider->getDeviceId();
  if (deviceId.empty()) {
    logger->info("📝 Génération d'un nouvel ID device...");
    
    // Créer les services pour l'injection de dépendances
    randomProvider = new ArduinoRandomProvider();
    timeProvider = new ArduinoTimeProvider();
    
    // Créer le générateur avec injection de dépendances
    RandomDeviceIdGenerator* idGenerator = new RandomDeviceIdGenerator(randomProvider, timeProvider);
    deviceId = idGenerator->generate();
    configProvider->setDeviceId(deviceId);
    
    logger->info("✅ Nouvel ID généré: " + deviceId);
    
    delete idGenerator;
  } else {
    logger->info("📋 ID device existant: " + deviceId);
  }

  // Afficher l'ID sur l'écran
  screen->showMessage(deviceId);

  // Initialiser le Bluetooth
  NimBLEServer* pServer = nullptr; // Sera créé dans ESP32BluetoothProvider::init()
  BluetoothProvider* bluetoothProvider = new ESP32BluetoothProvider(pServer);
  if (bluetoothProvider->init(deviceId)) {
    bluetoothProvider->start();
    logger->info("✅ Bluetooth NimBLE initialisé et démarré");
    screen->showStatus("BLE: Actif - " + deviceId.substr(6));
  } else {
    logger->error("❌ Erreur: Impossible d'initialiser le Bluetooth");
    screen->showError("BLE: Erreur init");
  }

  logger->info("");
  logger->info("🏁 Initialisation terminée !");
  logger->info("=====================================");
}

void loop() {
  // Boucle principale
  delay(1000);
}
