#include "InMemoryAuthChallengeStore.h"

void InMemoryAuthChallengeStore::store(AuthChallenge* challenge) {
    challenges.push_back(challenge);
}

AuthChallenge* InMemoryAuthChallengeStore::get(const std::string& challengeId) {
    for (auto* challenge : challenges) {
        if (challenge->getId() == challengeId) {
            return challenge;
        }
    }
    return nullptr;
}
