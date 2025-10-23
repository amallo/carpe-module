#pragma once
#include "core/transport/MessageTransport.h"
#include <vector>
#include <cstdint>
#include <string>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLECharacteristic.h>

/**
 * @brief Implémentation Bluetooth du transport de messages via NimBLE
 * Utilise NimBLE pour l'envoi de messages encodés
 */
class BluetoothMessageTransport : public MessageTransport {
public:
    explicit BluetoothMessageTransport(const std::string& transportType);
    ~BluetoothMessageTransport();
    
    void send(const std::vector<uint8_t>& encodedMessage) override;
    const std::string& getTransportType() const override;
    
    // Méthodes pour la configuration Bluetooth
    bool init(const std::string& deviceName);
    void start();
    void stop();
    
private:
    std::string transportType;
    std::string deviceName;
    bool isInitialized;
    bool isStarted;
    
    // NimBLE components
    NimBLEServer* bleServer;
    NimBLECharacteristic* messageCharacteristic;
    
    // Callback pour les connexions
    static void onConnect(NimBLEServer* pServer);
    static void onDisconnect(NimBLEServer* pServer);
};
