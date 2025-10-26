#pragma once
#include "core/peer/model/AuthChallenge.h"
#include <string>

/**
 * @brief Interface pour stocker les challenges d'authentification
 */
class AuthChallengeStore {
public:
    virtual ~AuthChallengeStore() = default;
    virtual void store(AuthChallenge* challenge) = 0;
    virtual bool isEmpty() const = 0;
    virtual void reset() = 0;
    virtual AuthChallenge* get(const std::string& challengeId) = 0;
};
