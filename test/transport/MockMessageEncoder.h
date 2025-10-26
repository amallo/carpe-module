#pragma once
#include "core/peer/encoders/MessageEncoder.h"
#include "core/peer/model/Message.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"
#include <vector>
#include <cstdint>
#include <string>

class MockMessageEncoder : public MessageEncoder {
public:
    MockMessageEncoder();
    
    // Implémentation générique pour n'importe quel type de message
    template<typename Payload>
    std::vector<uint8_t> encode(const Message<Payload>& message) const {
        // Pour les tests, on simule l'encodage
        std::vector<uint8_t> data;
        
        // Encoder le type
        const std::string& type = message.getType();
        if (!type.empty()) {
            data.push_back(static_cast<uint8_t>(type[0]));
        }
        
        // Encoder le nonce
        uint16_t nonce = message.getNonce();
        data.push_back((nonce >> 8) & 0xFF);
        data.push_back(nonce & 0xFF);
        
        // Pour InitiateAuthChallengeMessage, encoder le challengeId
        if (type == "auth_request") {
            // Cast vers InitiateAuthChallengeMessage pour accéder au challengeId
            const InitiateAuthChallengeMessage* authMessage = 
                dynamic_cast<const InitiateAuthChallengeMessage*>(&message);
            if (authMessage) {
                for (char c : authMessage->getChallengeId()) {
                    data.push_back(static_cast<uint8_t>(c));
                }
            }
        }
        
        return data;
    }
    
    // Méthodes d'assertion pour les tests
    bool wasEncodedWith(const std::string& type, uint16_t nonce) const;
    bool wasEncodedWith(const std::string& type, uint16_t nonce, const std::string& challengeId) const;
    bool wasEncodedWith(const InitiateAuthChallengeMessage& message) const;
    
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