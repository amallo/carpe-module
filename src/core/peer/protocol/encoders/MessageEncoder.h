#pragma once
#include "core/peer/protocol/Message.h"
#include "core/peer/protocol/MessageHeader.h"
#include <vector>
#include <cstdint>

/**
 * @brief Interface pour encoder un message en binaire
 */
class MessageEncoder {
public:
    virtual ~MessageEncoder() = default;
    
    /**
     * @brief Encode le message complet (header + payload) en binaire
     * @param message Le message à encoder
     * @return Vecteur de bytes encodé
     */
    virtual std::vector<uint8_t> encode(const MessageInterface& message) const = 0;
    
protected:
    /**
     * @brief Encode le MessageHeader en binaire (TYPE byte + NONCE)
     * @param header Le header à encoder
     * @return Header encodé (3 bytes)
     */
    std::vector<uint8_t> encodeHeader(const MessageHeader& header) const {
        std::vector<uint8_t> data;
        data.push_back(header.getType());
        data.push_back((header.getNonce() >> 8) & 0xFF);  // Big-endian
        data.push_back(header.getNonce() & 0xFF);
        return data;
    }
};
