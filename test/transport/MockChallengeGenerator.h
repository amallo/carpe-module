#pragma once
#include <vector>
#include <memory>
#include "core/transport/model/Challenge.h"

class MockChallengeGenerator {
public:
    MockChallengeGenerator();
    
    void scheduleGeneratedChallenge(Challenge* challenge);
    Challenge* generateChallenge();
    
    bool wasGenerateChallengeCalled() const;
    void reset();
    
private:
    std::vector<std::unique_ptr<Challenge>> scheduledChallenges;
    int currentIndex;
    bool generateChallengeCalled;
};
