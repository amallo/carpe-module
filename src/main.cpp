#include <Wire.h>
#include <core/device/providers/Screen.h>
#include <core/device/providers/infra/OLEDScreen.h>
#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/infra/NvsConfigProvider.h>
#include <core/device/generators/infra/RandomDeviceIdGenerator.h>
#include <core/device/generators/infra/RandomPinCodeGenerator.h>
#include <core/device/SetupDeviceUseCase.h>
#include <core/transport/PeerConnection.h>
#include <core/transport/providers/infra/Esp32MessageTransport.h>
#include <core/transport/providers/infra/Esp32AuthMessageEncoder.h>
#include <core/transport/generators/infra/Esp32ChallengeGenerator.h>
#include <core/random/providers/infra/SecureRandomProvider.h>
#include <core/time/providers/infra/ArduinoTimeProvider.h>
#include <core/logging/providers/infra/SerialLogger.h>
#include <Arduino.h>

// Configuration de l'écran OLED pour TTGO LoRa32 V1
// Utiliser les pins par défaut du board (SDA=4, SCL=15)


// Services de base
Screen* screen = nullptr;
ConfigProvider* configProvider = nullptr;
SecureRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;
SerialLogger* logger = nullptr;

// Services de transport
Esp32MessageTransport* messageTransport = nullptr;
Esp32AuthMessageEncoder* authMessageEncoder = nullptr;
Esp32ChallengeGenerator* challengeGenerator = nullptr;
PeerConnection* peerConnection = nullptr;
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

  // Initialiser les services de transport
  messageTransport = new Esp32MessageTransport("bluetooth");
  authMessageEncoder = new Esp32AuthMessageEncoder();
  challengeGenerator = new Esp32ChallengeGenerator(randomProvider);
  
  // Initialiser le transport Bluetooth
  if (!messageTransport->init(deviceId)) {
    logger->error("❌ Erreur: Impossible d'initialiser le transport Bluetooth");
    screen->showError("BLE: Erreur init");
    return;
  }
  
  messageTransport->start();
  logger->info("✅ Transport Bluetooth initialisé et démarré");
  
  // Créer la connexion peer avec injection de dépendances
  peerConnection = new PeerConnection(challengeGenerator, *messageTransport, *screen, *authMessageEncoder);
  logger->info("✅ PeerConnection initialisé avec Clean Architecture");

  // Nettoyage des ressources
  delete idGenerator;
  delete pinCodeGenerator;

  logger->info("");
  logger->info("🏁 Lancement terminé !");
  logger->info("=====================================");
}

void loop() {
  // Boucle principale
  static unsigned long lastConnectionTest = 0;
  static bool connectionTested = false;
  
  // Simuler une connexion après 5 secondes pour tester PeerConnection
  if (!connectionTested && millis() - lastConnectionTest > 5000) {
    logger->info("🔗 Simulation d'une connexion device...");
    peerConnection->onDeviceConnected("AA:BB:CC:DD:EE:FF");
    connectionTested = true;
  }
  
  delay(1000);
}
