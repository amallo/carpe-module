#include "MessageRouter.h"
#include "providers/BluetoothProvider.h"
#include "MessageEncoder.h"

MessageRouter::MessageRouter(MessageEncoder* encoder) 
    : bluetoothProvider(nullptr), messageEncoder(encoder) {
    // Future: loraProvider(nullptr)
}

void MessageRouter::setBluetoothProvider(BluetoothProvider* provider) {
    bluetoothProvider = provider;
}

bool MessageRouter::routeMessage(const Message& message, const std::string& targetProtocol) {
    if (targetProtocol == "bluetooth") {
        if (bluetoothProvider && messageEncoder) {
            // Encoder le message en binaire
            auto binaryData = messageEncoder->encode(message);
            // Envoyer via le provider
            bool result = bluetoothProvider->sendBinary(binaryData.data(), binaryData.size());
            return result;
        } else {
            // Debug: pas de provider bluetooth ou encoder configuré
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

