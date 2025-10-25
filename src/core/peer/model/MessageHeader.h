#pragma once
#include <string>
#include <cstdint>

/**
 * @brief Header commun à tous les messages du protocole CARPE
 * Contient les champs obligatoires : type et nonce
 */
class MessageHeader {
public:
    std::string type;                    // Type de message ("auth_request", "auth_response", etc.)
    uint16_t nonce;                      // Valeur anti-replay (2 bytes)
    
    /**
     * @brief Constructeur principal
     * @param type Type de message (ex: "auth_request")
     * @param nonce Valeur anti-replay 16-bit
     */
    MessageHeader(const std::string& type, uint16_t nonce);
    
    /**
     * @brief Constructeur par défaut
     */
    MessageHeader() = delete;
    
    /**
     * @brief Destructeur
     */
    ~MessageHeader() = default;
    
    /**
     * @brief Constructeur de copie
     */
    MessageHeader(const MessageHeader& other) = default;
    
    /**
     * @brief Opérateur d'assignation
     */
    MessageHeader& operator=(const MessageHeader& other) = default;
    
    /**
     * @brief Vérifier si le header est valide
     * @return true si le header a un type non-vide
     */
    bool isValid() const;
    
    /**
     * @brief Accès au type du message
     */
    const std::string& getType() const {
        return type;
    }
    
    /**
     * @brief Accès au nonce du message
     */
    uint16_t getNonce() const {
        return nonce;
    }
};
