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
    AuthChallenge* get(const std::string& challengeId) override;
    bool wasChallengeStored(AuthChallenge* challenge) const;
    void reset();
    bool isEmpty() const override;
    
private:
    std::vector<AuthChallenge*> storedChallenges;
};
