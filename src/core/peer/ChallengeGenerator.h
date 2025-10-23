#pragma once
#include "core/peer/model/Challenge.h"

class ChallengeGenerator {
public:
    virtual ~ChallengeGenerator() = default;
    virtual Challenge* generateChallenge() = 0;
};
