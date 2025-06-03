#include <core/logging/Logger.h>
#include <core/Screen.h>
#include <core/transport/providers/BluetoothProvider.h>

class  BluetoothConnectionCallback {
private:
    Logger* logger;
    Screen* screen;
    
public:
    BluetoothConnectionCallback(Logger* logger, Screen* screen) : logger(logger), screen(screen) {}
    
    void onDeviceConnected(const std::string& deviceAddress)  {
        logger->info("🎉 CALLBACK: Device connecté - " + deviceAddress);
        screen->showStatus("BLE: Connecté");
        // Ici vous pouvez ajouter votre logique personnalisée
    }
    
    void onDeviceDisconnected(const std::string& deviceAddress)  {
        logger->warn("⚠️  CALLBACK: Device déconnecté - " + deviceAddress);
        screen->showStatus("BLE: Déconnecté");
        // Ici vous pouvez ajouter votre logique personnalisée
    }
};