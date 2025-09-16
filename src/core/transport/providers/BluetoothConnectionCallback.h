#include <core/logging/Logger.h>
#include <core/Screen.h>
#include <core/transport/providers/BluetoothProvider.h>

class  BluetoothConnectionCallback {
private:
    Logger* logger;
    Screen* screen;
    std::string deviceId;
    
public:
    BluetoothConnectionCallback(Logger* logger, Screen* screen) : logger(logger), screen(screen), deviceId("") {}
    
    void setDeviceId(const std::string& id) {
        deviceId = id;
    }
    
    void onDeviceConnected(const std::string& deviceAddress)  {
        logger->info("🎉 CALLBACK: Device connecté - " + deviceAddress);
        // Message optimisé pour OLED (2 lignes)
        std::string readyMessage = deviceId + "\nCONNECTE";
        screen->showMessage(readyMessage);
        logger->info("📱 " + deviceId + " prêt");
        // Ici vous pouvez ajouter votre logique personnalisée
    }
    
    void onDeviceDisconnected(const std::string& deviceAddress)  {
        logger->warn("⚠️  CALLBACK: Device déconnecté - " + deviceAddress);
        // Message optimisé pour OLED (2 lignes)
        std::string waitingMessage = deviceId + "\nATTENTE...";
        screen->showMessage(waitingMessage);
        logger->info("📱 " + deviceId + " en attente de connexion");
        // Ici vous pouvez ajouter votre logique personnalisée
    }
};