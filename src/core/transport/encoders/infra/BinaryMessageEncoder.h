#pragma once
#include "../MessageEncoder.h"
#include <map>
#include <cstdint>

/**
 * @brief Encodeur binaire implémentant le protocole CARPE v0
 * Conforme au format défini dans protocol.md
 */
class BinaryMessageEncoder : public MessageEncoder {
private:
    // Mapping des types de messages vers leurs codes
    static const std::map<std::string, uint8_t> messageTypeCodes;
    static const std::map<uint8_t, std::string> messageTypeNames;
    
public:
    BinaryMessageEncoder();
    virtual ~BinaryMessageEncoder() = default;
    
    // Interface MessageEncoder
    std::vector<uint8_t> encode(const Message& message) override;
    Message decode(const std::vector<uint8_t>& binary) override;
    
private:
    /**
     * @brief Obtenir le code numérique pour un type de message
     * @param type Le type de message (ex: "PAIR_REQUEST")
     * @return Le code sur 1 byte
     */
    uint8_t getTypeCode(const std::string& type) const;
    
    /**
     * @brief Obtenir le nom du type depuis un code
     * @param code Le code sur 1 byte
     * @return Le nom du type de message
     */
    std::string getTypeName(uint8_t code) const;
    
    /**
     * @brief Encoder un header selon le protocole
     * @param type Code du type de message
     * @param payloadLength Taille du payload
     * @param nonce Valeur anti-replay
     * @return Header de 6 bytes
     */
    std::vector<uint8_t> encodeHeader(uint8_t type, uint16_t payloadLength, uint16_t nonce) const;
    
    /**
     * @brief Décoder un header
     * @param header Données du header (6 bytes)
     * @param type [out] Type de message
     * @param length [out] Taille du payload
     * @param flags [out] Flags
     * @param nonce [out] Nonce
     * @return true si le décodage a réussi
     */
    bool decodeHeader(const std::vector<uint8_t>& header, uint8_t& type, uint16_t& length, uint8_t& flags, uint16_t& nonce) const;
};
