#include "MockAuthChallengeStore.h"

MockAuthChallengeStore::MockAuthChallengeStore() {
}

void MockAuthChallengeStore::store(AuthChallenge* challenge) {
    storedChallenges.push_back(challenge);
}

AuthChallenge* MockAuthChallengeStore::get(const std::string& challengeId) {
    for (auto* challenge : storedChallenges) {
        if (challenge->getId() == challengeId) {
            return challenge;
        }
    }
    return nullptr;
}

bool MockAuthChallengeStore::wasChallengeStored(AuthChallenge* challenge) const {
    for (auto* storedChallenge : storedChallenges) {
        if (storedChallenge->getId() == challenge->getId() && 
            storedChallenge->getPinCode() == challenge->getPinCode()) {
            return true;
        }
    }
    return false;
}

void MockAuthChallengeStore::reset() {
    storedChallenges.clear();
}
