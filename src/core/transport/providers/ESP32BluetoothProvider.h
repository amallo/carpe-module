#pragma once
#include "BluetoothProvider.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLECharacteristic.h>
#include <BLEAdvertising.h>
#include <string>
#include <Arduino.h>

class ESP32BluetoothReceiveCallback;

/**
 * @brief Implémentation ESP32 du fournisseur BLE
 */
class ESP32BluetoothProvider : public BluetoothProvider {
private:
    BLEServer* pServer;
    BLEService *pService;
    BLECharacteristic *pCharacteristic;
    bool isInitialized;
    
public:
    ESP32BluetoothProvider(BLEServer* pServer);
    virtual ~ESP32BluetoothProvider();
    
    bool init(const std::string& deviceId) override;
    bool start() override;
    bool sendString(const std::string& message) override;
    
    // Méthodes publiques spécifiques ESP32
    bool isConnected() override;
    bool isStarted() override;
    
    friend class ESP32BluetoothReceiveCallback;
}; 