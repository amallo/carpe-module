#pragma once
#include "core/peer/AuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include <vector>

class InMemoryAuthChallengeStore : public AuthChallengeStore {
public:
    void store(AuthChallenge* challenge) override;
    AuthChallenge* get(const std::string& challengeId) override;
    
private:
    std::vector<AuthChallenge*> challenges;
};
