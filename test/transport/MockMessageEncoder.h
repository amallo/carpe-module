#pragma once
#include <core/transport/encoders/MessageEncoder.h>
#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief Mock pour tester l'encodage/décodage de messages
 * Permet de simuler le comportement d'un encoder sans implémentation réelle
 */
class MockMessageEncoder : public MessageEncoder {
private:
    std::vector<uint8_t> nextEncodedData;    // Données à retourner lors du prochain encode()
    Message nextDecodedMessage;              // Message à retourner lors du prochain decode()
    std::vector<Message> encodedMessages;    // Historique des messages encodés
    std::vector<std::vector<uint8_t>> decodedBinary; // Historique des données décodées
    
public:
    MockMessageEncoder();
    
    // Interface MessageEncoder
    std::vector<uint8_t> encode(const Message& message) override;
    Message decode(const std::vector<uint8_t>& binary) override;
    
    // Méthodes de configuration pour les tests
    void setNextEncodedData(const std::vector<uint8_t>& data);
    void setNextDecodedMessage(const Message& message);
    void scheduleEncode(const std::string& expectedString);
    
    // Méthodes d'inspection pour les tests
    bool wasMessageEncoded(const std::string& type, uint16_t nonce) const;
    bool wasBinaryDecoded(const std::vector<uint8_t>& binary) const;
    const std::vector<Message>& getEncodedMessages() const;
    const std::vector<std::vector<uint8_t>>& getDecodedBinary() const;
    void clearHistory();
};
