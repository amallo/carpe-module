#include "UserMessageHeader.h"
#include <algorithm>

UserMessageHeader::UserMessageHeader(const std::vector<uint8_t>& senderId, 
                                     const std::vector<uint8_t>& recipientId,
                                     const MessageHeader& header)
    : header(header) {
    // Normaliser SENDER_ID à 16 bytes (null-padded)
    this->senderId.resize(16, 0);
    size_t copyLength = std::min(senderId.size(), size_t(16));
    std::copy(senderId.begin(), senderId.begin() + copyLength, this->senderId.begin());
    
    // Normaliser RECIPIENT_ID à 16 bytes (null-padded)
    this->recipientId.resize(16, 0);
    copyLength = std::min(recipientId.size(), size_t(16));
    std::copy(recipientId.begin(), recipientId.begin() + copyLength, this->recipientId.begin());
}

std::vector<uint8_t> UserMessageHeader::encode() const {
    std::vector<uint8_t> data;
    
    // Encoder le header de base (TYPE + NONCE)
    auto headerData = header.encode();
    data.insert(data.end(), headerData.begin(), headerData.end());
    
    // Ajouter SENDER_ID (16 bytes)
    data.insert(data.end(), senderId.begin(), senderId.end());
    
    // Ajouter RECIPIENT_ID (16 bytes)
    data.insert(data.end(), recipientId.begin(), recipientId.end());
    
    return data;  // Total: 35 bytes
}

