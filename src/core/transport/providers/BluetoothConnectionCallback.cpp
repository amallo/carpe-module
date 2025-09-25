#include "BluetoothConnectionCallback.h"
#include <core/transport/providers/BluetoothProvider.h>
#include <core/device/PinCodeGenerator.h>
#include <core/transport/MessageRouter.h>
#include <core/transport/model/Message.h>

void BluetoothConnectionCallback::onDeviceConnected(const std::string& deviceAddress) {
    logger->info("🎉 CALLBACK: Device connecté - " + deviceAddress);
    
    // Générer un PIN challenge et l'envoyer au client
    if (bluetoothProvider && pinCodeGenerator) {
        std::string challengePin = pinCodeGenerator->generatePinCode();
        std::string challengeMessage = "pair:challenge:" + challengePin;
        
        // Créer un message d'authentification
         std::vector<uint8_t> payload(challengeMessage.begin(), challengeMessage.end());
        Message authMessage("AUTH_REQUEST", 0x1234, payload);  // nonce fixe pour l'instant
        messageRouter->routeMessage(authMessage, "bluetooth");
        logger->info("📤 Message envoyé au client: " + challengeMessage);
        
        // Afficher le PIN sur l'écran
        std::string pinMessage = deviceId + "\nPIN: " + challengePin;
        screen->showMessage(pinMessage);
        logger->info("📱 " + deviceId + " - PIN: " + challengePin);
    }
    // Ici vous pouvez ajouter votre logique personnalisée
}

void BluetoothConnectionCallback::onDeviceDisconnected(const std::string& deviceAddress) {
    logger->warn("⚠️  CALLBACK: Device déconnecté - " + deviceAddress);
    // Message optimisé pour OLED (2 lignes)
    std::string waitingMessage = deviceId + "\nATTENTE...";
    screen->showMessage(waitingMessage);
    logger->info("📱 " + deviceId + " en attente de connexion");
    // Ici vous pouvez ajouter votre logique personnalisée
}
