#pragma once
#include "core/peer/model/AuthChallenge.h"

class ChallengeGenerator {
public:
    virtual ~ChallengeGenerator() = default;
    virtual AuthChallenge* generateChallenge() = 0;
};
