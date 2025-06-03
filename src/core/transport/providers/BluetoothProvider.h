#pragma once
#include <string>
#include "BluetoothConnectionCallback.h"
#include "BluetoothReceivedMessageCallback.h"


/**
 * @brief Interface pour les fournisseurs de transport Bluetooth
 * Abstraction permettant l'envoi et la réception via BLE ou Bluetooth Classic
 */
class BluetoothProvider {
public:
    virtual ~BluetoothProvider() = default;
    
    virtual bool init(const std::string& deviceId) = 0;
    virtual bool start() = 0;
    virtual bool sendString(const std::string& message) = 0;
    virtual bool isConnected() = 0;
    virtual bool isStarted() = 0;
    
    // Gestion des callbacks de connexion
    virtual void setConnectionCallback(BluetoothConnectionCallback* callback) = 0;
    virtual void setReceivedMessageCallback(BluetoothReceivedMessageCallback* callback) = 0;
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
