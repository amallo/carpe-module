#include "MockMessageTransport.h"

MockMessageTransport::MockMessageTransport(const std::string& transportType) 
    : transportType(transportType) {
}

void MockMessageTransport::send(const std::string& message) {
    sentMessages.push_back(message);
}

const std::string& MockMessageTransport::getTransportType() const {
    return transportType;
}

bool MockMessageTransport::wasMessageSent(const AuthRequestMessage& message) const {
    // Vérifier si le challengeId est dans les messages envoyés
    for (const auto& sentMessage : sentMessages) {
        if (sentMessage.find(message.getChallengeId()) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool MockMessageTransport::wasMessageSent(const Message& message) const {
    // Vérifier si le type de message est dans les messages envoyés
    for (const auto& sentMessage : sentMessages) {
        if (sentMessage.find(message.type) != std::string::npos) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string>& MockMessageTransport::getSentMessages() const {
    return sentMessages;
}

void MockMessageTransport::reset() {
    sentMessages.clear();
}
