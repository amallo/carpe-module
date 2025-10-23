#pragma once
#include "core/peer/model/AuthChallenge.h"

class AuthChallengeGenerator {
public:
    virtual ~AuthChallengeGenerator() = default;
    virtual AuthChallenge* generateChallenge() = 0;
};
