#pragma once
#include "core/peer/protocol/MessageHeader.h"
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Interface de base pour tous les messages
 */
class MessageInterface {
public:
    virtual ~MessageInterface() = default;
    virtual std::vector<uint8_t> encode() const = 0;
    virtual uint8_t getType() const = 0;
    virtual uint16_t getNonce() const = 0;
    virtual size_t getPayloadSize() const = 0;
    virtual std::vector<uint8_t> getSenderId() const { return {}; }  // Par défaut vide, surchargé pour USER_MESSAGE
    virtual std::vector<uint8_t> getRecipientId() const { return {}; }  // Par défaut vide, surchargé pour USER_MESSAGE
    virtual bool operator==(const MessageInterface& other) const = 0;
    virtual MessageInterface* clone() const = 0;
};

/**
 * @brief Interface paramétrée pour les messages du protocole CARPE
 * @tparam Payload Type du payload du message
 */
template<typename Payload>
class Message : public MessageInterface {
public:
    /**
     * @brief Constructeur principal
     * @param header Header du message (TYPE byte + NONCE)
     * @param payload Données spécifiques du message
     */
    Message(const MessageHeader& header, const Payload& payload)
        : header(header), payload(payload) {}
    
    /**
     * @brief Destructeur virtuel pour permettre l'héritage
     */
    virtual ~Message() = default;
    
    /**
     * @brief Accès au header du message
     */
    const MessageHeader& getHeader() const {
        return header;
    }
    
    /**
     * @brief Accès au type du message (TYPE byte du protocole)
     */
    uint8_t getType() const override {
        return header.getType();
    }
    
    /**
     * @brief Accès au nonce du message
     */
    uint16_t getNonce() const override {
        return header.getNonce();
    }
    
    /**
     * @brief Taille du payload encodé (par défaut: taille totale - 3 bytes header)
     */
    size_t getPayloadSize() const override {
        auto encoded = encode();
        return encoded.size() >= 3 ? encoded.size() - 3 : 0;
    }
    
    /**
     * @brief Accès au payload du message
     */
    const Payload& getPayload() const {
        return payload;
    }
    
    /**
     * @brief Encoder le message complet (header + payload) en binaire
     * À implémenter par les classes dérivées (utilise l'encoder)
     */
    virtual std::vector<uint8_t> encode() const = 0;
    
    /**
     * @brief Cloner le message (à implémenter par les classes dérivées)
     */
    virtual MessageInterface* clone() const = 0;

    bool operator==(const MessageInterface& other) const override {
        return getType() == other.getType() && getNonce() == other.getNonce();
    }
    
    /**
     * @brief Header commun (type + nonce)
     */
    MessageHeader header;
    
    /**
     * @brief Données spécifiques du message
     */
    Payload payload;
};