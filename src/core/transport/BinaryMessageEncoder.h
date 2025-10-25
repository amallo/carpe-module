#pragma once
#include "MessageEncoder.h"
#include "core/peer/model/Message.h"
#include <vector>
#include <cstdint>

/**
 * @brief Encoder binaire pour les messages du protocole CARPE
 * Implémente l'encodage binaire standard pour tous les types de messages
 */
class BinaryMessageEncoder : public MessageEncoder {
public:
    BinaryMessageEncoder();
    virtual ~BinaryMessageEncoder() = default;
    
    /**
     * @brief Encoder un message générique en binaire
     * @tparam Payload Type du payload du message
     * @param message Le message à encoder
     * @return Vecteur de bytes encodé selon le protocole CARPE
     */
    template<typename Payload>
    std::vector<uint8_t> encode(const Message<Payload>& message) const {
        std::vector<uint8_t> data;
        
        // 1. Encoder le type (1 byte pour le premier caractère)
        const std::string& type = message.getType();
        if (!type.empty()) {
            data.push_back(static_cast<uint8_t>(type[0]));
        }
        
        // 2. Encoder le nonce (2 bytes, big-endian)
        uint16_t nonce = message.getNonce();
        data.push_back((nonce >> 8) & 0xFF);
        data.push_back(nonce & 0xFF);
        
        // 3. Encoder le payload spécifique
        encodePayload(message.getPayload(), data);
        
        return data;
    }
    
private:
    /**
     * @brief Encoder le payload générique en binaire
     * @tparam Payload Type du payload
     * @param payload Le payload à encoder
     * @param data Vecteur de données où ajouter les bytes encodés
     */
    template<typename Payload>
    void encodePayload(const Payload& payload, std::vector<uint8_t>& data) const {
        // Sérialisation générique : utiliser la représentation mémoire
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&payload);
        data.insert(data.end(), bytes, bytes + sizeof(Payload));
    }
};
