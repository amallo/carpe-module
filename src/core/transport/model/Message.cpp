#include "Message.h"

Message::Message(const std::string& type, uint16_t nonce, const std::vector<uint8_t>& payload)
    : type(type), nonce(nonce), payload(payload) {
}

Message::Message() 
    : type(""), nonce(0), payload() {
}

bool Message::isValid() const {
    return !type.empty();
}

size_t Message::getPayloadSize() const {
    return payload.size();
}
