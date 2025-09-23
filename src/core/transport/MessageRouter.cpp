#include "MessageRouter.h"
#include "providers/BluetoothProvider.h"

MessageRouter::MessageRouter() 
    : bluetoothProvider(nullptr) {
    // Future: loraProvider(nullptr)
}

void MessageRouter::setBluetoothProvider(BluetoothProvider* provider) {
    bluetoothProvider = provider;
}

bool MessageRouter::routeMessage(const std::vector<uint8_t>& message, const std::string& targetProtocol) {
    if (targetProtocol == "bluetooth") {
        if (bluetoothProvider) {
            if (bluetoothProvider->isConnected()) {
                bool result = bluetoothProvider->sendBinary(message.data(), message.size());
                return result;
            } else {
                // Debug: provider non connecté
                return false;
            }
        } else {
            // Debug: pas de provider bluetooth configuré
            return false;
        }
    }
    // Future: support pour LoRa
    // else if (targetProtocol == "lora") {
    //     if (loraProvider && loraProvider->isConnected()) {
    //         return loraProvider->sendBinary(message.data(), message.size());
    //     }
    //     return false;
    // }
    
    return false; // Protocole non supporté
}

