#pragma once
#include "core/peer/AuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include <vector>

class InMemoryAuthChallengeStore : public AuthChallengeStore {
public:
    void store(AuthChallenge* challenge) override;
    bool isEmpty() const override;
    void reset() override;
    bool resolve(const AuthChallenge& challenge) override;
    
private:
    std::vector<AuthChallenge*> challenges;
};
