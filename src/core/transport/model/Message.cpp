#include "Message.h"

Message::Message(const std::string& type, uint16_t nonce)
    : type(type), nonce(nonce) {
}

bool Message::isValid() const {
    return !type.empty();
}

