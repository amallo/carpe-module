#pragma once
#include "core/peer/model/AuthSession.h"
#include <string>

class AuthSessionStore {
public:
    virtual ~AuthSessionStore() = default;
    virtual void store(AuthSession* session) = 0;
    virtual AuthSession* current() = 0;
};