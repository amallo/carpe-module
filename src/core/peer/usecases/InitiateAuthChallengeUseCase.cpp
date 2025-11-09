#include "InitiateAuthChallengeUseCase.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/protocol/messages/InitiateAuthChallengeMessage.h"
#include "core/peer/protocol/MessageHeader.h"
#include "core/peer/protocol/MessageTypes.h"

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
    
    // Créer l'encoder
    InitiateAuthChallengeMessageEncoder encoder;
    
    // Créer le MessageHeader (TYPE INITIATE_AUTH_CHALLENGE + NONCE)
    MessageHeader header(MessageType::INITIATE_AUTH_CHALLENGE, 0);
    
    // Créer le message avec payload, header et encoder
    InitiateAuthChallengePayload payload(challenge->getId());
    InitiateAuthChallengeMessage message(payload, header, &encoder);
    
    messageGateway->send(message);
}