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
#include <core/peer/providers/infra/LoRaMessageGateway.h>
#include <core/peer/providers/infra/InMemoryAuthChallengeStore.h>
#include <core/peer/providers/infra/NimBLEConnectionCallback.h>
#include <core/peer/providers/infra/NimBLECharacteristicCallback.h>
#include <core/peer/usecases/InitiateAuthChallengeUseCase.h>
#include <core/peer/usecases/ReceiveMessageUseCase.h>
#include <core/peer/protocol/decoders/MessageDecoder.h>
#include <core/peer/generators/infra/RandomAuthChallengeGenerator.h>
#include <core/device/providers/infra/OLEDScreen.h>
#include <LoRa.h>

// Services de base
SerialLogger* logger = nullptr;
ConfigProvider* configProvider = nullptr;
SecureRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;

// Services NimBLE
NimBLEServer* pServer = nullptr;
NimBLEConnectionCallback* connectionCallback = nullptr;
NimBLECharacteristicCallback* characteristicCallback = nullptr;
InitiateAuthChallengeUseCase* initiateAuthChallengeUseCase = nullptr;

// Services pour ReceiveMessageUseCase
MessageDecoder* messageDecoder = nullptr;
LoRaMessageGateway* loraMessageGateway = nullptr;
ReceiveMessageUseCase* receiveMessageUseCase = nullptr;
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

  // Initialiser LoRa
  logger->info("📡 Initialisation de LoRa...");
  loraMessageGateway = new LoRaMessageGateway();
  if (!loraMessageGateway->begin(868E6, 18, 14, 26)) {
    logger->error("❌ Erreur lors de l'initialisation de LoRa");
    delete loraMessageGateway;
    loraMessageGateway = nullptr;
  } else {
    logger->info("✅ LoRa initialisé avec succès");
  }

  // Initialiser NimBLE
  logger->info("🔵 Initialisation de NimBLE...");
  NimBLEDevice::init("Carpe-" + deviceId);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  
  // Créer le serveur BLE
  pServer = NimBLEDevice::createServer();
  
  // Créer les services pour InitiateAuthChallengeUseCase
  OLEDScreen screen;
  NimBLEMessageGateway blueToothMessageGateway;
  InMemoryAuthChallengeStore authChallengeStore;
  RandomAuthChallengeGenerator authChallengeGenerator(randomProvider);
  
  // Créer le use case pour l'initiation de challenge
  InitiateAuthChallengeUseCase initiateAuthChallengeUseCase(
    screen,
    authChallengeGenerator, 
    blueToothMessageGateway, 
    authChallengeStore
  );
  
  // Créer les services pour ReceiveMessageUseCase
  messageDecoder = new MessageDecoder();
  if (loraMessageGateway) {
    receiveMessageUseCase = new ReceiveMessageUseCase(
      *messageDecoder,
      blueToothMessageGateway,
      *loraMessageGateway
    );
  }
  
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
  blueToothMessageGateway.setCharacteristic(pCharacteristic);
  
  // Créer et attacher le callback pour la réception de messages
  if (receiveMessageUseCase) {
    characteristicCallback = new NimBLECharacteristicCallback(*receiveMessageUseCase);
    pCharacteristic->setCallbacks(characteristicCallback);
  }
  
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
  // Vérifier s'il y a des messages LoRa reçus
  if (receiveMessageUseCase && loraMessageGateway) {
    int packetSize = LoRa.parsePacket();
    if (packetSize > 0) {
      // Lire les données du paquet LoRa
      std::vector<uint8_t> data;
      data.reserve(packetSize);
      
      while (LoRa.available()) {
        data.push_back(LoRa.read());
      }
      
      // Appeler le use case avec la source LORA
      if (data.size() > 0) {
        receiveMessageUseCase->execute(data, ReceiveMessageUseCase::Source::LORA);
      }
    }
  }
  
  delay(10);  // Petit délai pour éviter de surcharger le CPU
}
