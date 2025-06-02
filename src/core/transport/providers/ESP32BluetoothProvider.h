#pragma once
#include "BluetoothProvider.h"
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLECharacteristic.h>
#include <NimBLEAdvertising.h>
#include <string>
#include <Arduino.h>

class ESP32BluetoothReceiveCallback;

/**
 * @brief Implémentation ESP32 du fournisseur BLE avec NimBLE
 */
class ESP32BluetoothProvider : public BluetoothProvider {
private:
    NimBLEServer* pServer;
    NimBLEService *pService;
    NimBLECharacteristic *pCharacteristic;
    bool isInitialized;
    
public:
    ESP32BluetoothProvider(NimBLEServer* pServer);
    virtual ~ESP32BluetoothProvider();
    
    bool init(const std::string& deviceId) override;
    bool start() override;
    bool sendString(const std::string& message) override;
    
    // Méthodes publiques spécifiques ESP32
    bool isConnected() override;
    bool isStarted() override;
    
    friend class ESP32BluetoothReceiveCallback;
}; 