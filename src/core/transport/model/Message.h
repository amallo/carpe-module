#pragma once
#include <string>
#include <cstdint>

/**
 * @brief Interface de base pour les messages du protocole CARPE
 * Les clients définissent leur propre structure de données
 */
class Message {
public:
    std::string type;                    // Type de message ("auth_request", "auth_response", etc.)
    uint16_t nonce;                     // Valeur anti-replay (2 bytes)
    
    /**
     * @brief Constructeur principal
     * @param type Type de message (ex: "auth_request")
     * @param nonce Valeur anti-replay 16-bit
     */
    Message(const std::string& type, uint16_t nonce);
    
    /**
     * @brief Destructeur virtuel pour permettre l'héritage
     */
    virtual ~Message() = default;
    
    /**
     * @brief Vérifier si le message est valide
     * @return true si le message a un type non-vide
     */
    bool isValid() const;
};