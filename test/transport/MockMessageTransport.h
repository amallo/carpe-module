#pragma once
#include <vector>
#include <string>
#include "core/transport/MessageTransport.h"
#include "core/transport/model/Message.h"
#include "core/transport/model/AuthRequestMessage.h"

class MockMessageTransport : public MessageTransport {
public:
    explicit MockMessageTransport(const std::string& transportType);
    
    void send(const std::string& message) override;
    const std::string& getTransportType() const override;
    
    bool wasMessageSent(const AuthRequestMessage& message) const;
    bool wasMessageSent(const Message& message) const;
    const std::vector<std::string>& getSentMessages() const;
    void reset();
    
private:
    std::string transportType;
    std::vector<std::string> sentMessages;
};
