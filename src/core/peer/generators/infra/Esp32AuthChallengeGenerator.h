#pragma once
#include "core/peer/AuthChallengeGenerator.h"
#include "core/random/providers/RandomProvider.h"
#include <string>

class Esp32AuthChallengeGenerator : public AuthChallengeGenerator {
public:
    explicit Esp32AuthChallengeGenerator(RandomProvider* randomProvider);
    AuthChallenge* generateChallenge() override;
    
private:
    RandomProvider* randomProvider;
};
