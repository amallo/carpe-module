#pragma once
#include <vector>
#include <cstdint>

// Forward declaration
class AuthRequestMessage;

class AuthMessageEncoder {
public:
    virtual ~AuthMessageEncoder() = default;
    virtual std::vector<uint8_t> encode(const AuthRequestMessage& message) const = 0;
};
