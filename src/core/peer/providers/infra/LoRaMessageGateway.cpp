#include "LoRaMessageGateway.h"
#include <vector>

LoRaMessageGateway::LoRaMessageGateway() : initialized(false) {
}

bool LoRaMessageGateway::begin(long frequency, int nss, int rst, int dio0) {
    LoRa.setPins(nss, rst, dio0);
    if (!LoRa.begin(frequency)) {
        initialized = false;
        return false;
    }
    initialized = true;
    return true;
}

void LoRaMessageGateway::send(const MessageInterface& message) {
    if (!initialized) {
        return;
    }
    
    // Encoder le message
    std::vector<uint8_t> data = message.encode();
    
    // Envoyer via LoRa
    LoRa.beginPacket();
    LoRa.write(data.data(), data.size());
    LoRa.endPacket();
}

