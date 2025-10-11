#pragma once
#include <vector>
#include <cstdint>

class MessageTransport {
public:
    virtual ~MessageTransport() = default;
    virtual void send(const std::vector<uint8_t>& encodedMessage) = 0;
    virtual const std::string& getTransportType() const = 0;
};
