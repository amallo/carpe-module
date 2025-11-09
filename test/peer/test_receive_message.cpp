#include "doctest/doctest.h"
#include "core/peer/protocol/MessageHeader.h"
#include "core/peer/protocol/UserMessageHeader.h"
#include "core/peer/protocol/decoders/MessageDecoder.h"
#include "core/peer/usecases/ReceiveMessageUseCase.h"
#include "test/transport/MockMessageGateway.h"
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

/**
 * @brief Tests pour la réception et le décodage de messages
 * 
 * Ces tests vérifient :
 * - Le décodage du header (TYPE + NONCE)
 * - La validation du header
 * - La gestion des messages invalides
 * - Le forwarding des messages valides
 */

namespace {
    /**
     * @brief Helper pour créer un champ fixe de 16 bytes avec padding null
     */
    std::vector<uint8_t> createFixedField16(const std::string& value) {
        std::vector<uint8_t> field(16, 0x00);
        size_t copyLength = std::min(value.size(), size_t(16));
        std::copy(value.begin(), value.begin() + copyLength, field.begin());
        return field;
    }
    
    /**
     * @brief Helper pour créer un champ CONTENT de 128 bytes avec padding null
     */
    std::vector<uint8_t> createContentField(const std::string& content) {
        std::vector<uint8_t> field(128, 0x00);
        size_t copyLength = std::min(content.size(), size_t(128));
        std::copy(content.begin(), content.begin() + copyLength, field.begin());
        return field;
    }
    
    /**
     * @brief Crée un USER_MESSAGE complet avec les paramètres donnés
     * @param nonce Nonce du message (2 bytes, big-endian)
     * @param senderId ID de l'expéditeur (sera padding à 16 bytes)
     * @param recipientId ID du destinataire (sera padding à 16 bytes, vide pour public)
     * @param sessionId ID de session (sera padding à 16 bytes)
     * @param content Contenu du message (sera padding à 128 bytes)
     * @return Vecteur de bytes représentant le message complet (179 bytes)
     */
    std::vector<uint8_t> createUserMessage(
        uint16_t nonce,
        const std::string& senderId,
        const std::string& recipientId,
        const std::string& sessionId,
        const std::string& content
    ) {
        std::vector<uint8_t> data;
        
        // Header: TYPE (1) + NONCE (2) + SENDER_ID (16) + RECIPIENT_ID (16) = 35 bytes
        data.push_back(0x07);  // TYPE = USER_MESSAGE
        data.push_back((nonce >> 8) & 0xFF);  // NONCE high byte (big-endian)
        data.push_back(nonce & 0xFF);          // NONCE low byte
        
        // SENDER_ID (16 bytes)
        std::vector<uint8_t> senderIdField = createFixedField16(senderId);
        data.insert(data.end(), senderIdField.begin(), senderIdField.end());
        
        // RECIPIENT_ID (16 bytes)
        std::vector<uint8_t> recipientIdField = createFixedField16(recipientId);
        data.insert(data.end(), recipientIdField.begin(), recipientIdField.end());
        
        // Payload: SESSION_ID (16) + CONTENT (128) = 144 bytes
        std::vector<uint8_t> sessionIdField = createFixedField16(sessionId);
        data.insert(data.end(), sessionIdField.begin(), sessionIdField.end());
        
        std::vector<uint8_t> contentField = createContentField(content);
        data.insert(data.end(), contentField.begin(), contentField.end());
        
        return data;  // Total: 35 + 144 = 179 bytes
    }
    
