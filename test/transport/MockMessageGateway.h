#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/protocol/Message.h"
#include <string>
#include <vector>
#include <memory>

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
    std::vector<std::unique_ptr<MessageInterface>> sentMessages;
};
