#include "doctest/doctest.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/protocol/messages/AuthChallengeNegociationMessageSucceded.h"
#include "core/peer/protocol/messages/AuthChallengeNegociationFailureMessage.h"
#include "core/peer/usecases/NegociateAuthChallengeUseCase.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockMessageGateway.h"
#include "test/transport/MockAuthChallengeStore.h"
#include "test/transport/MockMessageEncoder.h"
#include "core/peer/providers/infra/InMemoryAuthChallengeStore.h"
#include "core/peer/providers/infra/InMemoryAuthSessionStore.h"
#include "test/core/device/generators/MockCommonIDGenerator.h"

struct NegocateAuthChallengeTestSetup {
    MockScreen screen;
    MockMessageGateway messageGateway;
    InMemoryAuthChallengeStore challengeStore;
    InMemoryAuthSessionStore sessionStore;
    MockMessageEncoder mockMessageEncoder;
    MockCommonIDGenerator commonIdGenerator;
    NegociateAuthChallengeUseCase useCase;
    MockCommonIDGenerator idGenerator;
    
    NegocateAuthChallengeTestSetup() 
        : messageGateway("bluetooth")
        , useCase(screen, messageGateway, challengeStore, sessionStore, idGenerator) {
    }

    void givenChallenge(const std::string& challengeId, const std::string& pinCode, int remainingAttempts = 3) {
        AuthChallenge* challenge = new AuthChallenge(challengeId, pinCode, remainingAttempts);
        challengeStore.store(challenge);
    }
    void givenChallengeWithNoRemainingAttempts(const std::string& challengeId, const std::string& pinCode) {
       return givenChallenge(challengeId, pinCode, 0);
    }
    
    void negociate(const std::string& challengeId, const std::string& pinCode) {
        useCase.execute(challengeId, pinCode);
    }
    bool verifyMessageSent(const MessageInterface& message) {
        return messageGateway.wasMessageSent(message);
    }
    bool isChallengeEnded() {
        return challengeStore.isEmpty();
    }
    bool wasCreatedSession(const AuthSession& session) {
        AuthSession* current = sessionStore.current();
        return current && *current == session;
    }
    void wasGeneratedSessionId(const std::string& sessionId) {
        return idGenerator.scheduleID(sessionId);
    }
};

TEST_CASE("Should open a session when correct PIN is provided") {
    NegocateAuthChallengeTestSetup setup;
    
    // Given: A challenge with PIN "1234" is stored
    setup.givenChallenge("challenge-1", "1234");
    setup.wasGeneratedSessionId("session-1");
    
    // When: The negotiation starts
    setup.negociate("challenge-1", "1234");
    
    // Then: The negotiation should succeed
    AuthChallengeNegociationMessageSucceded expectedMessage = AuthChallengeNegociationMessageSucceded::create("session-1", "challenge-1");
    CHECK(setup.verifyMessageSent(expectedMessage));
    AuthSession expectedSession(AuthSessionPayload("session-1", "challenge-1"));
    CHECK(setup.wasCreatedSession(expectedSession));
    CHECK(setup.isChallengeEnded());
}

TEST_CASE("Should end challenge negotiation when incorrect PIN is provided and over the remaining attempts") {
    NegocateAuthChallengeTestSetup setup;

     // Given: A challenge with PIN "1234" is stored and no remaining attempts
     setup.givenChallengeWithNoRemainingAttempts("challenge-1", "1234");
    
    // when: the negotiation starts with an incorrect PIN
    setup.negociate("challenge-1", "5634");
    
    // then: the negotiation should fail
    AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create("challenge-1", "Invalid challenge", -1, 0);
    CHECK(setup.verifyMessageSent(message));
    CHECK(setup.isChallengeEnded());
}

TEST_CASE("Should end challenge negotiation when challenge is not found") {
    NegocateAuthChallengeTestSetup setup;

    // Given: A challenge with PIN "1234" is stored
    setup.givenChallenge("challenge-1", "1234", 1);
    
    // when: the negotiation starts with an incorrect PIN
    setup.negociate("challenge-2", "1234");
    AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create("challenge-2", "Invalid challenge", -1, 0);
    CHECK(setup.verifyMessageSent(message));
    CHECK(setup.isChallengeEnded());
}

TEST_CASE("Should retry challenge negotiation when incorrect PIN is provided and remaining attempts is not 0") {
    NegocateAuthChallengeTestSetup setup;

     // Given: A challenge with PIN "1234" is stored
     setup.givenChallenge("challenge-1", "1234", 2);
    
    // when: the negotiation starts with an incorrect PIN
    setup.negociate("challenge-1", "5634");
    
    // then: the negotiation should fail
    AuthChallengeNegociationFailureMessage message = AuthChallengeNegociationFailureMessage::create("challenge-1", "Invalid PIN", 1);
    CHECK(setup.verifyMessageSent(message));
    CHECK(!setup.isChallengeEnded());
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
