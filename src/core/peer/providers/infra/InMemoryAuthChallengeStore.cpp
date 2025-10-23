#include "InMemoryAuthChallengeStore.h"

void InMemoryAuthChallengeStore::store(AuthChallenge* challenge) {
    challenges.push_back(challenge);
}
