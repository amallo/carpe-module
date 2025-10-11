#pragma once
#include <core/logging/Logger.h>
#include <core/device/providers/Screen.h>

// Forward declarations pour éviter la dépendance circulaire
class BluetoothProvider;
class PinCodeGenerator;
class MessageRouter;

class  BluetoothConnectionCallback {
private:
    Logger* logger;
    Screen* screen;
    BluetoothProvider* bluetoothProvider;
    PinCodeGenerator* pinCodeGenerator;
    MessageRouter* messageRouter;  // Nouveau pour le routage futur
    std::string deviceId;
    
public:
    // Constructeur original - maintenu pour compatibilité
    BluetoothConnectionCallback(Logger* logger, Screen* screen, BluetoothProvider* provider, PinCodeGenerator* pinGenerator) 
        : logger(logger), screen(screen), bluetoothProvider(provider), pinCodeGenerator(pinGenerator), messageRouter(nullptr), deviceId("") {}
    
    // Nouveau constructeur avec MessageRouter optionnel
    BluetoothConnectionCallback(Logger* logger, Screen* screen, BluetoothProvider* provider, PinCodeGenerator* pinGenerator, MessageRouter* router) 
        : logger(logger), screen(screen), bluetoothProvider(provider), pinCodeGenerator(pinGenerator), messageRouter(router), deviceId("") {}
    
    void setDeviceId(const std::string& id) {
        deviceId = id;
    }
    
    void onDeviceConnected(const std::string& deviceAddress);
    void onDeviceDisconnected(const std::string& deviceAddress);
};