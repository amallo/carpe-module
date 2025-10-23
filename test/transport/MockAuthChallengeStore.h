#pragma once
#include "core/peer/AuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include <vector>

/**
 * @brief Mock pour AuthChallengeStore
 */
class MockAuthChallengeStore : public AuthChallengeStore {
public:
    MockAuthChallengeStore();
    
    void store(AuthChallenge* challenge) override;
    bool wasChallengeStored(AuthChallenge* challenge) const;
    void reset();
    
private:
    std::vector<AuthChallenge*> storedChallenges;
};