    /**
     * @brief Crée un USER_MESSAGE avec payload de taille incorrecte (pour les tests de validation)
     */
    std::vector<uint8_t> createUserMessageWithIncorrectPayloadSize(
        uint16_t nonce,
        const std::string& senderId,
        const std::string& recipientId,
        const std::string& sessionId,
        const std::string& content,
        size_t payloadSize  // Taille incorrecte du payload
    ) {
        std::vector<uint8_t> data;
        
        // Header: TYPE (1) + NONCE (2) + SENDER_ID (16) + RECIPIENT_ID (16) = 35 bytes
        data.push_back(0x07);  // TYPE = USER_MESSAGE
        data.push_back((nonce >> 8) & 0xFF);
        data.push_back(nonce & 0xFF);
        
        std::vector<uint8_t> senderIdField = createFixedField16(senderId);
        data.insert(data.end(), senderIdField.begin(), senderIdField.end());
        
        std::vector<uint8_t> recipientIdField = createFixedField16(recipientId);
        data.insert(data.end(), recipientIdField.begin(), recipientIdField.end());
        
        // Payload avec taille incorrecte
        std::vector<uint8_t> sessionIdField = createFixedField16(sessionId);
        data.insert(data.end(), sessionIdField.begin(), sessionIdField.end());
        
        // Ajouter le contenu et ajuster la taille
        std::vector<uint8_t> contentField = createContentField(content);
        size_t contentSize = payloadSize - 16;  // SESSION_ID fait 16 bytes
        if (contentSize > 128) contentSize = 128;
        if (contentSize < contentField.size()) {
            contentField.resize(contentSize);
        }
        data.insert(data.end(), contentField.begin(), contentField.end());
        
        return data;
    }
}

TEST_CASE("Should decode valid public message") {
    std::vector<uint8_t> data = createUserMessage(
        0x1234,           // NONCE
        "sender-1",       // SENDER_ID
        "",               // RECIPIENT_ID (vide = public)
        "session-1",      // SESSION_ID
        "hi"              // CONTENT
    );
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == true);
    
    // Le message doit être redirigé vers LoRa (pas vers Bluetooth)
    MessageInterface* message = loraGateway.getLastSentMessage();
    CHECK(message != nullptr);
    CHECK(message->getType() == 0x07);
    CHECK(message->getNonce() == 0x1234);
    CHECK(message->getPayloadSize() == 144);  // 16 (SESSION_ID) + 128 (CONTENT)
    
    // Vérifier SENDER_ID et RECIPIENT_ID
    std::vector<uint8_t> senderId = message->getSenderId();
    std::vector<uint8_t> recipientId = message->getRecipientId();
    CHECK(senderId.size() == 16);
    CHECK(recipientId.size() == 16);
    
    // Vérifier SENDER_ID="sender-1"
    auto senderIdEnd = std::find(senderId.begin(), senderId.end(), 0x00);
    std::string senderIdStr(senderId.begin(), senderIdEnd);
    CHECK(senderIdStr == "sender-1");
    
    // Vérifier RECIPIENT_ID est public (tous des 0x00)
    bool isPublic = true;
    for (size_t i = 0; i < 16; i++) {
        if (recipientId[i] != 0x00) {
            isPublic = false;
            break;
        }
    }
    CHECK(isPublic == true);
}

TEST_CASE("Should decode valid private message") {
    std::vector<uint8_t> data = createUserMessage(
        0x5678,           // NONCE
        "sender-1",       // SENDER_ID
        "recipient-1",    // RECIPIENT_ID (privé)
        "session-1",      // SESSION_ID
        "hi"              // CONTENT
    );
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == true);
    
    // Le message doit être redirigé vers LoRa (pas vers Bluetooth)
    MessageInterface* message = loraGateway.getLastSentMessage();
    CHECK(message != nullptr);
    CHECK(message->getType() == 0x07);
    CHECK(message->getNonce() == 0x5678);
    CHECK(message->getPayloadSize() == 144);  // 16 (SESSION_ID) + 128 (CONTENT)
    
    // Vérifier SENDER_ID et RECIPIENT_ID
    std::vector<uint8_t> senderId = message->getSenderId();
    std::vector<uint8_t> recipientId = message->getRecipientId();
    CHECK(senderId.size() == 16);
    CHECK(recipientId.size() == 16);
    
    // Vérifier SENDER_ID="sender-1"
    auto senderIdEnd = std::find(senderId.begin(), senderId.end(), 0x00);
    std::string senderIdStr(senderId.begin(), senderIdEnd);
    CHECK(senderIdStr == "sender-1");
    
    // Vérifier RECIPIENT_ID="recipient-1"
    auto recipientIdEnd = std::find(recipientId.begin(), recipientId.end(), 0x00);
    std::string recipientIdStr(recipientId.begin(), recipientIdEnd);
    CHECK(recipientIdStr == "recipient-1");
}

