#include "MessageHeader.h"

MessageHeader::MessageHeader(const std::string& type, uint16_t nonce)
    : type(type), nonce(nonce) {
}

bool MessageHeader::isValid() const {
    return !type.empty();
}
