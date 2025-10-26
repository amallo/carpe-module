#include "MockAuthChallengeStore.h"

MockAuthChallengeStore::MockAuthChallengeStore() {
}

void MockAuthChallengeStore::store(AuthChallenge* challenge) {
    storedChallenges.push_back(challenge);
}


AuthChallenge* MockAuthChallengeStore::get(const std::string& challengeId, const std::string& pinCode) {
    for (auto* challenge : storedChallenges) {
        if (challenge->getId() == challengeId && challenge->getPinCode() == pinCode) {
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

bool MockAuthChallengeStore::isEmpty() const {
    return storedChallenges.empty();
}

void MockAuthChallengeStore::reset() {
    storedChallenges.clear();
}
