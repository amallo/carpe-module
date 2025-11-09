#include "ReceiveMessageUseCase.h"
#include "core/peer/protocol/Message.h"

ReceiveMessageUseCase::ReceiveMessageUseCase(MessageDecoder& decoder, MessageGateway& bluetoothGateway, MessageGateway& loraGateway)
    : decoder(&decoder), bluetoothGateway(&bluetoothGateway), loraGateway(&loraGateway) {
}

ReceiveMessageUseCase::~ReceiveMessageUseCase() {
}

bool ReceiveMessageUseCase::execute(const std::vector<uint8_t>& data, Source source) {
    // 1. Décoder le message
    MessageInterface* message = decoder->decode(data);
    
    // 2. Valider le message
    if (message == nullptr) {
        return false;
    }
    
    // 3. Forward le message vers l'autre transport
    // Si reçu depuis Bluetooth → rediriger vers LoRa
    // Si reçu depuis LoRa → rediriger vers Bluetooth
    if (source == Source::BLUETOOTH) {
        loraGateway->send(*message);
    } else {
        bluetoothGateway->send(*message);
    }
    
    // Nettoyer la mémoire
    delete message;
    
    return true;
}

