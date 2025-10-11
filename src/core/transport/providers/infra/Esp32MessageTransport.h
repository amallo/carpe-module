#pragma once
#include "core/transport/MessageTransport.h"
#include <vector>
#include <cstdint>
#include <string>
#include <BluetoothSerial.h>

/**
 * @brief Implémentation ESP32 du transport de messages via Bluetooth
 * Utilise BluetoothSerial pour l'envoi de messages encodés
 */
class Esp32MessageTransport : public MessageTransport {
public:
    explicit Esp32MessageTransport(const std::string& transportType);
    
    void send(const std::vector<uint8_t>& encodedMessage) override;
    const std::string& getTransportType() const override;
    
    // Méthodes pour la configuration Bluetooth
    bool init(const std::string& deviceName);
    void start();
    void stop();
    
private:
    std::string transportType;
    BluetoothSerial* bluetoothSerial;
    bool isInitialized;
    bool isStarted;
};
