#pragma once
#include <string>

struct AuthSessionPayload {
    std::string sessionId;
    std::string challengeId;
    AuthSessionPayload(const std::string& sessionId, const std::string& challengeId)
        : sessionId(sessionId), challengeId(challengeId) {}

    bool operator==(const AuthSessionPayload& other) const {
        return sessionId == other.sessionId && challengeId == other.challengeId;
    }
};

class AuthSession {
public:
    AuthSession(const AuthSessionPayload& payload);
    ~AuthSession();

    bool operator==(const AuthSession& other) const;

private:
    AuthSessionPayload payload;
};