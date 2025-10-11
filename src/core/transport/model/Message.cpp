#include "Message.h"

Message::Message(const std::string& type, uint16_t nonce)
    : header(type, nonce) {
}

Message::Message(const MessageHeader& header)
    : header(header) {
}

bool Message::isValid() const {
    return header.isValid();
}

const std::string& Message::getType() const {
    return header.type;
}

uint16_t Message::getNonce() const {
    return header.nonce;
}

