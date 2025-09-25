#include "BinaryMessageEncoder.h"
#include <algorithm>

// Définition des mappings de types selon protocol.md
const std::map<std::string, uint8_t> BinaryMessageEncoder::messageTypeCodes = {
    {"PAIR_REQUEST", 0x01},
    {"PAIR_RESPONSE", 0x02}, 
    {"PAIR_CONFIRM", 0x03},
    {"AUTH_REQUEST", 0x01}  // Alias pour compatibilité avec les tests existants
};

const std::map<uint8_t, std::string> BinaryMessageEncoder::messageTypeNames = {
    {0x01, "PAIR_REQUEST"},
    {0x02, "PAIR_RESPONSE"},
    {0x03, "PAIR_CONFIRM"}
};

BinaryMessageEncoder::BinaryMessageEncoder() {
}

std::vector<uint8_t> BinaryMessageEncoder::encode(const Message& message) {
    // Obtenir le code du type de message
    uint8_t typeCode = getTypeCode(message.type);
    if (typeCode == 0) {
        // Type inconnu, retourner une séquence vide
        return {};
    }
    
    // Calculer la taille du payload
    uint16_t payloadLength = static_cast<uint16_t>(message.payload.size());
    
    // Encoder le header (6 bytes)
    auto header = encodeHeader(typeCode, payloadLength, message.nonce);
    
    // Construire le message final : HEADER + PAYLOAD
    std::vector<uint8_t> result;
    result.reserve(header.size() + message.payload.size());
    
    // Ajouter le header
    result.insert(result.end(), header.begin(), header.end());
    
    // Ajouter le payload
    result.insert(result.end(), message.payload.begin(), message.payload.end());
    
    return result;
}

Message BinaryMessageEncoder::decode(const std::vector<uint8_t>& binary) {
    // Vérifier la taille minimale (header = 6 bytes)
    if (binary.size() < 6) {
        return Message(); // Message invalide
    }
    
    // Extraire le header
    std::vector<uint8_t> headerData(binary.begin(), binary.begin() + 6);
    
    uint8_t type, flags;
    uint16_t length, nonce;
    
    if (!decodeHeader(headerData, type, length, flags, nonce)) {
        return Message(); // Header invalide
    }
    
    // Vérifier que la taille du message correspond
    if (binary.size() != 6 + length) {
        return Message(); // Taille incohérente
    }
    
    // Extraire le payload
    std::vector<uint8_t> payload;
    if (length > 0) {
        payload.assign(binary.begin() + 6, binary.end());
    }
    
    // Créer le message
    std::string typeName = getTypeName(type);
    return Message(typeName, nonce, payload);
}

uint8_t BinaryMessageEncoder::getTypeCode(const std::string& type) const {
    auto it = messageTypeCodes.find(type);
    return (it != messageTypeCodes.end()) ? it->second : 0;
}

std::string BinaryMessageEncoder::getTypeName(uint8_t code) const {
    auto it = messageTypeNames.find(code);
    return (it != messageTypeNames.end()) ? it->second : "";
}

std::vector<uint8_t> BinaryMessageEncoder::encodeHeader(uint8_t type, uint16_t payloadLength, uint16_t nonce) const {
    std::vector<uint8_t> header(6);
    
    // TYPE (1 byte)
    header[0] = type;
    
    // LENGTH (2 bytes, big-endian)
    header[1] = static_cast<uint8_t>((payloadLength >> 8) & 0xFF);
    header[2] = static_cast<uint8_t>(payloadLength & 0xFF);
    
    // FLAGS (1 byte) - 0x00 en v0
    header[3] = 0x00;
    
    // NONCE (2 bytes, big-endian)
    header[4] = static_cast<uint8_t>((nonce >> 8) & 0xFF);
    header[5] = static_cast<uint8_t>(nonce & 0xFF);
    
    return header;
}

bool BinaryMessageEncoder::decodeHeader(const std::vector<uint8_t>& header, uint8_t& type, uint16_t& length, uint8_t& flags, uint16_t& nonce) const {
    if (header.size() != 6) {
        return false;
    }
    
    // TYPE (1 byte)
    type = header[0];
    
    // LENGTH (2 bytes, big-endian)
    length = static_cast<uint16_t>((header[1] << 8) | header[2]);
    
    // FLAGS (1 byte)
    flags = header[3];
    
    // NONCE (2 bytes, big-endian)
    nonce = static_cast<uint16_t>((header[4] << 8) | header[5]);
    
    return true;
}
