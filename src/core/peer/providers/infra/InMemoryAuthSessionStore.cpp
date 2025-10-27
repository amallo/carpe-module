#include "InMemoryAuthSessionStore.h"

InMemoryAuthSessionStore::InMemoryAuthSessionStore() {
}

void InMemoryAuthSessionStore::store(AuthSession* session) {
    sessions.push_back(session);
}

AuthSession* InMemoryAuthSessionStore::current() {
    if (sessions.empty()) {
        return nullptr;
    }
    return sessions.back();
}