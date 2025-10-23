#include "doctest/doctest.h"
#include "src/core/peer/usecases/InitiateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageGateway.h"
#include "test/transport/MockAuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

TEST_CASE("Should display pin code challenge on challenge initiation") {  
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway("bluetooth");
    challengeGenerator.scheduleGeneratedChallenge(new AuthChallenge("challenge-1", "1234"));
    MockAuthChallengeStore challengeStore;
    InitiateAuthChallengeUseCase useCase(screen, challengeGenerator, messageGateway, challengeStore);

    useCase.execute("AA:BB:CC:DD:EE:FF");
    CHECK(screen.wasDisplayedPinCodeChallenge("1234"));
}

TEST_CASE("Should send initiate auth challenge message on challenge initiation") {  
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway("bluetooth");
    challengeGenerator.scheduleGeneratedChallenge(new AuthChallenge("challenge-1", "1234"));
    MockAuthChallengeStore challengeStore;
    InitiateAuthChallengeUseCase useCase(screen, challengeGenerator, messageGateway, challengeStore);

    useCase.execute("AA:BB:CC:DD:EE:FF");
    CHECK(messageGateway.wasMessageSent(new InitiateAuthChallengeMessage("challenge-1")));
}

TEST_CASE("Should store challenge on challenge initiation") {
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway("bluetooth");
    MockAuthChallengeStore challengeStore;
    challengeGenerator.scheduleGeneratedChallenge(new AuthChallenge("challenge-1", "1234"));
    InitiateAuthChallengeUseCase useCase(screen, challengeGenerator, messageGateway, challengeStore);

    useCase.execute("AA:BB:CC:DD:EE:FF");
    CHECK(challengeStore.wasChallengeStored(new AuthChallenge("challenge-1", "1234")));
}