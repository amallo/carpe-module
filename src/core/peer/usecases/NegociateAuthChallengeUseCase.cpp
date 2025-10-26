#include "NegociateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/model/AuthChallengeNegociationFailureMessage.h"
NegociateAuthChallengeUseCase::NegociateAuthChallengeUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore, MessageEncoder& encoder)
    : screen(&screen), messageGateway(&messageGateway), challengeStore(&challengeStore), encoder(&encoder) {
}

NegociateAuthChallengeUseCase::~NegociateAuthChallengeUseCase() {
}

void NegociateAuthChallengeUseCase::execute(const std::string& challengeId, const std::string& pinCode) {
    AuthChallenge* currentAuthChallenge = challengeStore->get(challengeId, pinCode);
    
    if (currentAuthChallenge) {
        // Challenge trouvé et PIN correct
        AuthChallengeNegociationMessageSucceded message = AuthChallengeNegociationMessageSucceded::create(challengeId, *encoder);
        messageGateway->send(message);
        challengeStore->reset();
    } else {
        // Challenge non trouvé ou PIN incorrect
        AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create(challengeId, "Invalid PIN", 0, *encoder);
        messageGateway->send(message);
        challengeStore->reset();
    }
}
