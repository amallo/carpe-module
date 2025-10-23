#include "BluetoothMessageTransport.h"
#include <Arduino.h>

// UUIDs pour le service et la caractéristique
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define MESSAGE_CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

BluetoothMessageTransport::BluetoothMessageTransport(const std::string& transportType) 
    : transportType(transportType), deviceName(""), isInitialized(false), isStarted(false),
      bleServer(nullptr), messageCharacteristic(nullptr) {
}

BluetoothMessageTransport::~BluetoothMessageTransport() {
    stop();
}

void BluetoothMessageTransport::send(const std::vector<uint8_t>& encodedMessage) {
    if (!isStarted || !messageCharacteristic) {
        return; // Bluetooth pas encore démarré
    }
    
    // Envoyer le message encodé via NimBLE
    messageCharacteristic->setValue(encodedMessage.data(), encodedMessage.size());
    messageCharacteristic->notify();
}

const std::string& BluetoothMessageTransport::getTransportType() const {
    return transportType;
}

bool BluetoothMessageTransport::init(const std::string& deviceName) {
    if (isInitialized) {
        return true;
    }
    
    this->deviceName = deviceName;
    
    // Initialiser NimBLE
    NimBLEDevice::init(deviceName.c_str());
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);
    
    // Créer le serveur BLE
    bleServer = NimBLEDevice::createServer();
    bleServer->setCallbacks(new NimBLEServerCallbacks());
    
    // Créer le service
    NimBLEService* service = bleServer->createService(SERVICE_UUID);
    
    // Créer la caractéristique pour les messages
    messageCharacteristic = service->createCharacteristic(
        MESSAGE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );
    
    // Démarrer le service
    service->start();
    
    isInitialized = true;
    return true;
}

void BluetoothMessageTransport::start() {
    if (isInitialized && !isStarted && bleServer) {
        // Démarrer l'advertising
        NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
        advertising->addServiceUUID(SERVICE_UUID);
        advertising->setScanResponse(true);
        advertising->setMinPreferred(0x06);
        advertising->setMaxPreferred(0x12);
        advertising->start();
        
        isStarted = true;
    }
}

void BluetoothMessageTransport::stop() {
    if (isStarted) {
        NimBLEDevice::getAdvertising()->stop();
        isStarted = false;
    }
    
    if (isInitialized) {
        NimBLEDevice::deinit(true);
        isInitialized = false;
    }
}

// Callbacks statiques
void BluetoothMessageTransport::onConnect(NimBLEServer* pServer) {
    Serial.println("🔗 Client connecté");
}

void BluetoothMessageTransport::onDisconnect(NimBLEServer* pServer) {
    Serial.println("🔌 Client déconnecté");
}
