#include <Arduino.h>
#include <core/logging/providers/infra/SerialLogger.h>
#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/infra/NvsConfigProvider.h>
#include <core/device/generators/infra/RandomDeviceIdGenerator.h>
#include <core/device/generators/infra/RandomPinCodeGenerator.h>
#include <core/device/SetupDeviceUseCase.h>
#include <core/random/providers/infra/SecureRandomProvider.h>
#include <core/time/providers/infra/ArduinoTimeProvider.h>
#include <NimBLEDevice.h>
#include <core/peer/providers/infra/NimBLEMessageGateway.h>
#include <core/peer/providers/infra/InMemoryAuthChallengeStore.h>
#include <core/peer/providers/infra/NimBLEConnectionCallback.h>
#include <core/peer/usecases/InitiateAuthChallengeUseCase.h>
#include <core/peer/generators/infra/RandomAuthChallengeGenerator.h>
#include <core/device/providers/infra/OLEDScreen.h>

// Services de base
SerialLogger* logger = nullptr;
ConfigProvider* configProvider = nullptr;
SecureRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;

// Services NimBLE
NimBLEServer* pServer = nullptr;
NimBLEConnectionCallback* connectionCallback = nullptr;
InitiateAuthChallengeUseCase* initiateAuthChallengeUseCase = nullptr;
void setup() {
  // Initialiser le logger
  logger = new SerialLogger(true);
  logger->begin(115200);
  logger->setLevel(LogLevel::INFO);
  
  logger->info("🚀 Initialisation de Carpe...");
  logger->info("Platform: ESP32 (Arduino Framework)");

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
  } else if (response.error_message == "ALREADY_INITIALIZED") {
    logger->info("📋 Le device a déjà été initialisé. Device ID existant: " + response.device_id);
    deviceId = response.device_id;
  } else {
    logger->error("❌ Erreur lors de l'initialisation du device: " + response.error_message);
    delete idGenerator;
    delete pinCodeGenerator;
    return;
  }

  logger->info("📱 " + deviceId + " en attente de connexion");

  // Initialiser NimBLE
  logger->info("🔵 Initialisation de NimBLE...");
  NimBLEDevice::init("Carpe-" + deviceId);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  
  // Créer le serveur BLE
  pServer = NimBLEDevice::createServer();
  
  // Créer les services pour InitiateAuthChallengeUseCase
  OLEDScreen screen;
  NimBLEMessageGateway messageGateway;
  InMemoryAuthChallengeStore authChallengeStore;
  RandomAuthChallengeGenerator authChallengeGenerator(randomProvider);
  
  // Créer le use case
  InitiateAuthChallengeUseCase initiateAuthChallengeUseCase(
    screen,
    authChallengeGenerator, 
    messageGateway, 
    authChallengeStore
  );
  
  // Créer le callback de connexion
  connectionCallback = new NimBLEConnectionCallback(initiateAuthChallengeUseCase);
  pServer->setCallbacks(connectionCallback);
  
  // Créer le service BLE
  NimBLEService* pService = pServer->createService("12345678-1234-1234-1234-123456789abc");
  NimBLECharacteristic* pCharacteristic = pService->createCharacteristic(
    "87654321-4321-4321-4321-cba987654321",
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
  );
  
  // Connecter la caractéristique au message gateway
  messageGateway.setCharacteristic(pCharacteristic);
  
  // Démarrer le service et la publicité
  pService->start();
  NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("12345678-1234-1234-1234-123456789abc");
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMaxPreferred(0x12);
  pAdvertising->start();
  
  logger->info("🔵 BLE démarré - En attente de connexions...");

  // Nettoyage des ressources
  delete idGenerator;
  delete pinCodeGenerator;

  logger->info("🏁 Lancement terminé !");
}

void loop() {
  // Boucle principale - nouvelle logique à implémenter
  delay(1000);
}
