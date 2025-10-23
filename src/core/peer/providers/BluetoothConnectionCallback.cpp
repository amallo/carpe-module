#include "BluetoothConnectionCallback.h"
#include <core/peer/providers/BluetoothProvider.h>
#include <core/device/PinCodeGenerator.h>
#include <core/transport/MessageRouter.h>
#include <core/peer/model/Message.h>

void BluetoothConnectionCallback::onDeviceConnected(const std::string& deviceAddress) {
    logger->info("🎉 CALLBACK: Device connecté - " + deviceAddress);
    
    // Générer un PIN challenge et l'envoyer au client
    if (bluetoothProvider && pinCodeGenerator) {
        std::string challengePin = pinCodeGenerator->generatePinCode();
        
        // Note: Cette logique est maintenant gérée par PeerConnection
        // Le callback ne fait plus l'envoi de messages directement
        logger->info("📤 PIN challenge envoyé au client: " + challengePin);
        
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
