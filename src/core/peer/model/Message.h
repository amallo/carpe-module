#pragma once
#include "MessageHeader.h"

/**
 * @brief Interface de base pour les messages du protocole CARPE
 * Les clients définissent leur propre structure de données
 */
class Message {
public:
    MessageHeader header;               // Header commun (type + nonce)
    
    /**
     * @brief Constructeur principal
     * @param type Type de message (ex: "auth_request")
     * @param nonce Valeur anti-replay 16-bit
     */
    Message(const std::string& type, uint16_t nonce);
    
    /**
     * @brief Constructeur avec MessageHeader
     * @param header Header du message
     */
    Message(const MessageHeader& header);
    
    /**
     * @brief Destructeur virtuel pour permettre l'héritage
     */
    virtual ~Message() = default;
    
    /**
     * @brief Vérifier si le message est valide
     * @return true si le message a un header valide
     */
    bool isValid() const;
    
    /**
     * @brief Accès direct au type (pour compatibilité)
     */
    const std::string& getType() const;
    
    /**
     * @brief Accès direct au nonce (pour compatibilité)
     */
    uint16_t getNonce() const;
};