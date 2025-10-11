#include "MockAuthMessageEncoder.h"
#include "core/transport/model/AuthRequestMessage.h"
#include <cstring>

MockAuthMessageEncoder::MockAuthMessageEncoder() : currentResultIndex(0) {
}

std::vector<uint8_t> MockAuthMessageEncoder::encode(const AuthRequestMessage& message) const {
    // Enregistrer les paramètres pour les assertions
    encodedTypes.push_back(message.getType());
    encodedNonces.push_back(message.getNonce());
    encodedChallengeIds.push_back(message.getChallengeId());
    
    // Encoder directement l'AuthRequestMessage
    return createEncodedMessage(message.getType(), message.getNonce(), message.getChallengeId());
}

bool MockAuthMessageEncoder::wasEncodedWith(const std::string& type, uint16_t nonce) const {
    for (size_t i = 0; i < encodedTypes.size(); i++) {
        if (encodedTypes[i] == type && encodedNonces[i] == nonce) {
            return true;
        }
    }
    return false;
}

bool MockAuthMessageEncoder::wasEncodedWith(const std::string& type, uint16_t nonce, const std::string& challengeId) const {
    for (size_t i = 0; i < encodedTypes.size(); i++) {
        if (encodedTypes[i] == type && encodedNonces[i] == nonce && encodedChallengeIds[i] == challengeId) {
            return true;
        }
    }
    return false;
}

bool MockAuthMessageEncoder::wasEncodedWith(const AuthRequestMessage& message) const {
    return wasEncodedWith(message.getType(), message.getNonce(), message.getChallengeId());
}

void MockAuthMessageEncoder::scheduleEncodedResult(const std::vector<uint8_t>& result) {
    scheduledResults.push_back(result);
}

void MockAuthMessageEncoder::scheduleEncodedResult(const std::string& type, uint16_t nonce, const std::string& challengeId) {
    std::vector<uint8_t> result = createEncodedMessage(type, nonce, challengeId);
    scheduledResults.push_back(result);
}

std::vector<uint8_t> MockAuthMessageEncoder::createEncodedMessage(const std::string& type, uint16_t nonce, const std::string& challengeId) const {
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

void MockAuthMessageEncoder::reset() {
    encodedTypes.clear();
    encodedNonces.clear();
    encodedChallengeIds.clear();
    scheduledResults.clear();
    currentResultIndex = 0;
}