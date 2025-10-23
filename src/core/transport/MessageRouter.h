#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include "core/peer/model/Message.h"

// Forward declarations
class BluetoothProvider;
class MessageEncoder;
// class LoRaProvider;  // Future

/**
 * @brief Router simple pour diriger les messages entre différents protocoles
 * Permet le routage bidirectionnel BLE ↔ LoRa (futur)
 */
class MessageRouter {
private:
    BluetoothProvider* bluetoothProvider;
    MessageEncoder* messageEncoder;
    // LoRaProvider* loraProvider;  // Future
    
public:
    MessageRouter(MessageEncoder* encoder);
    virtual ~MessageRouter() = default;
    
    /**
     * @brief Enregistrer un provider Bluetooth pour l'envoi
     * @param provider Pointeur vers le provider Bluetooth
     */
    void setBluetoothProvider(BluetoothProvider* provider);
    
    /**
     * @brief Router un message vers le protocole spécifié
     * @param message Le message à envoyer
     * @param targetProtocol Le protocole cible ("bluetooth", "lora")
     * @return true si l'envoi a réussi, false sinon
     */
    bool routeMessage(const Message& message, const std::string& targetProtocol);
    
    
    // Future: void setLoRaProvider(LoRaProvider* provider);
    
protected:
    /**
     * @brief Constructeur de copie interdit
     */
    MessageRouter(const MessageRouter&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    MessageRouter& operator=(const MessageRouter&) = delete;
};
