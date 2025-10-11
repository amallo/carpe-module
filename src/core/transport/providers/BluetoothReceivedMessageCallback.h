#pragma once
#include <string>
#include <core/logging/Logger.h>
#include <core/device/providers/Screen.h>
#include <core/transport/MessageReceivedCallback.h>

/**
 * @brief Callback de réception de messages Bluetooth
 * Hérite de MessageReceivedCallback pour l'unification future
 */
class BluetoothReceivedMessageCallback : public MessageReceivedCallback {
    private:
    Logger* logger;
    Screen* screen;

public:
    BluetoothReceivedMessageCallback(Logger* logger, Screen* screen) : logger(logger), screen(screen) {}
    
    // Ancienne interface - maintenue pour compatibilité
    void onReceivedMessage(const std::string& message) {
        logger->info("🔍 Message reçu: " + message);
        screen->showMessage(message);
    }
    
    // Nouvelle interface MessageReceivedCallback
    void onMessageReceived(const std::vector<uint8_t>& message, const std::string& source) override {
        // Convertir le message binaire en string pour maintenir le comportement existant
        std::string messageStr(reinterpret_cast<const char*>(message.data()), message.size());
        
        // Utiliser l'ancienne méthode pour préserver exactement le même comportement
        onReceivedMessage(messageStr);
    }
};