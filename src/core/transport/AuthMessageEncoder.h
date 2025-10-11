#pragma once
#include <vector>
#include <cstdint>

// Forward declaration
class Message;

class AuthMessageEncoder {
public:
    virtual ~AuthMessageEncoder() = default;
    virtual std::vector<uint8_t> encode(const Message& message) const = 0;
};
