#include "StartAuthChallengeNegociationUseCase.h"

StartAuthChallengeNegociationUseCase::StartAuthChallengeNegociationUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), 
      currentChallenge(nullptr) {
}

StartAuthChallengeNegociationUseCase::~StartAuthChallengeNegociationUseCase() {
    if (currentChallenge) {
        delete currentChallenge;
    }
}

void StartAuthChallengeNegociationUseCase::execute(const std::string& challengeId) {
    // Récupérer le challenge depuis le store
    currentChallenge = challengeStore->get(challengeId);
    
    if (currentChallenge) {
        // Afficher le PIN sur l'écran
        screen->displayPinCodeChallenge(currentChallenge->getPinCode());
    }
}
