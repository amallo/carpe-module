#include "ESP32MessageHeaderEncoder.h"
#include <cstring>

ESP32MessageHeaderEncoder::ESP32MessageHeaderEncoder() {
}

std::vector<uint8_t> ESP32MessageHeaderEncoder::encodeHeader(const MessageHeader& header) const {
    std::vector<uint8_t> encoded;
    
    // Encoder le type (1 byte)
    encoded.push_back(header.getType());
    
    // Encoder le nonce (2 bytes)
    std::vector<uint8_t> nonceBytes = encodeNonce(header.getNonce());
    encoded.insert(encoded.end(), nonceBytes.begin(), nonceBytes.end());
    
    return encoded;
}

std::vector<uint8_t> ESP32MessageHeaderEncoder::encodeNonce(uint16_t nonce) const {
    std::vector<uint8_t> encoded;
    
    // Nonce: 2 bytes (little-endian)
    encoded.push_back(nonce & 0xFF);        // Low byte
    encoded.push_back((nonce >> 8) & 0xFF); // High byte
    
    return encoded;
}
