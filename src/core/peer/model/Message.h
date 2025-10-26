#pragma once
#include "MessageHeader.h"
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
    virtual const std::string& getType() const = 0;
    virtual uint16_t getNonce() const = 0;
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
     * @param type Type de message (ex: "auth_request")
     * @param nonce Valeur anti-replay 16-bit
     * @param payload Données spécifiques du message
     */
    Message(const std::string& type, uint16_t nonce, const Payload& payload)
        : header(type, nonce), payload(payload) {}
    
    /**
     * @brief Destructeur virtuel pour permettre l'héritage
     */
    virtual ~Message() = default;
    
    /**
     * @brief Vérifier si le message est valide
     * @return true si le message a un header valide
     */
    bool isValid() const {
        return header.isValid();
    }
    
    /**
     * @brief Accès au type du message
     */
    const std::string& getType() const {
        return header.getType();
    }
    
    /**
     * @brief Accès au nonce du message
     */
    uint16_t getNonce() const {
        return header.getNonce();
    }
    
    /**
     * @brief Accès au payload du message
     */
    const Payload& getPayload() const {
        return payload;
    }
    
    /**
     * @brief Encoder le message en bytes (à implémenter par les classes dérivées)
     */
    virtual std::vector<uint8_t> encode() const = 0;
    
    /**
     * @brief Cloner le message (à implémenter par les classes dérivées)
     */
    virtual MessageInterface* clone() const = 0;

    virtual bool operator==(const MessageInterface& other) const {
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