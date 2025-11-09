#include "NegociateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/protocol/messages/AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/protocol/messages/AuthChallengeNegociationFailureMessage.h"
#include "core/peer/model/AuthSession.h"
#include "core/peer/protocol/MessageHeader.h"
#include "core/peer/protocol/MessageTypes.h"
#include "core/peer/providers/AuthSessionStore.h"

// Forward declarations - encoders définis dans leurs fichiers .cpp respectifs
class AuthChallengeNegociationMessageSuccededEncoder;
class AuthChallengeNegociationFailureMessageEncoder;

NegociateAuthChallengeUseCase::NegociateAuthChallengeUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore, AuthSessionStore& sessionStore, CommonIDGenerator& idGenerator)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), sessionStore(&sessionStore), idGenerator(&idGenerator) {
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
    handleIncorrectPin(challenge);
}

void NegociateAuthChallengeUseCase::sendSuccessMessage(const std::string& challengeId) {
    std::string sessionId = idGenerator->generate();
    // Create and store session
    AuthSession* session = new AuthSession(AuthSessionPayload(sessionId, challengeId));
    sessionStore->store(session);

    // Créer l'encoder
    AuthChallengeNegociationMessageSuccededEncoder encoder;
    
    // Créer le MessageHeader (TYPE AUTH_CHALLENGE_NEGOTIATION_SUCCESS + NONCE)
    MessageHeader header(MessageType::AUTH_CHALLENGE_NEGOTIATION_SUCCESS, 0); // Nonce could be generated here
    
    // Créer le message avec payload, header et encoder
    AuthChallengeNegociationSuccessPayload payload(sessionId, challengeId);
    AuthChallengeNegociationMessageSucceded message(payload, header, &encoder);
    
    messageGateway->send(message);
    
    challengeStore->reset();
}

void NegociateAuthChallengeUseCase::sendFailureMessage(const std::string& challengeId, const std::string& reason, int remainingAttempts) {
    // Créer l'encoder
    AuthChallengeNegociationFailureMessageEncoder encoder;
    
    // Créer le MessageHeader (TYPE AUTH_CHALLENGE_NEGOTIATION_FAILURE + NONCE)
    MessageHeader header(MessageType::AUTH_CHALLENGE_NEGOTIATION_FAILURE, 0); // Nonce could be generated here
    
    // Créer le message avec payload, header et encoder
    AuthChallengeNegociationFailurePayload payload(challengeId, reason, remainingAttempts);
    AuthChallengeNegociationFailureMessage message(payload, header, &encoder);
    
    messageGateway->send(message);
    
    if (remainingAttempts < 0) {
        challengeStore->reset();
    }
}

void NegociateAuthChallengeUseCase::handleIncorrectPin(AuthChallenge* challenge) {
    challenge->decreaseRemainingAttempts();
    int remaining = challenge->getRemainingAttempts();
    
    if (remaining <= 0) {
        sendFailureMessage(challenge->getId(), "Invalid challenge", remaining);
    } else {
        sendFailureMessage(challenge->getId(), "Invalid PIN", remaining);
    }
}
