#pragma once
#include <vector>
#include <memory>
#include "core/peer/ChallengeGenerator.h"
#include "core/peer/model/AuthChallenge.h"

class MockChallengeGenerator : public ChallengeGenerator {
public:
    MockChallengeGenerator();
    
    void scheduleGeneratedChallenge(AuthChallenge* challenge);
    AuthChallenge* generateChallenge() override;
    
    bool wasGenerateChallengeCalled() const;
    void reset();
    
private:
    std::vector<std::unique_ptr<AuthChallenge>> scheduledChallenges;
    int currentIndex;
    bool generateChallengeCalled;
};
