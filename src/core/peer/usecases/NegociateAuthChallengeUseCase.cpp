#include "NegociateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/model/AuthChallengeNegociationFailureMessage.h"
#include "core/peer/model/AuthSession.h"
#include "core/peer/providers/AuthSessionStore.h"

NegociateAuthChallengeUseCase::NegociateAuthChallengeUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore, AuthSessionStore& sessionStore)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), sessionStore(&sessionStore) {
}

NegociateAuthChallengeUseCase::~NegociateAuthChallengeUseCase() {}

void NegociateAuthChallengeUseCase::execute(const std::string& challengeId, const std::string& pinCode) {
    AuthChallenge* challenge = challengeStore->get(challengeId);
    
    // Challenge non trouvé
    if (challenge == nullptr) {
        sendFailureMessage(challengeId, "Invalid challenge", -1);
        return;
    }
    
    // PIN correct
    if (challenge->matchPinCode(pinCode)) {
        sendSuccessMessage(challengeId);
        return;
    }
    
    // PIN incorrect - gérer les tentatives
    handleIncorrectPin(challengeId, challenge);
}

void NegociateAuthChallengeUseCase::sendSuccessMessage(const std::string& challengeId) {
    AuthChallengeNegociationMessageSucceded message = AuthChallengeNegociationMessageSucceded::create(challengeId);
    messageGateway->send(message);
    
    // Create and store session
    AuthSession* session = new AuthSession(AuthSessionPayload("session-1", "challenge-1"));
    sessionStore->store(session);
    
    challengeStore->reset();
}

void NegociateAuthChallengeUseCase::sendFailureMessage(const std::string& challengeId, const std::string& reason, int remainingAttempts) {
    AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create(challengeId, reason, remainingAttempts);
    messageGateway->send(message);
    if (remainingAttempts < 0) {
        challengeStore->reset();
    }
}

void NegociateAuthChallengeUseCase::handleIncorrectPin(const std::string& challengeId, AuthChallenge* challenge) {
    challenge->decreaseRemainingAttempts();
    int remaining = challenge->getRemainingAttempts();
    
    if (remaining < 0) {
        sendFailureMessage(challengeId, "Invalid challenge", remaining);
    } else {
        sendFailureMessage(challengeId, "Invalid PIN", remaining);
    }
}
