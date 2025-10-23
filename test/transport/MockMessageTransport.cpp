#include "MockMessageTransport.h"

MockMessageTransport::MockMessageTransport(const std::string& transportType) 
    : transportType(transportType) {
}

void MockMessageTransport::send(const std::vector<uint8_t>& encodedMessage) {
    sentMessages.push_back(encodedMessage);
    
    // Pour simplifier les tests, on extrait le challengeId du message encodé
    // Format: [type(4)][nonce(2)][challengeId...]
    if (encodedMessage.size() > 6) {
        std::string challengeId(encodedMessage.begin() + 6, encodedMessage.end());
        sentChallengeIds.push_back(challengeId);
    }
}

const std::string& MockMessageTransport::getTransportType() const {
    return transportType;
}

bool MockMessageTransport::wasMessageSent(const InitiateAuthChallengeMessage& message) const {
    // Vérifier si le challengeId a été envoyé
    std::string challengeId = message.getChallengeId();
    for (const auto& sentChallengeId : sentChallengeIds) {
        if (sentChallengeId == challengeId) {
            return true;
        }
    }
    return false;
}

bool MockMessageTransport::wasMessageSent(const Message& message) const {
    // Vérifier si le type de message est dans les messages encodés
    for (const auto& sentMessage : sentMessages) {
        // Les 4 premiers bytes contiennent le type
        if (sentMessage.size() >= 4) {
            std::string type(sentMessage.begin(), sentMessage.begin() + 4);
            if (type.find(message.getType()) != std::string::npos) {
                return true;
            }
        }
    }
    return false;
}

const std::vector<std::vector<uint8_t>>& MockMessageTransport::getSentMessages() const {
    return sentMessages;
}

void MockMessageTransport::reset() {
    sentMessages.clear();
    sentChallengeIds.clear();
}
