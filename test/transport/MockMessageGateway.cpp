#include "MockMessageGateway.h"

MockMessageGateway::MockMessageGateway(const std::string& transportType) 
    : transportType(transportType) {
}

void MockMessageGateway::send(Message* message) {
    sentMessages.push_back(message);
}

bool MockMessageGateway::wasMessageSent(Message* message) {
    for (auto* sentMessage : sentMessages) {
        if (sentMessage->getType() == message->getType() && 
            sentMessage->getNonce() == message->getNonce()) {
            return true;
        }
    }
    return false;
}
