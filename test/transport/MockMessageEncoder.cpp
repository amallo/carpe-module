#include "MockMessageEncoder.h"

MockMessageEncoder::MockMessageEncoder() 
    : nextEncodedData(), nextDecodedMessage(), encodedMessages(), decodedBinary() {
}

std::vector<uint8_t> MockMessageEncoder::encode(const Message& message) {
    // Enregistrer le message dans l'historique
    encodedMessages.push_back(message);
    
    // Retourner les données pré-configurées
    return nextEncodedData;
}

Message MockMessageEncoder::decode(const std::vector<uint8_t>& binary) {
    // Enregistrer les données dans l'historique
    decodedBinary.push_back(binary);
    
    // Retourner le message pré-configuré
    return nextDecodedMessage;
}

void MockMessageEncoder::setNextEncodedData(const std::vector<uint8_t>& data) {
    nextEncodedData = data;
}

void MockMessageEncoder::setNextDecodedMessage(const Message& message) {
    nextDecodedMessage = message;
}

void MockMessageEncoder::scheduleEncode(const std::string& expectedString) {
    // Convertir le string en données binaires pour le retour
    nextEncodedData.assign(expectedString.begin(), expectedString.end());
}

bool MockMessageEncoder::wasMessageEncoded(const std::string& type, uint16_t nonce) const {
    for (const auto& msg : encodedMessages) {
        if (msg.type == type && msg.nonce == nonce) {
            return true;
        }
    }
    return false;
}

bool MockMessageEncoder::wasBinaryDecoded(const std::vector<uint8_t>& binary) const {
    for (const auto& data : decodedBinary) {
        if (data == binary) {
            return true;
        }
    }
    return false;
}

const std::vector<Message>& MockMessageEncoder::getEncodedMessages() const {
    return encodedMessages;
}

const std::vector<std::vector<uint8_t>>& MockMessageEncoder::getDecodedBinary() const {
    return decodedBinary;
}

void MockMessageEncoder::clearHistory() {
    encodedMessages.clear();
    decodedBinary.clear();
}
