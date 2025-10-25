#pragma once
#include "core/peer/generators/AuthChallengeGenerator.h"
#include "core/random/providers/RandomProvider.h"
#include <string>

class RandomAuthChallengeGenerator : public AuthChallengeGenerator {
public:
    explicit RandomAuthChallengeGenerator(RandomProvider* randomProvider);
    AuthChallenge* generateChallenge() override;
    
private:
    RandomProvider* randomProvider;
};
