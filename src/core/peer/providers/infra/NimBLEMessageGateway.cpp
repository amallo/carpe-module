#include "NimBLEMessageGateway.h"
#include <vector>

NimBLEMessageGateway::NimBLEMessageGateway() : characteristic(nullptr) {
}

void NimBLEMessageGateway::setCharacteristic(NimBLECharacteristic* characteristic) {
    this->characteristic = characteristic;
}

void NimBLEMessageGateway::send(const MessageInterface& message) {
    if (!characteristic) {
        return;
    }
    
    // Encoder le message et l'envoyer
    std::vector<uint8_t> data = message.encode();
    characteristic->setValue(data.data(), data.size());
    characteristic->notify();
}
