#pragma once
#include <vector>
#include <cstdint>

// Forward declaration
class InitiateAuthChallengeMessage;

class MessageEncoder {
public:
    virtual ~MessageEncoder() = default;
    virtual std::vector<uint8_t> encode(const InitiateAuthChallengeMessage& message) const = 0;
};
