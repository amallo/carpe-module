#include "ESP32BluetoothProvider.h"
#include "../BluetoothConstants.h"
#include <Arduino.h>
#include <core/Screen.h>



class ESP32BluetoothReceiveCallback : public NimBLECharacteristicCallbacks {
private:
    ESP32BluetoothProvider* provider;
public:
    ESP32BluetoothReceiveCallback(ESP32BluetoothProvider* prov) : provider(prov) {}
    
    void onWrite(NimBLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {

            provider->getLogger()->info(std::string(BluetoothConstants::Messages::RECEIVED_PREFIX) + value);
            provider->handleReceivedMessage(value);
        }
    }
};

class ESP32BluetoothServerCallback : public NimBLEServerCallbacks {
private:
    ESP32BluetoothProvider* provider;
public:
    ESP32BluetoothServerCallback(ESP32BluetoothProvider* prov) : provider(prov) {}
    
    void onConnect(NimBLEServer* pServer) {
        provider->getLogger()->info("🔗 Client connecté");
        
        // Récupérer l'adresse du client connecté - version simplifiée
        std::string deviceAddress = "unknown";
        if (pServer->getConnectedCount() > 0) {
            // Utiliser l'adresse de connexion disponible
            auto peerInfo = pServer->getPeerInfo(0);
            deviceAddress = peerInfo.getAddress().toString();
        }
        
        provider->handleDeviceConnected(deviceAddress);
    }
    
    void onDisconnect(NimBLEServer* pServer) {
        provider->getLogger()->info("🔌 Client déconnecté");
        provider->handleDeviceDisconnected("unknown");
        
        // Redémarrer l'advertising automatiquement après déconnexion
        provider->getLogger()->info("🔄 Redémarrage de l'advertising...");
        NimBLEDevice::startAdvertising();
    }
};

ESP32BluetoothProvider::ESP32BluetoothProvider(SerialLogger* logger) 
    : pServer(nullptr), pService(nullptr), pCharacteristic(nullptr), logger(logger), 
      connectionCallback(nullptr), receivedMessageCallback(nullptr), isInitialized(false) {
}

ESP32BluetoothProvider::~ESP32BluetoothProvider() {
    if (pServer && pServer->getAdvertising()) {
        pServer->getAdvertising()->stop();
    }
    NimBLEDevice::deinit(true);
}

bool ESP32BluetoothProvider::init(const std::string& deviceId) {
    logger->info("🔵 Initialisation du service Bluetooth...");
    logger->info("🏷️  Device ID: " + deviceId);
    
    // Initialiser BLE avec le nom du device
    NimBLEDevice::init(deviceId.c_str());
    
    // Configurer la puissance de transmission pour une meilleure portée
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);
    logger->debug("📡 Puissance de transmission configurée au maximum");
    
    // Créer le serveur BLE
    pServer = NimBLEDevice::createServer();
    if (!pServer) {
        logger->error("❌ Impossible de créer le serveur BLE");
        return false;
    }
    
    // Configurer les callbacks de connexion/déconnexion
    pServer->setCallbacks(new ESP32BluetoothServerCallback(this));
    
    // Créer le service
    NimBLEService *pService = pServer->createService(BluetoothConstants::SERVICE_UUID);
    logger->debug("🔧 Service BLE créé avec UUID: " + std::string(BluetoothConstants::SERVICE_UUID));
    
    // Créer la caractéristique pour recevoir des messages
    pCharacteristic = pService->createCharacteristic(
        BluetoothConstants::CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | 
        NIMBLE_PROPERTY::WRITE |
        NIMBLE_PROPERTY::NOTIFY
    );
    logger->debug("📝 Caractéristique créée avec UUID: " + std::string(BluetoothConstants::CHARACTERISTIC_UUID));
    
    // Ajouter le callback pour recevoir des données
    pCharacteristic->setCallbacks(new ESP32BluetoothReceiveCallback(this));
    
    pService->start();
    isInitialized = true;
    logger->info("✅ Service Bluetooth initialisé avec succès");
    logger->info("📱 Nom BLE configuré: " + deviceId);
    return true;
}

bool ESP32BluetoothProvider::start() {
    if (!isInitialized) {
        logger->error(BluetoothConstants::format_not_initialized_message("start"));
        return false;
    }
    
    logger->info("📻 Démarrage de l'advertising Bluetooth...");
    
    // Configurer l'advertising pour être découvrable
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    
    // Ajouter le service UUID
    pAdvertising->addServiceUUID(BluetoothConstants::SERVICE_UUID);
    
    // Le nom a déjà été configuré dans init() avec NimBLEDevice::init(deviceId)
    // NimBLE utilise automatiquement ce nom pour l'advertising
    
    // Configurer l'advertising pour être découvrable ET connectable
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(BluetoothConstants::MIN_PREFERRED_CONNECTION_INTERVAL);
    pAdvertising->setMaxPreferred(BluetoothConstants::MAX_PREFERRED_CONNECTION_INTERVAL);
    
    // Forcer la visibilité avec flags explicites
    pAdvertising->setAppearance(0x0000);  // Generic device
    pAdvertising->setAdvertisementType(BLE_GAP_CONN_MODE_UND);  // Connectable undirected
    
    // Démarrer l'advertising en mode découvrable
    pAdvertising->start();
    
    logger->info(BluetoothConstants::Messages::SERVICE_STARTED);
    logger->info("🔍 Service UUID: " + std::string(BluetoothConstants::SERVICE_UUID));
    logger->info("📡 Device visible avec le Device ID configuré dans init()");
    return true;
}

bool ESP32BluetoothProvider::sendString(const std::string& message) {
    if (!isInitialized || !pCharacteristic) {
        logger->error(BluetoothConstants::format_not_initialized_message("send"));
        return false;
    }
    
    pCharacteristic->setValue(message.c_str());
    pCharacteristic->notify();
    logger->debug("📤 Message envoyé via BLE: " + message);
    return true;
}

bool ESP32BluetoothProvider::isConnected() {
    return pServer && pServer->getConnectedCount() > 0;
}

bool ESP32BluetoothProvider::isStarted() {
    return isInitialized && pServer && pCharacteristic;
}

void ESP32BluetoothProvider::setConnectionCallback(BluetoothConnectionCallback* callback) {
    connectionCallback = callback;
}

void ESP32BluetoothProvider::setReceivedMessageCallback(BluetoothReceivedMessageCallback* callback) {
    receivedMessageCallback = callback;
}

void ESP32BluetoothProvider::handleDeviceConnected(const std::string& deviceAddress) {
    logger->info("✅ Appairage réussi avec: " + deviceAddress);
    if (connectionCallback) {
        connectionCallback->onDeviceConnected(deviceAddress);
    }
}

void ESP32BluetoothProvider::handleDeviceDisconnected(const std::string& deviceAddress) {
    logger->info("❌ Déconnexion de: " + deviceAddress);
    if (connectionCallback) {
        connectionCallback->onDeviceDisconnected(deviceAddress);
    }
}

void ESP32BluetoothProvider::handleReceivedMessage(const std::string& message) {
    logger->info("🔍 Message reçu: " + message);
    if (receivedMessageCallback) {
        receivedMessageCallback->onReceivedMessage(message);
    }
}
