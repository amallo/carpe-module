#include "Esp32MessageTransport.h"
#include <Arduino.h>

Esp32MessageTransport::Esp32MessageTransport(const std::string& transportType) 
    : transportType(transportType), bluetoothSerial(nullptr), isInitialized(false), isStarted(false) {
}

void Esp32MessageTransport::send(const std::vector<uint8_t>& encodedMessage) {
    if (!isStarted || !bluetoothSerial) {
        return; // Bluetooth pas encore démarré
    }
    
    // Envoyer le message encodé via Bluetooth Serial
    bluetoothSerial->write(encodedMessage.data(), encodedMessage.size());
}

const std::string& Esp32MessageTransport::getTransportType() const {
    return transportType;
}

bool Esp32MessageTransport::init(const std::string& deviceName) {
    if (isInitialized) {
        return true;
    }
    
    // Initialiser Bluetooth Serial
    bluetoothSerial = new BluetoothSerial();
    if (!bluetoothSerial->begin(deviceName.c_str())) {
        delete bluetoothSerial;
        bluetoothSerial = nullptr;
        return false;
    }
    
    isInitialized = true;
    return true;
}

void Esp32MessageTransport::start() {
    if (isInitialized && !isStarted) {
        isStarted = true;
    }
}

void Esp32MessageTransport::stop() {
    if (isStarted && bluetoothSerial) {
        bluetoothSerial->end();
        delete bluetoothSerial;
        bluetoothSerial = nullptr;
        isStarted = false;
        isInitialized = false;
    }
}
