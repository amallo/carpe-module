#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>
#include "core/transport/PeerConnection.h"
#include "core/transport/model/Challenge.h"
#include "core/transport/model/AuthRequestMessage.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageTransport.h"
#include "test/transport/MockScreen.h"

// Test de l'envoi de challenge à la connexion
TEST_CASE("Should send challenge on connection") {
    MockChallengeGenerator challengeGenerator;
    challengeGenerator.scheduleGeneratedChallenge(new Challenge("challenge-1", "5678"));

    MockMessageTransport bluetoothTransport("bluetooth");
    MockScreen screen;
    
    PeerConnection peerConnection(&challengeGenerator, bluetoothTransport, screen);
    
    // Simuler la connexion d'un device
    peerConnection.onDeviceConnected("AA:BB:CC:DD:EE:FF");
    
    // Vérifier que le message d'authentification a été envoyé
    AuthRequestMessage expectedMessage("challenge-1");
    CHECK(bluetoothTransport.wasMessageSent(expectedMessage));
    
    // Vérifier que le PIN a été affiché sur l'écran
    CHECK(screen.wasDisplayPinCodeChallengeCalledWithPinCode("5678"));
}



 
