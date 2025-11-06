#include "MockMessageEncoder.h"
#include "core/peer/protocol/messages/InitiateAuthChallengeMessage.h"
#include <cstring>

MockMessageEncoder::MockMessageEncoder() : currentResultIndex(0) {
}

std::vector<uint8_t> MockMessageEncoder::encode(const MessageInterface& message) const {
    // Utiliser la méthode encode() du message directement
    return message.encode();
}

bool MockMessageEncoder::wasEncodedWith(const std::string& type, uint16_t nonce) const {
    for (size_t i = 0; i < encodedTypes.size(); i++) {
        if (encodedTypes[i] == type && encodedNonces[i] == nonce) {
            return true;
        }
    }
    return false;
}

bool MockMessageEncoder::wasEncodedWith(const std::string& type, uint16_t nonce, const std::string& challengeId) const {
    for (size_t i = 0; i < encodedTypes.size(); i++) {
        if (encodedTypes[i] == type && encodedNonces[i] == nonce && encodedChallengeIds[i] == challengeId) {
            return true;
        }
    }
    return false;
}

bool MockMessageEncoder::wasEncodedWith(const InitiateAuthChallengeMessage& message) const {
    // getType() retourne maintenant uint8_t, pas string - cette méthode n'est plus utilisée
    // TODO: Adapter ou supprimer si plus nécessaire
    return false;
}

void MockMessageEncoder::scheduleEncodedResult(const std::vector<uint8_t>& result) {
    scheduledResults.push_back(result);
}

void MockMessageEncoder::scheduleEncodedResult(const std::string& type, uint16_t nonce, const std::string& challengeId) {
    std::vector<uint8_t> result = createEncodedMessage(type, nonce, challengeId);
    scheduledResults.push_back(result);
}

std::vector<uint8_t> MockMessageEncoder::createEncodedMessage(const std::string& type, uint16_t nonce, const std::string& challengeId) const {
    std::vector<uint8_t> encoded;
    
    // Header: type (4 bytes) + nonce (2 bytes)
    // Type: 4 bytes (padded with nulls if shorter)
    std::string typePadded = type;
    typePadded.resize(4, '\0');  // Pad to 4 bytes
    encoded.insert(encoded.end(), typePadded.begin(), typePadded.end());
    
    // Nonce: 2 bytes (little-endian)
    encoded.push_back(nonce & 0xFF);        // Low byte
    encoded.push_back((nonce >> 8) & 0xFF); // High byte
    
    // Ajouter le challengeId si c'est un AuthRequestMessage
    if (!challengeId.empty()) {
        encoded.insert(encoded.end(), challengeId.begin(), challengeId.end());
    }
    
    return encoded;
}

void MockMessageEncoder::reset() {
    encodedTypes.clear();
    encodedNonces.clear();
    encodedChallengeIds.clear();
    scheduledResults.clear();
    currentResultIndex = 0;
}