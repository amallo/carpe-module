#include "doctest/doctest.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/model/AuthChallengeNegociationFailureMessage.h"
#include "core/peer/usecases/NegociateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockMessageGateway.h"
#include "test/transport/MockAuthChallengeStore.h"
#include "test/transport/MockMessageEncoder.h"

struct NegocateAuthChallengeTestSetup {
    MockScreen screen;
    MockMessageGateway messageGateway;
    MockAuthChallengeStore challengeStore;
    MockMessageEncoder mockMessageEncoder;
    NegociateAuthChallengeUseCase useCase;
    
    NegocateAuthChallengeTestSetup() 
        : messageGateway("bluetooth")
        , useCase(screen, messageGateway, challengeStore, mockMessageEncoder) {
    }

    void givenChallenge(const std::string& challengeId, const std::string& pinCode, int remainingAttempts = 3) {
        AuthChallenge* challenge = new AuthChallenge(challengeId, pinCode, remainingAttempts);
        challengeStore.store(challenge);
    }
    
    void negociate(const std::string& challengeId, const std::string& pinCode) {
        useCase.execute(challengeId, pinCode);
    }
    bool verifyMessageSent(const MessageInterface& message) {
        return messageGateway.wasMessageSent(message);
    }
    bool isEmptyChallenge() {
        return challengeStore.isEmpty();
    }
};

TEST_CASE("Should succeed challenge negotiation when correct PIN is provided") {
    NegocateAuthChallengeTestSetup setup;
    
    // Given: A challenge with PIN "1234" is stored
    setup.givenChallenge("challenge-1", "1234");
    
    // When: The negotiation starts
    setup.negociate("challenge-1", "1234");
    
    // Then: The negotiation should succeed
    AuthChallengeNegociationMessageSucceded expectedMessage = AuthChallengeNegociationMessageSucceded::create("challenge-1", setup.mockMessageEncoder);
    CHECK(setup.verifyMessageSent(expectedMessage));
    CHECK(setup.isEmptyChallenge());
    // papa louva myriam romy joséphine éléonore robin
}

TEST_CASE("Should fail challenge negotiation when incorrect PIN is provided and over the remaining attempts") {
    NegocateAuthChallengeTestSetup setup;

     // Given: A challenge with PIN "1234" is stored
     setup.givenChallenge("challenge-1", "1234", 0);
    
    // when: the negotiation starts with an incorrect PIN
    setup.negociate("challenge-1", "5634");
    
    // then: the negotiation should fail
    AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create("challenge-1", "Invalid PIN", 2, setup.mockMessageEncoder);
    CHECK(setup.verifyMessageSent(message));
    CHECK(setup.isEmptyChallenge());
}
/*
TEST_CASE("Should fail after 3 incorrect attempts") {
    NegocateAuthChallengeTestSetup setup;
    
    // Given: A challenge with PIN "1234" is active
    setup.negociate("challenge-1", "1234");
    
    // When: 3 incorrect PINs are submitted
    CHECK(setup.submitPin("1111") == false);
    CHECK(setup.submitPin("2222") == false);
    CHECK(setup.submitPin("3333") == false);
    
    // Then: The negotiation should be terminated
    CHECK(setup.useCase.isNegotiationActive() == false);
    CHECK(setup.screen.wasDisplayedFailureMessage());
}

TEST_CASE("Should succeed on 3rd attempt if correct PIN is provided") {
    NegocateAuthChallengeTestSetup setup;
    
    // Given: A challenge with PIN "1234" is active
    setup.negociate("challenge-1", "1234");
    
    // When: 2 incorrect PINs, then correct PIN
    CHECK(setup.submitPin("1111") == false);
    CHECK(setup.submitPin("2222") == false);
    bool result = setup.submitPin("1234");
    
    // Then: The negotiation should succeed
    CHECK(result == true);
    CHECK(setup.screen.wasDisplayedSuccessMessage());
}

TEST_CASE("Should timeout after 1 minute") {
    PinNegotiationTestSetup setup;
    
    // Given: A challenge is started
    setup.negociate("challenge-1", "1234");
    
    // When: 1 minute passes without any PIN submission
    setup.useCase.simulateTimeout();
    
    // Then: The negotiation should timeout
    CHECK(setup.useCase.isNegotiationActive() == false);
    CHECK(setup.screen.wasDisplayedTimeoutMessage());
}

TEST_CASE("Should stop negotiation when interrupted") {
    PinNegotiationTestSetup setup;
    
    // Given: A challenge is started
    setup.startNegotiation("challenge-1", "1234");
    
    // When: The negotiation is interrupted
    setup.useCase.stopNegotiation();
    
    // Then: The negotiation should be stopped
    CHECK(setup.useCase.isNegotiationActive() == false);
}

TEST_CASE("Should not accept PIN after negotiation is stopped") {
    PinNegotiationTestSetup setup;
    
    // Given: A challenge is started and then stopped
    setup.startNegotiation("challenge-1", "1234");
    setup.useCase.stopNegotiation();
    
    // When: A correct PIN is submitted
    bool result = setup.submitPin("1234");
    
    // Then: The PIN should be rejected
    CHECK(result == false);
    CHECK_FALSE(setup.screen.wasDisplayedSuccessMessage());
}
    */
