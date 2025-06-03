#include <string>
#include <core/logging/Logger.h>
#include <core/Screen.h>

/**
 * @brief Interface pour les callbacks de réception de messages Bluetooth
 */
class BluetoothReceivedMessageCallback {
    private:
    Logger* logger;
    Screen* screen;

public:
    BluetoothReceivedMessageCallback(Logger* logger, Screen* screen) : logger(logger), screen(screen) {}
    
    void onReceivedMessage(const std::string& message) {
        logger->info("🔍 Message reçu: " + message);
        screen->showMessage(message);
    }
};