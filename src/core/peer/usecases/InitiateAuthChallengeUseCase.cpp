#include "InitiateAuthChallengeUseCase.h"
#include "core/peer/model/Challenge.h"
#include "core/peer/model/AuthRequestMessage.h"

InitiateAuthChallengeUseCase::InitiateAuthChallengeUseCase(Screen& screen, ChallengeGenerator& challengeGenerator, MessageGateway& messageGateway)
    : screen(&screen), challengeGenerator(&challengeGenerator), messageGateway(&messageGateway) {
}

InitiateAuthChallengeUseCase::~InitiateAuthChallengeUseCase() {
}

void InitiateAuthChallengeUseCase::execute(const std::string& deviceAddress) {
    // Générer un challenge
    Challenge* challenge = challengeGenerator->generateChallenge();
    
    // Afficher le PIN sur l'écran
    screen->displayPinCodeChallenge(challenge->getPinCode());
    
    // Envoyer le message d'authentification
    AuthRequestMessage* authMessage = new AuthRequestMessage(challenge->getId());
    messageGateway->send(authMessage);
    
}