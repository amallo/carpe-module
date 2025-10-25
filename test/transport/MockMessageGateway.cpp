#include "MockMessageGateway.h"

MockMessageGateway::MockMessageGateway(const std::string& transportType) 
    : transportType(transportType) {
}

void MockMessageGateway::send(const MessageInterface& message) {
    sentMessages.push_back(SentMessageInfo(message.getType(), message.getNonce()));
}

bool MockMessageGateway::wasMessageSent(const MessageInterface& message) {
    for (const SentMessageInfo& sentMessage : sentMessages) {
        if (sentMessage.type == message.getType() && 
            sentMessage.nonce == message.getNonce()) {
            return true;
        }
    }
    return false;
}
