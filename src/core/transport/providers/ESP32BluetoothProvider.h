#pragma once
#include "BluetoothProvider.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>



/**
 * @brief Implémentation ESP32 du fournisseur BLE
 */
class ESP32BluetoothProvider : public BluetoothProvider {
private:
    BLEServer* pServer;
    BLEService *pService;
    BLECharacteristic *pCharacteristic;
public:
    ESP32BluetoothProvider(BLEServer* pServer);
    virtual ~ESP32BluetoothProvider();
    
    bool init(const String& deviceId) override;
    bool start() override;
    bool sendString(const String& message) override;
    
    // Méthodes publiques spécifiques ESP32
    bool isConnected() override;
}; 