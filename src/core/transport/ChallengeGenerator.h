#pragma once
#include "core/transport/model/Challenge.h"

class ChallengeGenerator {
public:
    virtual ~ChallengeGenerator() = default;
    virtual Challenge* generateChallenge() = 0;
};
