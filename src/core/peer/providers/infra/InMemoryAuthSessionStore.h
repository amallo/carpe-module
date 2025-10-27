#pragma once
#include "core/peer/providers/AuthSessionStore.h"
#include "core/peer/model/AuthSession.h"
#include <vector>

class InMemoryAuthSessionStore : public AuthSessionStore {
public:
    InMemoryAuthSessionStore();
    void store(AuthSession* session) override;
    AuthSession* current() override;

private:
    std::vector<AuthSession*> sessions;
};