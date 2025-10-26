#include "StartAuthChallengeNegociationUseCase.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
StartAuthChallengeNegociationUseCase::StartAuthChallengeNegociationUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore, MessageEncoder& encoder)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), encoder(&encoder) {
}

StartAuthChallengeNegociationUseCase::~StartAuthChallengeNegociationUseCase() {
}

void StartAuthChallengeNegociationUseCase::execute(const std::string& challengeId) {
    // Vérifier que le challenge existe dans le store
    AuthChallenge* challenge = challengeStore->get(challengeId);
    
    AuthChallengeNegociationSuccessPayload payload(challengeId);
    AuthChallengeNegociationMessageSucceded message(payload, *encoder);
    messageGateway->send(message);
}
