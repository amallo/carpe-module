#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/protocol/Message.h"
#include <vector>
#include <memory>

/**
 * @brief Mock pour MessageGateway
 */
class MockMessageGateway : public MessageGateway {
public:
    MockMessageGateway();
    
    void send(const MessageInterface& message) override;
    bool wasMessageSent(const MessageInterface& message);
    MessageInterface* getLastSentMessage() const;
    
private:
    std::vector<std::unique_ptr<MessageInterface>> sentMessages;
};
