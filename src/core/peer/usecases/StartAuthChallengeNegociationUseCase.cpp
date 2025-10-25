#include "StartAuthChallengeNegociationUseCase.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
StartAuthChallengeNegociationUseCase::StartAuthChallengeNegociationUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore) {
}

StartAuthChallengeNegociationUseCase::~StartAuthChallengeNegociationUseCase() {
}

void StartAuthChallengeNegociationUseCase::execute(const std::string& challengeId) {
    // Vérifier que le challenge existe dans le store
    AuthChallenge* challenge = challengeStore->get(challengeId);
    
    AuthChallengeNegociationMessageSucceded message(challengeId);
    messageGateway->send(message);
}
