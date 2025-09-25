#pragma once
#include "model/Message.h"
#include <vector>
#include <cstdint>

/**
 * @brief Interface pour l'encodage/décodage de messages
 * Abstraction permettant différentes implémentations d'encodage (binaire, JSON, etc.)
 */
class MessageEncoder {
public:
    virtual ~MessageEncoder() = default;
    
    /**
     * @brief Encoder un message en format binaire
     * @param message Le message à encoder
     * @return Les données binaires encodées
     */
    virtual std::vector<uint8_t> encode(const Message& message) = 0;
    
    /**
     * @brief Décoder des données binaires en message
     * @param binary Les données binaires à décoder
     * @return Le message décodé
     */
    virtual Message decode(const std::vector<uint8_t>& binary) = 0;
    
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    MessageEncoder() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    MessageEncoder(const MessageEncoder&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    MessageEncoder& operator=(const MessageEncoder&) = delete;
};
