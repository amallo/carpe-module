#include "doctest/doctest.h"
#include "src/core/peer/usecases/InitiateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageGateway.h"
#include "test/transport/MockAuthChallengeStore.h"
#include "test/transport/MockMessageEncoder.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

struct TestSetup {
    MockScreen screen;
    MockChallengeGenerator challengeGenerator;
    MockMessageGateway messageGateway;
    MockAuthChallengeStore challengeStore;
    MockMessageEncoder mockMessageEncoder;
    InitiateAuthChallengeUseCase useCase;
    
    TestSetup() 
        : messageGateway("bluetooth")
        , useCase(screen, challengeGenerator, messageGateway, challengeStore, mockMessageEncoder) {
        challengeGenerator.scheduleGeneratedChallenge(new AuthChallenge("challenge-1", "1234"));
    }
    
    void execute() {
        useCase.execute("AA:BB:CC:DD:EE:FF");
    }
    bool verifyMessageSent(const MessageInterface& message) {
        return messageGateway.wasMessageSent(message);
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
    InitiateAuthChallengePayload payload("challenge-1");
    InitiateAuthChallengeMessage message(payload, setup.mockMessageEncoder);
    CHECK(setup.verifyMessageSent(message));
}

TEST_CASE("Should store challenge on challenge initiation") {
    TestSetup setup;
    setup.execute();
    CHECK(setup.challengeStore.wasChallengeStored(new AuthChallenge("challenge-1", "1234")));
}