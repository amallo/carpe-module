#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>
#include "core/peer/PeerConnection.h"
#include "core/peer/model/Challenge.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockMessageTransport.h"
#include "test/transport/MockScreen.h"
#include "test/transport/MockAuthMessageEncoder.h"

// Test de l'envoi de challenge à la connexion
TEST_CASE("Should send challenge on connection") {
    MockChallengeGenerator challengeGenerator;
    challengeGenerator.scheduleGeneratedChallenge(new Challenge("challenge-1", "5678"));

    MockMessageTransport bluetoothTransport("bluetooth");
    MockScreen screen;
    MockAuthMessageEncoder encoder;
    
    PeerConnection peerConnection(&challengeGenerator, bluetoothTransport, screen, encoder);
    
    // Simuler la connexion d'un device
    peerConnection.onDeviceConnected("AA:BB:CC:DD:EE:FF");
    
    // Vérifier que le message d'authentification a été envoyé
    InitiateAuthChallengeMessage expectedMessage("challenge-1");
    CHECK(bluetoothTransport.wasMessageSent(expectedMessage));
    
    // Vérifier que l'encoder a été appelé avec les bons paramètres
    CHECK(encoder.wasEncodedWith("auth_request", 12345, "challenge-1"));
    
    // Vérifier que le PIN a été affiché sur l'écran
    CHECK(screen.wasDisplayedPinCodeChallenge("5678"));
}



 
