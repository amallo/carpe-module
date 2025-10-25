#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/model/Message.h"
#include <string>
#include <vector>

/**
 * @brief Structure pour stocker les informations d'un message envoyé
 */
struct SentMessageInfo {
    std::string type;
    uint16_t nonce;
    
    SentMessageInfo(const std::string& type, uint16_t nonce) 
        : type(type), nonce(nonce) {}
};

/**
 * @brief Mock pour MessageGateway
 */
class MockMessageGateway : public MessageGateway {
public:
    explicit MockMessageGateway(const std::string& transportType);
    
    void send(const MessageInterface& message) override;
    bool wasMessageSent(const MessageInterface& message);
    
private:
    std::string transportType;
    std::vector<SentMessageInfo> sentMessages;
};
