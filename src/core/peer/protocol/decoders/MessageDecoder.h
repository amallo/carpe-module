#pragma once
#include "core/peer/protocol/Message.h"
#include <vector>
#include <memory>

/**
 * @brief Décodage de messages binaires
 */
class MessageDecoder {
public:
    /**
     * @brief Décode un message depuis des données binaires
     * @param data Données binaires complètes (HEADER + PAYLOAD)
     * @return MessageInterface* si valide, nullptr sinon
     */
    MessageInterface* decode(const std::vector<uint8_t>& data) const;
};

