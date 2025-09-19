#include <Wire.h>
#include <core/Screen.h>
#include <core/OLEDScreen.h>
#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/infra/NvsConfigProvider.h>
#include <core/device/generators/infra/RandomDeviceIdGenerator.h>
#include <core/device/generators/infra/RandomPinCodeGenerator.h>
#include <core/device/SetupDeviceUseCase.h>
#include <core/transport/providers/BluetoothProvider.h>
#include <core/transport/providers/infra/ESP32BluetoothProvider.h>
#include <core/random/providers/infra/SecureRandomProvider.h>
#include <core/time/providers/infra/ArduinoTimeProvider.h>
#include <core/logging/providers/infra/SerialLogger.h>
#include <Arduino.h>

// Configuration de l'écran OLED pour TTGO LoRa32 V1
#define OLED_SDA 21
#define OLED_SCL 22


Screen* screen = nullptr;
ConfigProvider* configProvider = nullptr;
SecureRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;
SerialLogger* logger = nullptr;
BluetoothConnectionCallback* bluetoothCallback = nullptr;
BluetoothReceivedMessageCallback* bluetoothReceivedMessageCallback = nullptr;
void setup() {
  // Initialiser le logger
  logger = new SerialLogger(true);  // avec timestamp
  logger->begin(115200);
  logger->setLevel(LogLevel::INFO);
  
  logger->info("🚀 Initialisation de Carpe...");
  logger->info("=====================================");
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
  
  // Créer les services pour l'injection de dépendances
  randomProvider = new SecureRandomProvider();
  timeProvider = new ArduinoTimeProvider();
  
  // Générateurs
  RandomDeviceIdGenerator* idGenerator = new RandomDeviceIdGenerator(randomProvider, timeProvider);
  RandomPinCodeGenerator* pinCodeGenerator = new RandomPinCodeGenerator(randomProvider);
  
  // On setup le device au démarrage si nécessaire
  SetupDeviceUseCase setupUseCase(configProvider, idGenerator, pinCodeGenerator);
  SetupDeviceRequest request;
  SetupDeviceResponse response = setupUseCase.execute(request);
  
  std::string deviceId;
  if (response.success) {
    logger->info("✅ Device initialisé avec succès. Device ID: " + response.device_id);
    deviceId = response.device_id;
    // Le PIN n'est plus utilisé au démarrage; il sera généré à la connexion
  } else if (response.error_message == "ALREADY_INITIALIZED") {
    logger->info("📋 Le device a déjà été initialisé. Device ID existant: " + response.device_id);
    deviceId = response.device_id;
    // Le PIN n'est plus utilisé au démarrage; il sera généré à la connexion
  } else {
    logger->error("❌ Erreur lors de l'initialisation du device: " + response.error_message);
    screen->showError("Device: Erreur");
    delete idGenerator;
    delete pinCodeGenerator;
    return;
  }

  // Afficher le statut d'attente de connexion (optimisé pour OLED)
  std::string statusMessage = deviceId + "\nATTENTE...";
  screen->showMessage(statusMessage);
  logger->info("📱 " + deviceId + " en attente de connexion");

  // Initialiser le Bluetooth
  ESP32BluetoothProvider* bluetoothProvider = new ESP32BluetoothProvider(logger);
  
  // Créer le callback Bluetooth avec injection du provider et du générateur de PIN sécurisé
  bluetoothCallback = new BluetoothConnectionCallback(logger, screen, bluetoothProvider, pinCodeGenerator);
  bluetoothCallback->setDeviceId(deviceId);
  bluetoothReceivedMessageCallback = new BluetoothReceivedMessageCallback(logger, screen);
  
  // Configurer les callbacks
  bluetoothProvider->setConnectionCallback(bluetoothCallback);
  bluetoothProvider->setReceivedMessageCallback(bluetoothReceivedMessageCallback);
  if (bluetoothProvider->init(deviceId)) {
    bluetoothProvider->start();
    logger->info("✅ Bluetooth NimBLE initialisé et démarré");
    // L'écran affiche déjà le message d'attente de connexion
  } else {
    logger->error("❌ Erreur: Impossible d'initialiser le Bluetooth");
    screen->showError("BLE: Erreur init");
  }

  // Nettoyage des ressources
  delete idGenerator;
  // Ne pas supprimer pinCodeGenerator; utilisé après connexion par le callback

  logger->info("");
  logger->info("🏁 Lancement terminé !");
  logger->info("=====================================");
}

void loop() {
  // Boucle principale
  delay(1000);
}
