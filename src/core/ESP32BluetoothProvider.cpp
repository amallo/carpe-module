#include "ESP32BluetoothProvider.h"

// UUIDs pour le service et la caractéristique BLE
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"


class ESP32BluetoothReceiveCallback: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.print("Received via BLE: ");
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }
    }
  }
};

ESP32BluetoothProvider::ESP32BluetoothProvider(BLEServer* pServer) 
    : pServer(pServer), pService(nullptr), pCharacteristic(nullptr) {
}

ESP32BluetoothProvider::~ESP32BluetoothProvider() {
    if (pServer && pServer->getAdvertising()) {
        pServer->getAdvertising()->stop();
    }
    BLEDevice::deinit(true);
}

bool ESP32BluetoothProvider::init(const String& deviceId) {
    
    // Initialiser le device BLE
    BLEDevice::init(deviceId.c_str());
    
    // Créer le serveur BLE
    pServer = BLEDevice::createServer();
    pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
    );
    pCharacteristic->setCallbacks(new ESP32BluetoothReceiveCallback());
    return true;
}

bool ESP32BluetoothProvider::isConnected() { return pServer->getConnectedCount() > 0; }


bool ESP32BluetoothProvider::start() {
    if (!pServer || !pService || !pCharacteristic) {
        Serial.println("ESP32BLE: Cannot start - not properly initialized. Did you call ESP32BLEProvider::init() ?");
        return false;
    }
    pService->start();
    
    // Démarrer l'advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->start();
    
    Serial.println("ESP32BLE: Service started and advertising");
    // Serial.print("ESP32BLE: Device name: ");
    // Serial.println(deviceId);
    
    return true;
}

bool ESP32BluetoothProvider::sendString(const String& message) {
    if (!pCharacteristic) {
        Serial.println("ESP32BLE: Cannot send - not properly initialized. Did you call ESP32BLEProvider::init() ?");
        return false;
    }
    pCharacteristic->setValue(message.c_str());
    pCharacteristic->notify();
    return true;
}
