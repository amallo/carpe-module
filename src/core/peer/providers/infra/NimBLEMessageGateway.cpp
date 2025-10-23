#include "NimBLEMessageGateway.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"
#include <vector>

NimBLEMessageGateway::NimBLEMessageGateway() : characteristic(nullptr) {
}

void NimBLEMessageGateway::setCharacteristic(NimBLECharacteristic* characteristic) {
    this->characteristic = characteristic;
}

void NimBLEMessageGateway::send(Message* message) {
    if (!characteristic) {
        delete message;
        return;
    }
    
    // Convertir le message en bytes pour l'envoi BLE
    std::vector<uint8_t> data;
    
    // Encoder le type (1 byte)
    const std::string& type = message->getType();
    if (!type.empty()) {
        data.push_back(static_cast<uint8_t>(type[0])); // Premier caractère du type
    }
    
    // Encoder le nonce (2 bytes)
    uint16_t nonce = message->getNonce();
    data.push_back((nonce >> 8) & 0xFF);
    data.push_back(nonce & 0xFF);
    
    // Si c'est un InitiateAuthChallengeMessage, encoder le challengeId
    // Utiliser une approche sans RTTI
    InitiateAuthChallengeMessage* authMessage = static_cast<InitiateAuthChallengeMessage*>(message);
    if (authMessage) {
        const std::string& challengeId = authMessage->getChallengeId();
        for (char c : challengeId) {
            data.push_back(static_cast<uint8_t>(c));
        }
    }
    
    // Envoyer via BLE
    characteristic->setValue(data.data(), data.size());
    characteristic->notify();
    
    delete message;
}