TEST_CASE("Should reject message that contains no payload") {
    // Message trop court: seulement 1 byte (TYPE), besoin de 35 bytes minimum pour USER_MESSAGE
    std::vector<uint8_t> data = {0x07};  // USER_MESSAGE type mais pas assez de données
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == false);
    
    // Aucun message ne doit être envoyé
    MessageInterface* message = loraGateway.getLastSentMessage();
    CHECK(message == nullptr);
    CHECK(bluetoothGateway.getLastSentMessage() == nullptr);
}

TEST_CASE("Should reject message with unknown type") {
    std::vector<uint8_t> data = {0x08, 0x12, 0x34};  // Type inconnu 0x08 avec nonce
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == false);
    
    // Aucun message ne doit être envoyé
    MessageInterface* message = loraGateway.getLastSentMessage();
    CHECK(message == nullptr);
    CHECK(bluetoothGateway.getLastSentMessage() == nullptr);
}

TEST_CASE("Should forward user message from bluetooth to lora") {
    std::vector<uint8_t> data = createUserMessage(
        0xABCD,           // NONCE
        "sender-1",       // SENDER_ID
        "",               // RECIPIENT_ID (vide = public)
        "session-1",      // SESSION_ID
        "hello"           // CONTENT
    );
    
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    // Exécuter le use case avec les données reçues depuis Bluetooth
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == true);
    
    // Vérifier que le message a été envoyé vers LoRa (pas vers Bluetooth)
    MessageInterface* messageInLoRa = loraGateway.getLastSentMessage();
    CHECK(messageInLoRa != nullptr);
    CHECK(messageInLoRa->getType() == 0x07);
    CHECK(messageInLoRa->getNonce() == 0xABCD);
    
    // Vérifier que rien n'a été envoyé vers Bluetooth
    MessageInterface* messageInBluetooth = bluetoothGateway.getLastSentMessage();
    CHECK(messageInBluetooth == nullptr);
}

TEST_CASE("Should forward user message from lora to bluetooth") {
    std::vector<uint8_t> data = createUserMessage(
        0xEF01,           // NONCE
        "sender-2",       // SENDER_ID
        "",               // RECIPIENT_ID (vide = public)
        "session-2",      // SESSION_ID
        "world"           // CONTENT
    );
    
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    // Exécuter le use case avec les données reçues depuis LoRa
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::LORA);
    CHECK(result == true);
    
    // Vérifier que le message a été envoyé vers Bluetooth (pas vers LoRa)
    MessageInterface* messageInBluetooth = bluetoothGateway.getLastSentMessage();
    CHECK(messageInBluetooth != nullptr);
    CHECK(messageInBluetooth->getType() == 0x07);
    CHECK(messageInBluetooth->getNonce() == 0xEF01);
    
    // Vérifier que rien n'a été envoyé vers LoRa
    MessageInterface* messageInLoRa = loraGateway.getLastSentMessage();
    CHECK(messageInLoRa == nullptr);
}

TEST_CASE("Should reject user message with incorrect payload size") {
    // USER_MESSAGE avec payload trop court (143 bytes au lieu de 144)
    std::vector<uint8_t> data = createUserMessageWithIncorrectPayloadSize(
        0x1234,           // NONCE
        "sender-1",       // SENDER_ID
        "",               // RECIPIENT_ID (vide = public)
        "session-1",      // SESSION_ID
        "hi",             // CONTENT
        143               // Payload size incorrect (au lieu de 144)
    );
    
    MessageDecoder decoder;
    MockMessageGateway bluetoothGateway;
    MockMessageGateway loraGateway;
    ReceiveMessageUseCase useCase(decoder, bluetoothGateway, loraGateway);
    
    bool result = useCase.execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
    CHECK(result == false);
    
    // Aucun message ne doit être envoyé
    MessageInterface* message = loraGateway.getLastSentMessage();
    CHECK(message == nullptr);
    CHECK(bluetoothGateway.getLastSentMessage() == nullptr);
}

