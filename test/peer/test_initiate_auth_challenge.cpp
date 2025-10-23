#include "doctest/doctest.h"
#include "src/core/peer/usecases/InitiateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageGateway.h"
#include "test/transport/MockAuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

struct TestSetup {
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway;
    MockAuthChallengeStore challengeStore;
    InitiateAuthChallengeUseCase useCase;
    
    TestSetup() 
        : messageGateway("bluetooth")
        , useCase(screen, challengeGenerator, messageGateway, challengeStore) {
        challengeGenerator.scheduleGeneratedChallenge(new AuthChallenge("challenge-1", "1234"));
    }
    
    void execute() {
        useCase.execute("AA:BB:CC:DD:EE:FF");
    }
};

TEST_CASE("Should display pin code challenge on challenge initiation") {  
    TestSetup setup;
    setup.execute();
    CHECK(setup.screen.wasDisplayedPinCodeChallenge("1234"));
}

TEST_CASE("Should send initiate auth challenge message on challenge initiation") {  
    TestSetup setup;
    setup.execute();
    CHECK(setup.messageGateway.wasMessageSent(new InitiateAuthChallengeMessage("challenge-1")));
}

TEST_CASE("Should store challenge on challenge initiation") {
    TestSetup setup;
    setup.execute();
    CHECK(setup.challengeStore.wasChallengeStored(new AuthChallenge("challenge-1", "1234")));
}