#include "NegociateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
NegociateAuthChallengeUseCase::NegociateAuthChallengeUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore, MessageEncoder& encoder)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), encoder(&encoder) {
}

NegociateAuthChallengeUseCase::~NegociateAuthChallengeUseCase() {
}

void NegociateAuthChallengeUseCase::execute(const std::string& challengeId, const std::string& pinCode) {
    AuthChallenge incomingChallenge(challengeId, pinCode);
    if (challengeStore->resolve(incomingChallenge)) {
        AuthChallengeNegociationMessageSucceded message = AuthChallengeNegociationMessageSucceded::create(challengeId, *encoder);
        messageGateway->send(message);
        challengeStore->reset();
    } 
}
