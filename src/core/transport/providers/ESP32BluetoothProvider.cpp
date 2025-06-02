#include "ESP32BluetoothProvider.h"
#include <Arduino.h>

// UUIDs pour le service et la caractéristique BLE
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"


class ESP32BluetoothReceiveCallback : public BLECharacteristicCallbacks {
private:
    ESP32BluetoothProvider* provider;
public:
    ESP32BluetoothReceiveCallback(ESP32BluetoothProvider* prov) : provider(prov) {}
    
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Received via BLE: ");
            Serial.println(value.c_str());
        }
    }
};

ESP32BluetoothProvider::ESP32BluetoothProvider(BLEServer* server) 
    : pServer(server), pCharacteristic(nullptr), isInitialized(false) {
}

ESP32BluetoothProvider::~ESP32BluetoothProvider() {
    if (pServer && pServer->getAdvertising()) {
        pServer->getAdvertising()->stop();
    }
    BLEDevice::deinit(true);
}

bool ESP32BluetoothProvider::init(const std::string& deviceId) {
    // Initialiser BLE avec le nom du device
    BLEDevice::init(deviceId.c_str());
    
    // Créer le serveur BLE
    pServer = BLEDevice::createServer();
    if (!pServer) {
        return false;
    }
    
    // Créer le service
    BLEService *pService = pServer->createService("12345678-1234-1234-1234-123456789abc");
    
    // Créer la caractéristique pour recevoir des messages
    pCharacteristic = pService->createCharacteristic(
        "87654321-4321-4321-4321-cba987654321",
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    
    // Ajouter le callback pour recevoir des données
    pCharacteristic->setCallbacks(new ESP32BluetoothReceiveCallback(this));
    
    pService->start();
    isInitialized = true;
    return true;
}

bool ESP32BluetoothProvider::start() {
    if (!isInitialized) {
        Serial.println("ESP32BLE: Cannot start - not properly initialized. Did you call ESP32BLEProvider::init() ?");
        return false;
    }
    
    // Démarrer l'advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID("12345678-1234-1234-1234-123456789abc");
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    
    Serial.println("ESP32BLE: Service started and advertising");
    return true;
}

bool ESP32BluetoothProvider::sendString(const std::string& message) {
    if (!isInitialized || !pCharacteristic) {
        Serial.println("ESP32BLE: Cannot send - not properly initialized. Did you call ESP32BLEProvider::init() ?");
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
