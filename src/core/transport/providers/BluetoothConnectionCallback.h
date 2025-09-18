#pragma once
#include <core/logging/Logger.h>
#include <core/Screen.h>

// Forward declarations pour éviter la dépendance circulaire
class BluetoothProvider;
class PinCodeGenerator;

class  BluetoothConnectionCallback {
private:
    Logger* logger;
    Screen* screen;
    BluetoothProvider* bluetoothProvider;
    PinCodeGenerator* pinCodeGenerator;
    std::string deviceId;
    
public:
    BluetoothConnectionCallback(Logger* logger, Screen* screen, BluetoothProvider* provider, PinCodeGenerator* pinGenerator) 
        : logger(logger), screen(screen), bluetoothProvider(provider), pinCodeGenerator(pinGenerator), deviceId("") {}
    
    void setDeviceId(const std::string& id) {
        deviceId = id;
    }
    
    void onDeviceConnected(const std::string& deviceAddress);
    void onDeviceDisconnected(const std::string& deviceAddress);
};