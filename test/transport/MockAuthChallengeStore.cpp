#include "MockAuthChallengeStore.h"

MockAuthChallengeStore::MockAuthChallengeStore() {
}

void MockAuthChallengeStore::store(AuthChallenge* challenge) {
    storedChallenges.push_back(challenge);
}


bool MockAuthChallengeStore::resolve(const AuthChallenge& challenge) {
    for (auto* storedChallenge : storedChallenges) {
        if (storedChallenge->getId() == challenge.getId() && 
            storedChallenge->getPinCode() == challenge.getPinCode()) {
            return true;
        }
    }
    return false;
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
