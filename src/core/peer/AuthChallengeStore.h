#pragma once
#include "core/peer/model/AuthChallenge.h"

/**
 * @brief Interface pour stocker les challenges d'authentification
 */
class AuthChallengeStore {
public:
    virtual ~AuthChallengeStore() = default;
    virtual void store(AuthChallenge* challenge) = 0;
};
