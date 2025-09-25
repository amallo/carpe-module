#pragma once
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Modèle de message pour le protocole CARPE
 * Structure de données pure représentant un message du protocole binaire
 */
class Message {
public:
    std::string type;                    // Type de message ("PAIR_REQUEST", "PAIR_RESPONSE", etc.)
    uint16_t nonce;                     // Valeur anti-replay (2 bytes)
    std::vector<uint8_t> payload;       // Données binaires brutes du payload
    
    /**
     * @brief Constructeur principal
     * @param type Type de message (ex: "PAIR_REQUEST")
     * @param nonce Valeur anti-replay 16-bit
     * @param payload Données binaires du payload
     */
    Message(const std::string& type, uint16_t nonce, const std::vector<uint8_t>& payload);
    
    /**
     * @brief Constructeur par défaut
     */
    Message();
    
    /**
     * @brief Destructeur
     */
    ~Message() = default;
    
    /**
     * @brief Constructeur de copie
     */
    Message(const Message& other) = default;
    
    /**
     * @brief Opérateur d'assignation
     */
    Message& operator=(const Message& other) = default;
    
    /**
     * @brief Vérifier si le message est valide
     * @return true si le message a un type non-vide
     */
    bool isValid() const;
    
    /**
     * @brief Obtenir la taille du payload
     * @return Taille du payload en bytes
     */
    size_t getPayloadSize() const;
};
