#include "InitiateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

InitiateAuthChallengeUseCase::InitiateAuthChallengeUseCase(Screen& screen, AuthChallengeGenerator& challengeGenerator, MessageGateway& messageGateway, AuthChallengeStore& challengeStore)
    : screen(&screen), challengeGenerator(&challengeGenerator), messageGateway(&messageGateway), challengeStore(&challengeStore) {
}

InitiateAuthChallengeUseCase::~InitiateAuthChallengeUseCase() {
}

void InitiateAuthChallengeUseCase::execute(const std::string& deviceAddress) {
    // Générer un challenge
    AuthChallenge* challenge = challengeGenerator->generateChallenge();

    // Stocker le challenge
    challengeStore->store(challenge);
    
    // Afficher le PIN sur l'écran
    screen->displayPinCodeChallenge(challenge->getPinCode());
    
    
    // Envoyer le message d'authentification
    InitiateAuthChallengePayload payload(challenge->getId());
    InitiateAuthChallengeMessage initiateAuthChallengeMessage(payload);
    messageGateway->send(initiateAuthChallengeMessage);
    
}