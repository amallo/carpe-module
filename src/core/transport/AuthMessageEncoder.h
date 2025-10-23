#pragma once
#include <vector>
#include <cstdint>

// Forward declaration
class InitiateAuthChallengeMessage;

class AuthMessageEncoder {
public:
    virtual ~AuthMessageEncoder() = default;
    virtual std::vector<uint8_t> encode(const InitiateAuthChallengeMessage& message) const = 0;
};
