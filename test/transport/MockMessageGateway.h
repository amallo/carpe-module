#pragma once
#include "core/peer/MessageGateway.h"
#include "core/peer/model/Message.h"
#include <string>
#include <vector>

/**
 * @brief Mock pour MessageGateway
 */
class MockMessageGateway : public MessageGateway {
public:
    explicit MockMessageGateway(const std::string& transportType);
    
    void send(Message* message) override;
    bool wasMessageSent(Message* message);
    
private:
    std::string transportType;
    std::vector<Message*> sentMessages;
};
