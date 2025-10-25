#pragma once
#include <vector>
#include <cstdint>
#include "core/peer/model/Message.h"

/**
 * @brief Interface générique pour encoder n'importe quel type de message
 */
class MessageEncoder {
public:
    virtual ~MessageEncoder() = default;
    
    /**
     * @brief Encoder un message générique paramétré
     * @tparam Payload Type du payload du message
     * @param message Le message à encoder
     * @return Vecteur de bytes encodé
     */
    template<typename Payload>
    std::vector<uint8_t> encode(const Message<Payload>& message) const {
        // Implémentation par défaut qui utilise la méthode encode() du message
        return message.encode();
    }
};
