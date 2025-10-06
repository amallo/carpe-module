#include "MockChallengeGenerator.h"

MockChallengeGenerator::MockChallengeGenerator() 
    : currentIndex(0), generateChallengeCalled(false) {
}

void MockChallengeGenerator::scheduleGeneratedChallenge(Challenge* challenge) {
    scheduledChallenges.push_back(std::unique_ptr<Challenge>(challenge));
}

Challenge* MockChallengeGenerator::generateChallenge() {
    generateChallengeCalled = true;
    if (currentIndex < scheduledChallenges.size()) {
        return scheduledChallenges[currentIndex++].get();
    }
    return nullptr;
}

bool MockChallengeGenerator::wasGenerateChallengeCalled() const {
    return generateChallengeCalled;
}

void MockChallengeGenerator::reset() {
    scheduledChallenges.clear();
    currentIndex = 0;
    generateChallengeCalled = false;
}
