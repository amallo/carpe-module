#include "doctest/doctest.h"
#include "src/core/peer/usecases/InitiateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageGateway.h"
#include "core/peer/model/Challenge.h"
#include "core/peer/model/AuthRequestMessage.h"

TEST_CASE("Should display pin code challenge on connection") {  
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway("bluetooth");
    challengeGenerator.scheduleGeneratedChallenge(new Challenge("challenge-1", "1234"));
    InitiateAuthChallengeUseCase useCase(screen, challengeGenerator, messageGateway);

    useCase.execute("AA:BB:CC:DD:EE:FF");
    CHECK(screen.wasDisplayedPinCodeChallenge("1234"));
}

TEST_CASE("Should send auth request challenge on connection") {  
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway("bluetooth");
    challengeGenerator.scheduleGeneratedChallenge(new Challenge("challenge-1", "1234"));
    InitiateAuthChallengeUseCase useCase(screen, challengeGenerator, messageGateway);

    useCase.execute("AA:BB:CC:DD:EE:FF");
    CHECK(messageGateway.wasMessageSent(new AuthRequestMessage("challenge-1")));
}