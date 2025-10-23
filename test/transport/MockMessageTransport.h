#pragma once
#include <vector>
#include <string>
#include "core/transport/MessageTransport.h"
#include "core/peer/model/Message.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

class MockMessageTransport : public MessageTransport {
public:
    explicit MockMessageTransport(const std::string& transportType);
    
    void send(const std::vector<uint8_t>& encodedMessage) override;
    const std::string& getTransportType() const override;
    
    bool wasMessageSent(const InitiateAuthChallengeMessage& message) const;
    bool wasMessageSent(const Message& message) const;
    const std::vector<std::vector<uint8_t>>& getSentMessages() const;
    void reset();
    
private:
    std::string transportType;
    std::vector<std::vector<uint8_t>> sentMessages;
    std::vector<std::string> sentChallengeIds;  // Pour faciliter les tests
};
