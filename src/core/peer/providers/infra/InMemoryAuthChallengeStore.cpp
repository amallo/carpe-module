#include "InMemoryAuthChallengeStore.h"
#include <algorithm>

void InMemoryAuthChallengeStore::store(AuthChallenge* challenge) {
    challenges.push_back(challenge);
}

bool InMemoryAuthChallengeStore::isEmpty() const {
    return challenges.empty();
}

void InMemoryAuthChallengeStore::reset() {
    for (auto* challenge : challenges) {
        delete challenge;
    }
    challenges.clear();
}

AuthChallenge* InMemoryAuthChallengeStore::get(const std::string& challengeId, const std::string& pinCode) {
    for (auto* challenge : challenges) {
        if (challenge->getId() == challengeId && challenge->getPinCode() == pinCode) {
            return challenge;
        }
    }
    return nullptr;
}
