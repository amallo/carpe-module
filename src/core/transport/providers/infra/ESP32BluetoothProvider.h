#pragma once
#include "../BluetoothProvider.h"
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLECharacteristic.h>
#include <NimBLEAdvertising.h>
#include <core/logging/providers/infra/SerialLogger.h>
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
    SerialLogger* logger;
    BluetoothConnectionCallback* connectionCallback;
    BluetoothReceivedMessageCallback* receivedMessageCallback;
    bool isInitialized;
    
public:
    ESP32BluetoothProvider(SerialLogger* logger);
    virtual ~ESP32BluetoothProvider();
    
    bool init(const std::string& deviceId) override;
    bool start() override;
    bool sendBinary(const uint8_t* data, size_t length) override;
    
    // Méthodes publiques spécifiques ESP32
    bool isConnected() override;
    bool isStarted() override;
    
    // Gestion des callbacks de connexion
    void setConnectionCallback(BluetoothConnectionCallback* callback) override;
    void setReceivedMessageCallback(BluetoothReceivedMessageCallback* callback);
    
    // Getter pour le logger (pour les callbacks)
    SerialLogger* getLogger() const { return logger; }
    
    // Méthodes internes pour les callbacks (appelées par les classes internes)
    void handleDeviceConnected(const std::string& deviceAddress);
    void handleDeviceDisconnected(const std::string& deviceAddress);
    void handleReceivedMessage(const std::string& message);
    
    friend class ESP32BluetoothReceiveCallback;
}; 