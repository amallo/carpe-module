#include "PeerConnection.h"
#include "test/transport/MockChallengeGenerator.h"
#include "test/transport/MockScreen.h"

PeerConnection::PeerConnection(MockChallengeGenerator* challengeGenerator, 
                               MessageTransport& transport, 
                               MockScreen& screen)
    : challengeGenerator(challengeGenerator), transport(&transport), screen(&screen) {
}

void PeerConnection::onDeviceConnected(const std::string& deviceAddress) {
    // Générer un challenge
    Challenge* challenge = challengeGenerator->generateChallenge();
    if (challenge) {
        // Créer le message d'authentification avec nonce
        AuthRequestMessage authMessage(challenge->getId(), 12345); // nonce fixe pour les tests
        
        // Envoyer le message (on envoie le challengeId comme string pour simplifier)
        transport->send(authMessage.getChallengeId());
        
        // Afficher le PIN sur l'écran
        screen->displayPinCodeChallenge(challenge->getPinCode());
    }
}
