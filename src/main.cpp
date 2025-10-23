#include <Arduino.h>
#include <core/logging/providers/infra/SerialLogger.h>
#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/infra/NvsConfigProvider.h>
#include <core/device/generators/infra/RandomDeviceIdGenerator.h>
#include <core/device/generators/infra/RandomPinCodeGenerator.h>
#include <core/device/SetupDeviceUseCase.h>
#include <core/random/providers/infra/SecureRandomProvider.h>
#include <core/time/providers/infra/ArduinoTimeProvider.h>

// Services de base
SerialLogger* logger = nullptr;
ConfigProvider* configProvider = nullptr;
SecureRandomProvider* randomProvider = nullptr;
ArduinoTimeProvider* timeProvider = nullptr;
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

  // Nettoyage des ressources
  delete idGenerator;
  delete pinCodeGenerator;

  logger->info("🏁 Lancement terminé !");
}

void loop() {
  // Boucle principale - nouvelle logique à implémenter
  delay(1000);
}
