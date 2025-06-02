#include "ESP32BluetoothProvider.h"
#include "BluetoothConstants.h"
#include <Arduino.h>

class ESP32BluetoothReceiveCallback : public NimBLECharacteristicCallbacks {
private:
    ESP32BluetoothProvider* provider;
public:
    ESP32BluetoothReceiveCallback(ESP32BluetoothProvider* prov) : provider(prov) {}
    
    void onWrite(NimBLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print(BluetoothConstants::Messages::RECEIVED_PREFIX);
            Serial.println(value.c_str());
        }
    }
};

ESP32BluetoothProvider::ESP32BluetoothProvider(NimBLEServer* server) 
    : pServer(server), pCharacteristic(nullptr), isInitialized(false) {
}

ESP32BluetoothProvider::~ESP32BluetoothProvider() {
    if (pServer && pServer->getAdvertising()) {
        pServer->getAdvertising()->stop();
    }
    NimBLEDevice::deinit(true);
}

bool ESP32BluetoothProvider::init(const std::string& deviceId) {
    // Initialiser BLE avec le nom du device
    NimBLEDevice::init(deviceId.c_str());
    
    // Créer le serveur BLE
    pServer = NimBLEDevice::createServer();
    if (!pServer) {
        return false;
    }
    
    // Créer le service
    NimBLEService *pService = pServer->createService(BluetoothConstants::SERVICE_UUID);
    
    // Créer la caractéristique pour recevoir des messages
    pCharacteristic = pService->createCharacteristic(
        BluetoothConstants::CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | 
        NIMBLE_PROPERTY::WRITE |
        NIMBLE_PROPERTY::NOTIFY
    );
    
    // Ajouter le callback pour recevoir des données
    pCharacteristic->setCallbacks(new ESP32BluetoothReceiveCallback(this));
    
    pService->start();
    isInitialized = true;
    return true;
}

bool ESP32BluetoothProvider::start() {
    if (!isInitialized) {
        Serial.println(BluetoothConstants::format_not_initialized_message("start").c_str());
        return false;
    }
    
    // Démarrer l'advertising
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BluetoothConstants::SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(BluetoothConstants::MIN_PREFERRED_CONNECTION_INTERVAL);
    pAdvertising->setMinPreferred(BluetoothConstants::MAX_PREFERRED_CONNECTION_INTERVAL);
    NimBLEDevice::startAdvertising();
    
    Serial.println(BluetoothConstants::Messages::SERVICE_STARTED);
    return true;
}

bool ESP32BluetoothProvider::sendString(const std::string& message) {
    if (!isInitialized || !pCharacteristic) {
        Serial.println(BluetoothConstants::format_not_initialized_message("send").c_str());
        return false;
    }
    pCharacteristic->setValue(message.c_str());
    pCharacteristic->notify();
    return true;
}

bool ESP32BluetoothProvider::isConnected() {
    return pServer && pServer->getConnectedCount() > 0;
}

bool ESP32BluetoothProvider::isStarted() {
    return isInitialized && pServer && pCharacteristic;
}
