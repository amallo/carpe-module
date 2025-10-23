#include "PeerConnection.h"

PeerConnection::PeerConnection(ChallengeGenerator* challengeGenerator, 
                               MessageTransport& transport, 
                               Screen& screen,
                               AuthMessageEncoder& encoder)
    : challengeGenerator(challengeGenerator), transport(&transport), screen(&screen), encoder(&encoder) {
}

void PeerConnection::onDeviceConnected(const std::string& deviceAddress) {
    // Générer un challenge
    Challenge* challenge = challengeGenerator->generateChallenge();
    if (challenge) {
        // Créer le message d'authentification avec nonce et encoder
        InitiateAuthChallengeMessage authMessage(challenge->getId(), 12345, *encoder); // nonce fixe pour les tests
        
        // Encoder le message en binaire selon le protocole CARPE
        std::vector<uint8_t> encodedMessage = authMessage.encode();
        
        // Envoyer le message encodé
        transport->send(encodedMessage);
        
        // Afficher le PIN sur l'écran
        screen->displayPinCodeChallenge(challenge->getPinCode());
    }
}
