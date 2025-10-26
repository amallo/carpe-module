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

bool InMemoryAuthChallengeStore::resolve(const AuthChallenge& challenge) {
    for (auto* storedChallenge : challenges) {
        if (*storedChallenge == challenge) {
            delete storedChallenge;
            challenges.erase(std::remove(challenges.begin(), challenges.end(), storedChallenge), challenges.end());
            return true;
        }
    }
    return false;
}
