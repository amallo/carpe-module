#pragma once
#include <Arduino.h>


/**
 * @brief Interface pour fournisseur BLE
 */
class BluetoothProvider {
public:
    virtual ~BluetoothProvider() = default;
    virtual bool init(const String& deviceId) = 0;
    virtual bool start() = 0;
    virtual bool isConnected()  = 0;
    virtual bool sendString(const String& message) = 0;
    
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    BluetoothProvider() = default;
    /**
     * @brief Constructeur de copie interdit
     */
    BluetoothProvider(const BluetoothProvider&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    BluetoothProvider& operator=(const BluetoothProvider&) = delete;
}; 
