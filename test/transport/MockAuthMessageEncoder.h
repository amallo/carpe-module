#pragma once
#include "core/transport/AuthMessageEncoder.h"
#include "core/transport/model/Message.h"
#include "core/transport/model/AuthRequestMessage.h"
#include <vector>
#include <cstdint>
#include <string>

class MockAuthMessageEncoder : public AuthMessageEncoder {
public:
    MockAuthMessageEncoder();
    
    std::vector<uint8_t> encode(const Message& message) const override;
    
    // Méthodes d'assertion pour les tests
    bool wasEncodedWith(const std::string& type, uint16_t nonce) const;
    bool wasEncodedWith(const std::string& type, uint16_t nonce, const std::string& challengeId) const;
    bool wasEncodedWith(const AuthRequestMessage& message) const;
    
    // Méthodes pour piloter le comportement
    void scheduleEncodedResult(const std::vector<uint8_t>& result);
    void scheduleEncodedResult(const std::string& type, uint16_t nonce, const std::string& challengeId);
    
    void reset();
    
private:
    std::vector<uint8_t> createEncodedMessage(const std::string& type, uint16_t nonce, const std::string& challengeId) const;
    
    // État pour les assertions
    mutable std::vector<std::string> encodedTypes;
    mutable std::vector<uint16_t> encodedNonces;
    mutable std::vector<std::string> encodedChallengeIds;
    
    // État pour piloter le comportement
    std::vector<std::vector<uint8_t>> scheduledResults;
    mutable int currentResultIndex;
};