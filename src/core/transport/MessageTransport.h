#pragma once
#include <string>

class MessageTransport {
public:
    virtual ~MessageTransport() = default;
    virtual void send(const std::string& message) = 0;
    virtual const std::string& getTransportType() const = 0;
};
