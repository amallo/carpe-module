#include "MockMessageGateway.h"
#include <iostream>

MockMessageGateway::MockMessageGateway(const std::string& transportType) 
    : transportType(transportType) {
}

void MockMessageGateway::send(const MessageInterface& message) {
    // Créer une copie du message avec unique_ptr
    sentMessages.push_back(std::unique_ptr<MessageInterface>(message.clone()));
}

bool MockMessageGateway::wasMessageSent(const MessageInterface& message) {
    for (const auto& sentMessage : sentMessages) {
        // Debug: afficher les nonces pour comprendre le problème
        std::cout << "DEBUG: Comparing sent message (nonce=" << sentMessage->getNonce() 
                  << ", type=" << sentMessage->getType() << ") with test message (nonce=" 
                  << message.getNonce() << ", type=" << message.getType() << ")" << std::endl;
        if (*sentMessage == message) {
            return true;
        }
    }
    return false;
}
