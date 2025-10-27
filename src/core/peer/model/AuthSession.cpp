#include "AuthSession.h"

AuthSession::AuthSession(const AuthSessionPayload& payload)
    : payload(payload) {
}

AuthSession::~AuthSession() {
}

bool AuthSession::operator==(const AuthSession& other) const {
    return payload == other.payload;
}